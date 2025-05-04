#ifndef CCPDFSCROLLAREA_H
#define CCPDFSCROLLAREA_H
#include <QScrollArea>
#include <QTouchEvent>
#include <QGestureEvent>
#include "ccpdfviewer.h"
class CCPdfScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit CCPdfScrollArea(QWidget* parent = nullptr) : QScrollArea(parent){
        setAttribute(Qt::WA_AcceptTouchEvents);
        grabGesture(Qt::PinchGesture);
    }

signals:
    void indicate_zoom(CCPdfViewer::ZoomDirection);

protected:
    /* start the recording of the press event */
    void mousePressEvent(QMouseEvent* event) override;

    /* end the recording of the press event */
    void mouseReleaseEvent(QMouseEvent* event) override;

    /* process the issue */
    void mouseMoveEvent(QMouseEvent* event) override;

    void handleGestureEvent(QGestureEvent* event);
private:
    bool        is_usr_clicked{false};
    QPoint      prev_point;
};

#endif // CCPDFSCROLLAREA_H
