#include "toolssidebar.h"
#include "ui_toolssidebar.h"

ToolsSideBar::ToolsSideBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ToolsSideBar)
{
    ui->setupUi(this);
    chapter_maker.bindSolvedTreeWidget(ui->outline_tree);
    setup_connections();
}

void ToolsSideBar::setup_connections()
{
    connect(ui->btn_open_meta_info_window, &QPushButton::clicked,
            this, &ToolsSideBar::sig_open_meta_info_window);
    connect(ui->outline_tree, &QTreeWidget::itemClicked, this, [=](QTreeWidgetItem* item, int) {
        int page = item->data(0, Qt::UserRole).toInt();
        if (page >= 0) {
            emit required_page_jump(page);
        }
    });
}

void ToolsSideBar::set_document_chapterize(CCPdfDocument* document_handling)
{
    chapter_maker.parse_and_set(document_handling);
}

ToolsSideBar::~ToolsSideBar()
{
    delete ui;
}
