#ifndef CALENDARWINDOW_H
#define CALENDARWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class CalendarWindow;
}
QT_END_NAMESPACE
class DateNoter;
class Noter;
class NoteCreatorWindow;
class CalendarWindow : public QMainWindow {
	Q_OBJECT

public:
    CalendarWindow(QWidget* parent = nullptr);
	~CalendarWindow();

    /**
     * @brief flipMode flip the Ui Apperence
     */
    void flipMode();

    void openNoteCreator();

private:
    Ui::CalendarWindow* ui;
    DateNoter* dateNoter;
    std::shared_ptr<Noter> noter;
    NoteCreatorWindow* noteCreatorWindow { nullptr };
    /**
     * @brief setupConnections will install the actions
     * to the connections
     */
    void setupConnections();
    /**
     * @brief adjustModeText using for the post flips
     */
    void adjustModeText();
    /**
     * @brief setup_noteWindow as expected
     */
    void setup_noteWindow();
private slots:
    /**
     * @brief process_enqueue_issue
     */
    void process_enqueue_issue();

    /**
     * @brief process_cancel_mark
     */
    void process_cancel_mark();
};
#endif // CALENDARWINDOW_H
