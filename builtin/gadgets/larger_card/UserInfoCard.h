/**
 * @file UserInfoCard.h
 * @brief Defines the UserInfoCard class, a custom QWidget for displaying user information.
 */

#ifndef USERINFOCARD_H
#define USERINFOCARD_H

#include "core/users/UserInfo.h"
#include <QWidget>

// Forward declarations for QLabel to avoid including its header in UserInfoCard.h if not strictly necessary,
// improving compilation times. However, for QLabel, it's often included directly.
// This is more for demonstrating good practice if there were more complex dependencies.
class QLabel;

/**
 * @class UserInfoCard
 * @brief The UserInfoCard class provides a customizable widget to display detailed user information.
 *
 * This widget is designed to present user details such as avatar, name, phone number, and email
 * in a clear and organized card format. It inherits from QWidget and utilizes QLabel
 * components for displaying individual pieces of information. The layout and appearance
 * can be customized through its paintEvent.
 */
class UserInfoCard : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs a UserInfoCard object.
     * @param parent A pointer to the parent widget, if any. Defaults to nullptr.
     */
    explicit UserInfoCard(QWidget* parent = nullptr);

public slots:
    /**
     * @brief Sets the user information to be displayed on the card.
     * 	 * This slot updates the QLabel elements with the provided user information,
     * triggering a repaint of the widget to reflect the changes.
     * @param info A constant reference to a UserInfo object containing the details to display.
     */
    void setUserInfo(const UserInfo& info);

protected:
    /**
     * @brief Overrides the default paint event for the widget.
     * 	 * This method is responsible for custom drawing operations for the UserInfoCard,
     * such as background, borders, or positioning of internal widgets.
     * @param event A pointer to the QPaintEvent object that contains information about the paint area.
     */
    void paintEvent(QPaintEvent* event) override;

private:
    /**
     * @brief QLabel to display the user's avatar.
     */
    QLabel* avatarLabel;
    /**
     * @brief QLabel to display the user's name.
     */
    QLabel* nameLabel;
    /**
     * @brief QLabel to display the user's phone number.
     */
    QLabel* phoneLabel;
    /**
     * @brief QLabel to display the user's email address.
     */
    QLabel* emailLabel;
};

#endif // USERINFOCARD_H
