#ifndef CALENDARWINDOW_H
#define CALENDARWINDOW_H

#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class CalendarWindow;
}
QT_END_NAMESPACE

// Forward declarations
class DateNoter;
class Noter;
class NoteCreatorWindow;

/**
 * @class CalendarWindow
 * @brief Main application window for calendar and note management
 *
 * Provides the primary interface for viewing dates, creating notes,
 * and toggling between light/dark modes.
 */
class CalendarWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructs the CalendarWindow
     * @param parent The parent widget (optional)
     */
    explicit CalendarWindow(QWidget* parent = nullptr);

    /**
     * @brief Destructor
     */
    ~CalendarWindow();

    /**
     * @brief Toggles between light and dark UI modes
     */
    void flipMode();

    /**
     * @brief Opens the note creator window
     */
    void openNoteCreator();

private:
    Ui::CalendarWindow* ui; /**< Pointer to the UI components */
    DateNoter* dateNoter; /**< Pointer to the date note widget */
    std::shared_ptr<Noter> noter; /**< Shared pointer to the note manager */
    NoteCreatorWindow* noteCreatorWindow { nullptr }; /**< Pointer to note creator window */

    /**
     * @brief Establishes signal-slot connections
     */
    void setupConnections();

    /**
     * @brief Updates UI text after mode change
     */
    void adjustModeText();

    /**
     * @brief Initializes the note window components
     */
    void setup_noteWindow();

private slots:
    /**
     * @brief Handles accepted note creation
     */
    void process_enqueue_issue();

    /**
     * @brief Handles cancelled note creation
     */
    void process_cancel_mark();
};

#endif // CALENDARWINDOW_H
