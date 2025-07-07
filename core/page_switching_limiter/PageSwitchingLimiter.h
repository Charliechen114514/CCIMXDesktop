#ifndef PAGESWITCHINGLIMITER_H
#define PAGESWITCHINGLIMITER_H
#include "library/qt_relative/genbound_progressbar/BoundProgressBarFactory.hpp"

/**
 *  PageSwitching Params here
 */
namespace PageSwitchingLimiterParams {
static constexpr unsigned short LEAST_POSX = 200;
static constexpr unsigned short MAX_POSX = 350;
static constexpr unsigned short DEF_POSX = 250;
}

class PageSwitchingLimiter : public BoundSliderFactory<
                                 PageSwitchingLimiterParams::DEF_POSX,
                                 PageSwitchingLimiterParams::LEAST_POSX,
                                 PageSwitchingLimiterParams::MAX_POSX> {
    Q_OBJECT
public:
    /**
     * @brief PageSwitchingLimiter
     * @param bar
     * @param parent
     */
    PageSwitchingLimiter(QSlider* bar, QObject* parent = nullptr);

protected:
    /**
     * @brief _plain_set_value signals enable class
     * @param value
     */
    void _plain_set_value(int value) override;
signals:
    void valueChanged(int value); ///< signals for monitoring
};

#endif // PAGESWITCHINGLIMITER_H
