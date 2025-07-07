#ifndef NOTECREATORWINDOW_H
#define NOTECREATORWINDOW_H

#include "Noter.h"
#include <QMainWindow>

namespace Ui {
class NoteCreatorWindow;
}

/**
 * @class NoteCreatorWindow
 * @brief A window for creating and editing date notes
 *
 * Provides a complete interface for creating, editing, and managing
 * notes with associated dates and colors.
 */
class NoteCreatorWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructs a NoteCreatorWindow
     * @param parent The parent widget
     */
    explicit NoteCreatorWindow(QWidget* parent = nullptr);

    /**
     * @brief Destructor
     */
    ~NoteCreatorWindow();

    /**
     * @brief Sets the operating date
     * @param date The date to operate on
     */
    void setOperatingDate(const QDate& date);

    /**
     * @struct Package
     * @brief Contains all data for a note
     */
    struct Package {
        QDate date; /**< The note date */
        QColor color; /**< The note color */
        NoteInfo info; /**< The note content */

        /**
         * @brief Resets all package data
         */
        inline void force_reset() {
            color = QColor();
            info = {};
            date = {};
        }
    };

    /**
     * @brief Gets the current note package
     * @return The current package
     */
    const Package& package() const { return internal_package; }

signals:
    /**
     * @brief Emitted when changes are accepted
     */
    void accept_enqueue();

private slots:
    /**
     * @brief Handles dialog acceptance
     */
    void on_buttonBox_accepted();

    /**
     * @brief Handles dialog rejection
     */
    void on_buttonBox_rejected();

private:
    Ui::NoteCreatorWindow* ui; /**< The UI components */
    Package internal_package; /**< The current note package */
};

#endif // NOTECREATORWINDOW_H
