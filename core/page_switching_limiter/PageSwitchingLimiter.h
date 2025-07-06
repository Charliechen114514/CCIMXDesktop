#ifndef PAGESWITCHINGLIMITER_H
#define PAGESWITCHINGLIMITER_H
class QProgressBar;
class PageSwitchingLimiter {
public:
    PageSwitchingLimiter() = default;
    void processing_progressbar_widget(QProgressBar* bar);
};

#endif // PAGESWITCHINGLIMITER_H
