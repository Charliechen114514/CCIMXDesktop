#ifndef METAINFOWINDOW_H
#define METAINFOWINDOW_H
#include "mupdf_tools/mupdf_tools.h"
#include <QMainWindow>

namespace Ui {
class MetaInfoWindow;
}

class MetaInfoWindow : public QMainWindow {
	Q_OBJECT

public:
	/**
	 * @brief Construct a new Meta Info Window object
	 * 
	 * @param parent 
	 */
	explicit MetaInfoWindow(QWidget* parent = nullptr);
	/**
	 * @brief set_metas meta infos for the displayings
	 * @param info infos to display
	 * @note if you wanna sync set and display, set_metas_and_display
	 * is your choice
	 * @see set_metas_and_display
	 */
	void set_metas(const CCPdfMetaInfo& info);
	/**
	 * @brief set_metas_and_display meta infos for the displayings
	 * @param info infos to display
	 * @note this make a direct flush
	 */
	void set_metas_and_display(const CCPdfMetaInfo& info);

	~MetaInfoWindow();

private slots:
	void on_pushButton_clicked();

private:
	Ui::MetaInfoWindow* ui;
};

#endif // METAINFOWINDOW_H
