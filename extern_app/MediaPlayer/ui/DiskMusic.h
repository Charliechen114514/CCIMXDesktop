#ifndef DISKMUSIC_H
#define DISKMUSIC_H
#include <QTimer>
#include <QWidget>
class QPropertyAnimation;
class QVariantAnimation;
namespace Ui {
class DiskMusic;
}

class DiskMusic : public QWidget {
	Q_OBJECT
	/* Animation use this to access how to draw arm */
	Q_PROPERTY(qreal armAngle READ armAngle WRITE setArmAngle NOTIFY armAngleChanged);
	static constexpr const unsigned int ANIMATION_DURATION = 300;
	static constexpr const unsigned int ANIMATION_FPS = 60;
	static constexpr const qreal BEGIN_ANGLE = -30;
	static constexpr const qreal END_ANGLE = -10;
	static constexpr const unsigned int SWITCH_COLOR_MSEC_INTERVAL = 20000;
	static constexpr const unsigned int COLOR_SWITCH_PROCESS_INTERVAL = 2000;

	/* every time the default color media first open */
	static constexpr const QColor BEGIN_COLOR = QColor(173, 216, 230);
	static constexpr const QColor END_COLOR = QColor(0, 51, 102);

public:
	explicit DiskMusic(QWidget* parent = nullptr);
	void setStatus(bool set_is_playing);
	void setPixmap(const QString& pixmap_path);
	inline qreal armAngle() const {
		return angle;
	}

	inline void setArmAngle(qreal angle) {
		this->angle = angle;
		update();
		emit armAngleChanged();
	}

	~DiskMusic();

signals:
	void armAngleChanged();

protected:
	void paintEvent(QPaintEvent*) override;

private:
	Ui::DiskMusic* ui;
	qreal angle { BEGIN_ANGLE }; /* arm angle */
	float current_rotations {};
	bool is_playing { false };
	QTimer animate_timer;
	QPropertyAnimation* animation { nullptr };
	QVariantAnimation* color_animation { nullptr };
	struct {
		QPixmap coverPixmap;
		QPixmap armPixmap;
		QPixmap recordPixmap;
	} pixmaps;
	void initUi();
	void initCore();
	void process_rotation() {
		current_rotations += 0.5;
		if (current_rotations >= 360.0)
			current_rotations -= 360.0;
		update();
	}
	/* for current varient change */
	void process_the_color_change(QPainter& p);
	void startColorTransition();

	QColor beginColor { BEGIN_COLOR };
	QColor endColor { END_COLOR };
	QColor targetStart;
	QColor targetEnd;

	QTimer color_switch_timer;
};

#endif // DISKMUSIC_H
