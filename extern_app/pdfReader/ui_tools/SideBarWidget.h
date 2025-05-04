#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include <QEasingCurve>
#include <QWidget>
class QPropertyAnimation;
class QParallelAnimationGroup;
namespace SideBarWidgetStaticConfig {
static constexpr const bool               INIT_STATE         = false;
static constexpr const int                ANIMATION_DURATION = 500;
static constexpr const QEasingCurve::Type ANIMATION_CURVE =
    QEasingCurve::InOutQuad;
};  // namespace SideBarWidgetStaticConfig

namespace Ui {
class SideBarWidget;
}

class SideBarWidget : public QWidget {
    Q_OBJECT

public:
    explicit SideBarWidget(QWidget* parent = nullptr);
    void inline showSideBar() {
        setState(false);
    }
    void inline hideSideBar() {
        setState(true);
    }
    enum class Role { SideBar, MainSide };
    /* addWidgets to the two sides */
    void addLayout(const QWidgetList& widgetList, Role r);
    /* remove the display widgets */
    void removeLayout(Role r);
    /* enable or disable the button visibilities */
    void setButtonVisible(bool visible);
    /* setTypes and durations */
    void setAnimationDuration(int duration);
    void setAnimationCurve(QEasingCurve::Type curve);
    inline bool current_ui_states(){return hidden_state;}
    ~SideBarWidget();
public slots:
    void switch_state();
    void switch_button_visible();

private:
    QPropertyAnimation*      animation_main;
    QPropertyAnimation*      animation_side;
    QPropertyAnimation*      animation_button;
    QParallelAnimationGroup* group;
    void inline setState(bool st) {
        hidden_state = st;
        hidden_state ? do_hide_animations() : do_show_animations();
    }
    void               __initMemory();
    void               __initConnection();
    void               do_hide_animations();
    void               do_show_animations();
    bool               hidden_state{SideBarWidgetStaticConfig::INIT_STATE};
    Ui::SideBarWidget* ui;
};

#endif  // SIDEBARWIDGET_H
