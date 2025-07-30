#ifndef INFOWIDGET_H
#define INFOWIDGET_H
#include <QWidget>
class QLabel;
class QListWidget;
class QTableWidget;

class InfoWidget : public QWidget {
	Q_OBJECT
public:
    explicit InfoWidget(QWidget* parent = nullptr);

public slots:
    void show_current_port(const int port);

private:
    QLabel* nameLabel { nullptr };
    QLabel* ipLabel { nullptr };
    QLabel* portTitle { nullptr };
    QTableWidget* infoTable { nullptr };
    QListWidget* portList { nullptr };
};

#endif // INFOWIDGET_H
