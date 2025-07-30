#ifndef ADDPANEL_H
#define ADDPANEL_H
#include <QWidget>
class QLineEdit;
class AddPanel : public QWidget {
	Q_OBJECT
public:
    AddPanel(QWidget* parent = nullptr);

signals:
    void addSubmitted(const QString& name);
    void request_new_connection(const QString& name, const QString& ip, const int port);

private:
    QLineEdit* editName;
    QLineEdit* ipAddr;
    QLineEdit* portAddr;

protected:
    bool event(QEvent* ev) override;
};

#endif // ADDPANEL_H
