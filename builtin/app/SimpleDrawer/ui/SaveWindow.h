#ifndef SAVEWINDOW_H
#define SAVEWINDOW_H

#include <QMainWindow>

namespace Ui {
class SaveWindow;
}

class SaveWindow : public QMainWindow {
	Q_OBJECT

public:
	/**
	 * @brief Construct a new Save Window object
	 * 
	 * @param parent 
	 */
	explicit SaveWindow(QWidget* parent = nullptr);
	/**
	 * @brief bindImage bind the image for saving
	 * @param image
	 */
	inline void bindImage(const QImage& image) {
		holdingImage = image;
		processImageIssue();
	}
	/**
	 * @brief processSave process the save sessions
	 */
	void processSave();

	~SaveWindow();

private slots:
	/**
	 * @brief on_height_spinbox_valueChanged
	 * hooks a change of the height settings
	 * @param arg1 new height
	 */
	void on_height_spinbox_valueChanged(int arg1);
	/**
	 * @brief on_width_spinbox_valueChanged
	 * hooks a change of the width settings
	 * @param arg1 new width
	 */
	void on_width_spinbox_valueChanged(int arg1);

	/**
	 * @brief on_btn_save_clicked save sessions hook
	 */
	void on_btn_save_clicked();

	/**
	 * @brief on_btn_quit_clicked quit sessions hook
	 */
	void on_btn_quit_clicked();

private:
	Ui::SaveWindow* ui;
	QImage holdingImage;
	/**
	 * @brief details image settings, including adjust spinbox...
	 */
	void processImageIssue();
};

#endif // SAVEWINDOW_H
