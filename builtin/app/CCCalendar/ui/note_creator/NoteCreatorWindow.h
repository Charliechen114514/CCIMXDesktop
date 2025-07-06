#ifndef NOTECREATORWINDOW_H
#define NOTECREATORWINDOW_H

#include "Noter.h"
#include <QMainWindow>
namespace Ui {
class NoteCreatorWindow;
}

class NoteCreatorWindow : public QMainWindow {
	Q_OBJECT

public:
    explicit NoteCreatorWindow(QWidget* parent = nullptr);
	~NoteCreatorWindow();

    void setOperatingDate(const QDate& d);

    struct Package {
        QDate date;
        QColor color;
        NoteInfo info;
        inline void force_reset() {
            color = QColor();
            info = {};
            date = {};
        }
    };

    const Package& package() const { return internal_package; }
signals:
    void accept_enqueue();
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::NoteCreatorWindow* ui;
    Package internal_package;
};

#endif // NOTECREATORWINDOW_H
