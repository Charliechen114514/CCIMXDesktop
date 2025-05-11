#include "MediaInfoWindow.h"
#include "core/UiTools.h"
#include "ui_MediaInfoWindow.h"

namespace {
void fillTableWithMediaInfo(QTableWidget* table, const MediaInfo& info) {
	struct KeyValue {
		QString key;
		QString value;
	};

	QList<KeyValue> items = {
		{ "Title", info.title },
		{ "Author", info.author },
		{ "Album Title", info.albumTitle },
		{ "Album Artist", info.albumArtist },
		{ "Composer", info.composer },
		{ "Genre", info.genre },
		{ "Duration (ms)", UiTools::toMediaTypicalTimeStr(info.durationMs) },
		{ "Date", info.date },
		{ "Track Number", QString::number(info.trackNumber) },
		{ "Bitrate", QString::number(info.audioBitRate) + " kbps" },
		{ "Audio Codec", info.audioCodec },
		{ "Media Type", info.mediaType },
		{ "Sample Rate", QString::number(info.sampleRate) + " Hz" },
		{ "Publisher", info.publisher }
	};

	table->clear();
	table->setColumnCount(2);
	table->setRowCount(items.size());
	/* stretch the last sections */
	table->horizontalHeader()->setStretchLastSection(true);
	table->setHorizontalHeaderLabels(QStringList() << "Key" << "Value");
	table->verticalHeader()->setVisible(false);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setSelectionMode(QAbstractItemView::NoSelection);

	for (int i = 0; i < items.size(); ++i) {
		qDebug() << "Key:" << items[i].key << "Value:" << items[i].value;
		table->setItem(i, 0, new QTableWidgetItem(items[i].key));
		table->setItem(i, 1, new QTableWidgetItem(items[i].value));
	}

	table->resizeColumnsToContents();
}

}

MediaInfoWindow::MediaInfoWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MediaInfoWindow) {
    ui->setupUi(this);
    /* prefilled */
    fillTableWithMediaInfo(ui->infoTable, {});
    connect(ui->btn_exit, &QPushButton::clicked,
            this, &MediaInfoWindow::close);
}

MediaInfoWindow::~MediaInfoWindow() {
    delete ui;
}

void MediaInfoWindow::filled_metainfo(const MediaInfo info) {
	/* filled the metas */
	fillTableWithMediaInfo(ui->infoTable, info);
}
