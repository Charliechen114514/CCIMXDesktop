#ifndef USERINFOCARD_H
#define USERINFOCARD_H
#include "core/users/UserInfo.h"
#include <QWidget>
class QLabel;

class UserInfoCard : public QWidget {
    Q_OBJECT
public:
    explicit UserInfoCard(QWidget* parent = nullptr);
public slots:
    void setUserInfo(const UserInfo& info);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QLabel* avatarLabel;
    QLabel* nameLabel;
    QLabel* phoneLabel;
    QLabel* emailLabel;
};
#endif // USERINFOCARD_H
