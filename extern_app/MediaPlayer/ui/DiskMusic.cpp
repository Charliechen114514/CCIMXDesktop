#include "DiskMusic.h"
#include "ui_DiskMusic.h"
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QVariantAnimation>
namespace {
/* pixmap should be rounded */
QPixmap toCirclePixmap(const QPixmap& org, int d) {
	QPixmap dst(d, d);
	dst.fill(Qt::transparent);

	QPainter painter(&dst);
	painter.setRenderHint(QPainter::Antialiasing);
	QPainterPath path;
	path.addEllipse(0, 0, d, d);
	painter.setClipPath(path);
	painter.drawPixmap(0, 0, d, d,
					   org.scaled(d, d,
								  Qt::KeepAspectRatioByExpanding,
								  Qt::SmoothTransformation));
	return dst;
}

/* to make it progressable */
QColor interpolateColor(const QColor& from, const QColor& to, qreal progress) {
	int r = from.red() + (to.red() - from.red()) * progress;
	int g = from.green() + (to.green() - from.green()) * progress;
	int b = from.blue() + (to.blue() - from.blue()) * progress;
	return QColor(r, g, b);
}

};

DiskMusic::DiskMusic(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DiskMusic) {
	ui->setupUi(this);
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAutoFillBackground(false);
	initCore();
	initUi();
}

void DiskMusic::setStatus(bool set_is_playing) {
	is_playing = set_is_playing;
	if (is_playing) {
		animate_timer.start(1000 / ANIMATION_FPS);
		animation->setStartValue(angle);
		animation->setEndValue(END_ANGLE);
		animation->start();
	} else {
		animate_timer.stop();
		animation->setStartValue(angle);
		animation->setEndValue(BEGIN_ANGLE);
		animation->start();
	}
}

void DiskMusic::setPixmap(const QString& pixmap_path) {
	pixmaps.coverPixmap = QPixmap(pixmap_path);
}

void DiskMusic::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	int side = qMin(width(), height());
	QPoint center(width() / 2, height() / 2);
	int recordRadius = side * 0.5;
	int coverRadius = recordRadius * 0.5;

	painter.save();
	process_the_color_change(painter);
	painter.restore();

	painter.save();
	painter.translate(center);
	painter.rotate(current_rotations);
	QPixmap scaledRecord = pixmaps.recordPixmap.scaled(recordRadius * 2, recordRadius * 2,
													   Qt::KeepAspectRatio, Qt::SmoothTransformation);
	painter.drawPixmap(-recordRadius, -recordRadius, scaledRecord);
	painter.restore();

	painter.save();
	painter.translate(center);
	painter.rotate(current_rotations);
	QPixmap circularCover = toCirclePixmap(pixmaps.coverPixmap, coverRadius * 2);
	painter.drawPixmap(-coverRadius, -coverRadius, circularCover);
	painter.restore();

	painter.save();
	painter.translate(center.x(), center.y() - recordRadius + 5);
	painter.rotate(angle);
	QPixmap scaledArm = pixmaps.armPixmap.scaledToWidth(side * 0.3, Qt::SmoothTransformation);
	painter.drawPixmap(-30, 0, scaledArm);
	painter.restore();
}

void DiskMusic::initUi() {
	targetStart = QColor::fromHsv(QRandomGenerator::global()->bounded(360), 128, 230);
	targetEnd = QColor::fromHsv(QRandomGenerator::global()->bounded(360), 255, 80);
	pixmaps.armPixmap = QPixmap(":/icons/tunearm.png");
	pixmaps.recordPixmap = QPixmap(":/icons/records.png");
	pixmaps.coverPixmap = QPixmap(":/icons/default_music_cover.png");
}

void DiskMusic::initCore() {
	connect(&animate_timer, &QTimer::timeout,
			this, &DiskMusic::process_rotation);
	animation = new QPropertyAnimation(this, "armAngle");
	animation->setDuration(DiskMusic::ANIMATION_DURATION);

	/* set up color sessions */
	color_animation = new QVariantAnimation(this);
	color_animation->setDuration(COLOR_SWITCH_PROCESS_INTERVAL);
	color_animation->setEasingCurve(QEasingCurve::InOutQuad);
	connect(color_animation, &QVariantAnimation::valueChanged, this, [this](const QVariant&) {
		update();
	});
	connect(&color_switch_timer, &QTimer::timeout, this, &DiskMusic::startColorTransition);
	color_switch_timer.start(SWITCH_COLOR_MSEC_INTERVAL);
}

void DiskMusic::process_the_color_change(QPainter& painter) {
	qreal progress = color_animation->state() == QAbstractAnimation::Running
		? color_animation->currentValue().toReal()
		: 1.0;

	QColor currentStart = interpolateColor(beginColor, targetStart, progress);
	QColor currentEnd = interpolateColor(endColor, targetEnd, progress);

	painter.setRenderHint(QPainter::Antialiasing);
	painter.setOpacity(0.6);

	QLinearGradient gradient(rect().topLeft(), rect().bottomRight());
	gradient.setColorAt(0, currentStart);
	gradient.setColorAt(1, currentEnd);

	painter.fillRect(rect(), gradient);

	if (progress >= 1.0) {
		beginColor = targetStart;
		endColor = targetEnd;
	}
}

void DiskMusic::startColorTransition() {
	targetStart = QColor::fromHsv(QRandomGenerator::global()->bounded(360), 128, 230);
	targetEnd = QColor::fromHsv(QRandomGenerator::global()->bounded(360), 255, 80);

	color_animation->setStartValue(0.0);
	color_animation->setEndValue(1.0);
	color_animation->start();
}

DiskMusic::~DiskMusic() {
	delete ui;
}
