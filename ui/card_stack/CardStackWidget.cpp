#include "CardStackWidget.h"
#include "library/random_gen_value/random_gen_value.h"
#include <QGraphicsOpacityEffect>
#include <QMouseEvent>
#include <QMutex>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QTimer>
QGraphicsOpacityEffect* CardStackWidget::ensureOpacity(QWidget* w) {
    auto* eff = qobject_cast<QGraphicsOpacityEffect*>(w->graphicsEffect());
    if (!eff) {
        eff = new QGraphicsOpacityEffect(w);
        w->setGraphicsEffect(eff);
    }
    return eff;
}

CardStackWidget::CardStackWidget(QWidget* parent)
    : QStackedWidget(parent)
    , current_animation(new QPropertyAnimation(this))
    , next_animation(new QPropertyAnimation(this))
    , group(new QParallelAnimationGroup(this)) {
    current_animation->setPropertyName("pos");
    next_animation->setPropertyName("pos");
    group->addAnimation(current_animation);
    group->addAnimation(next_animation);
    auto_switcher = new QTimer(this);
    connect(auto_switcher, &QTimer::timeout,
            this, [this]() {
                try {
                    slideTo(RandomGenerator<int>::random(0, count()));
                } catch (const std::exception& e) {
                    qCritical() << "Exception Occurs when card widgets randomly switching to a new card " << e.what();
                }
            });
    mutex = std::make_shared<QMutex>();
}

void CardStackWidget::mousePressEvent(QMouseEvent* event) {
    startPos = event->pos();
    isDragging = true;
}

void CardStackWidget::mouseMoveEvent(QMouseEvent* event) {
    if (count() == 0)
        return; // empty sessions

    if (!isDragging)
        return;

    int dy = event->pos().y() - startPos.y();
    if (qAbs(dy) < 5)
        return;
    QWidget* current_widget = currentWidget();
    int index = currentIndex();
    QWidget* other_wid = nullptr;

    if (dy > 0 && index > 0) {
        other_wid = widget(index - 1);
        other_wid->move(0, -height() + dy); // slider down
    } else if (dy < 0 && index < count() - 1) {
        other_wid = widget(index + 1);
        other_wid->move(0, height() + dy); // slide up
    }

    if (other_wid) {
        other_wid->resize(current_widget->size());
        other_wid->show();
        other_wid->raise();
    }
    current_widget->move(0, dy);
}

void CardStackWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (count() == 0)
        return; // empty sessions
    if (!isDragging)
        return;

    isDragging = false;

    int dy = event->pos().y() - startPos.y();
    int threshold = height() / 4;
    int idx = currentIndex();

    if (dy > threshold) {
        if (idx > 0) {
            qDebug() << "Card Switch to prev one";
            slideTo(idx - 1, false); // 向下切换到上一个
        } else {
            qDebug() << "Due to no prev, bouce back";
            bouceBack(dy, idx); // 没有上一个，回弹当前
        }
    } else if (dy < -threshold) {
        if (idx < count() - 1) {
            qDebug() << "Card Switch to next one";
            slideTo(idx + 1, true); // 向上切换到下一个
        } else {
            qDebug() << "Due to no next, bouce back";
            bouceBack(dy, idx); // 没有下一个，回弹当前
        }
    } else {
        qDebug() << "Miss the thredhold, bouce back";
        bouceBack(dy, idx);
    }
}

void CardStackWidget::bouceBack(int dy, int idx) {
    QWidget* curr = currentWidget();

    QMutexLocker<QMutex> guard(mutex.get());
    current_animation->stop();
    current_animation->setTargetObject(curr);
    current_animation->setPropertyName("pos"); // 保证是 pos
    current_animation->setDuration(animation_duration);
    current_animation->setStartValue(curr->pos());
    current_animation->setEndValue(QPoint(0, 0));

    next_animation->stop();
    next_animation->setTargetObject(nullptr);
    hideAfterAnimation.clear();

    if (dy > 0 && idx > 0) {
        QWidget* prev = widget(idx - 1);
        next_animation->setTargetObject(prev);
        next_animation->setPropertyName("pos");
        next_animation->setDuration(animation_duration);
        next_animation->setStartValue(prev->pos());
        next_animation->setEndValue(QPoint(0, -height()));
        hideAfterAnimation = prev;
    } else if (dy < 0 && idx < count() - 1) {
        QWidget* next = widget(idx + 1);
        next_animation->setTargetObject(next);
        next_animation->setPropertyName("pos");
        next_animation->setDuration(animation_duration);
        next_animation->setStartValue(next->pos());
        next_animation->setEndValue(QPoint(0, height()));
        hideAfterAnimation = next;
    }
    if (next_animation->targetObject()) {
        group->start();
    } else {
        current_animation->start();
    }
}

void CardStackWidget::setCardTransitionMode(CardTransitionMode mode) {
    transitionMode = mode;
}

CardStackWidget::CardTransitionMode CardStackWidget::cardTransitionMode() const {
    return transitionMode;
}

void CardStackWidget::slideTo(int newIndex) {
    return slideTo(newIndex, currentIndex() > newIndex);
}

void CardStackWidget::setablility_of_autoSwitch(bool ability) {
    if (ability) {
        auto_switcher->setInterval(randomize_duration);
        auto_switcher->start();
    } else {
        auto_switcher->stop();
    }
}

bool CardStackWidget::autoSwitchAbility() {
    return auto_switcher->isActive();
}

void CardStackWidget::slideTo(int newIndex, bool slideUp) {
    if (newIndex < 0 || newIndex >= count())
        return;

    if (newIndex == currentIndex())
        return; // no need to slide

    QWidget* curr = currentWidget();
    QWidget* next = widget(newIndex);
    int h = height();

    QMutexLocker<QMutex> guard(mutex.get());
    next->move(0, slideUp ? h : -h);
    next->show();
    next->raise();

    next_animation->stop();
    next_animation->setTargetObject(next);
    next_animation->setDuration(animation_duration);
    next_animation->setStartValue(next->pos());
    next_animation->setEndValue(QPoint(0, 0));
    next_animation->setPropertyName("pos");

    if (transitionMode == CardTransitionMode::Fade) {
        auto* eff = ensureOpacity(curr);
        eff->setOpacity(1.0);

        current_animation->stop();
        current_animation->setTargetObject(eff);
        current_animation->setPropertyName("opacity");
        current_animation->setDuration(animation_duration);
        current_animation->setStartValue(1.0);
        current_animation->setEndValue(0.0);
    } else {
        current_animation->stop();
        current_animation->setTargetObject(curr);
        current_animation->setPropertyName("pos");
        current_animation->setDuration(animation_duration);
        current_animation->setStartValue(curr->pos());
        current_animation->setEndValue(QPoint(0, slideUp ? -h : h));
    }

    hideAfterAnimation = curr;

    disconnect(group, nullptr, nullptr, nullptr);
    connect(group, &QParallelAnimationGroup::finished, this, [this, curr, newIndex]() {
        if (hideAfterAnimation) {
            hideAfterAnimation->hide();
            hideAfterAnimation->move(0, 0);
            if (auto* eff = qobject_cast<QGraphicsOpacityEffect*>(hideAfterAnimation->graphicsEffect())) {
                eff->setOpacity(1.0); // reset
            }
            hideAfterAnimation.clear();
        }
        setCurrentIndex(newIndex);
    });

    group->start();
}
