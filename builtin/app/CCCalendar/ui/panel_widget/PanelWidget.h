#ifndef PANELWIDGET_H
#define PANELWIDGET_H

#include <QWidget>
class QPropertyAnimation;
/**
 * @brief The PanelWidget class
 */
class PanelWidget : public QWidget {
	Q_OBJECT
public:
    /**
     * @brief PanelWidget
     * @param parent
     */
    explicit PanelWidget(QWidget* parent = nullptr);

    void slideIn(); ///< slide the widget in
    void slideOut(); ///< slide the widget out

private:
    QPropertyAnimation* animation; ///< Animation Holder
    bool isSlidingIn { false }; ///< marking for the sliding
    void closePanel(); ///< panel close IMPL
    void updatePosition(); ///< position calculation
    /**
     * @brief eventFilter
     * @param watched
     * @param event
     * @return
     */
    bool eventFilter(QObject* watched, QEvent* event) override;
};

#endif // PANELWIDGET_H
