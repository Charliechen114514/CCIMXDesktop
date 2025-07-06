#include "CalendarWindow.h"
#include "date_noter/DateNoter.h"
#include "note_creator/NoteCreatorWindow.h"
#include "ui_CalendarWindow.h"
CalendarWindow::CalendarWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::CalendarWindow) {
	ui->setupUi(this);
    dateNoter = new DateNoter(this);
    noter = std::make_shared<Noter>();
    setupConnections();
    adjustModeText();
}

CalendarWindow::~CalendarWindow() {
	delete ui;
}

void CalendarWindow::flipMode() {
    /* flip first */
    ui->calendarWidget->setDarkMode(!ui->calendarWidget->isDarkMode());
    adjustModeText();
}

void CalendarWindow::openNoteCreator() {
    setup_noteWindow();
    noteCreatorWindow->show();
}

void CalendarWindow::setupConnections() {
    connect(ui->actionExit, &QAction::triggered,
            this, &CalendarWindow::close);
    connect(ui->actionswitchMode, &QAction::triggered,
            this, &CalendarWindow::flipMode);
    connect(ui->calendarWidget, &ModernCalendarWidget::clicked,
            this, [this](const QDate d) {
                dateNoter->setDisplayingDate(d, noter->noteInfo(d));
                dateNoter->slideIn();
            });

    connect(ui->calendarWidget, &ModernCalendarWidget::activated,
            this, [this](const QDate& d) {
                setup_noteWindow();
                noteCreatorWindow->setOperatingDate(d);
                noteCreatorWindow->show();
            });

    connect(ui->actioncreate_notes, &QAction::triggered,
            this, &CalendarWindow::openNoteCreator);
    connect(ui->actionopen_selected_noter, &QAction::triggered,
            dateNoter, &DateNoter::slideIn);
    connect(ui->actioncancel_mark, &QAction::triggered,
            this, &CalendarWindow::process_cancel_mark);
}

void CalendarWindow::adjustModeText() {
    const bool isDarkMode = ui->calendarWidget->isDarkMode();
    const char* text = isDarkMode ? "Light Mode" : "Dark Mode";
    ui->actionswitchMode->setText(text);
}

void CalendarWindow::setup_noteWindow() {
    if (!noteCreatorWindow) {
        noteCreatorWindow = new NoteCreatorWindow(this);
        connect(noteCreatorWindow, &NoteCreatorWindow::accept_enqueue,
                this, &CalendarWindow::process_enqueue_issue);
    }
}

void CalendarWindow::process_enqueue_issue() {
    const NoteCreatorWindow::Package& package = noteCreatorWindow->package();
    ui->calendarWidget->setColorForDate(package.date, package.color);
    noter->submitNoteInfo(package.date, package.info);
}

void CalendarWindow::process_cancel_mark() {
    QDate d = ui->calendarWidget->selectedDate();
    noter->removeNoteInfo(d);
    ui->calendarWidget->popColorForData(d);
}
