#ifndef STACKPAGE_SWITCHER_ANIMATION_H
#define STACKPAGE_SWITCHER_ANIMATION_H
#include <QObject>
class QStackedWidget;

struct StackpageSwitcherAnimation : public QObject
{
    Q_OBJECT
public:
    explicit StackpageSwitcherAnimation(QObject* parent = nullptr) : QObject(parent){}

    struct AnimationInfo{
        int     new_index;
        bool    toLeft;
        int     animation_duration{400};
    };

    static void process_animations(
        QStackedWidget* binding_widget,
        AnimationInfo* animation_info);

};

#endif // STACKPAGE_SWITCHER_ANIMATION_H
