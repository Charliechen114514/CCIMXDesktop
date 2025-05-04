#include <QScrollBar>
#include "ccpdfscrollarea.h"

void CCPdfScrollArea::mousePressEvent(QMouseEvent* event)
{
    /* yeap a click is started */
    this->is_usr_clicked    = true;
    this->prev_point        =  event->pos();
    /* invoke this for the default behaviour */
    QScrollArea::mousePressEvent(event);
}

void CCPdfScrollArea::mouseReleaseEvent(QMouseEvent *event)
{
    this->is_usr_clicked    = false;
    /* invoke this for the default behaviour */
    QScrollArea::mouseReleaseEvent(event);
}

void CCPdfScrollArea::mouseMoveEvent(QMouseEvent *event)
{
    if(!is_usr_clicked){
        return QScrollArea::mouseMoveEvent(event);
    }

    QPoint delta    = event->pos() - prev_point;
    prev_point      = event->pos();
    QScrollBar* verticalBar = verticalScrollBar();
    QScrollBar* horizontalBar = horizontalScrollBar();
    if(verticalBar)
        verticalBar->setValue(verticalBar->value() - delta.y());
    if(horizontalBar)
        horizontalBar->setValue(horizontalBar->value() - delta.x());
    QScrollArea::mouseMoveEvent(event);
}

/* sadly disabled */
void CCPdfScrollArea::handleGestureEvent(QGestureEvent* event)
{
    // hanlding zoom
    // qDebug() << "Entering the gesture sessions";
    QGesture* zoomGesture = event->gesture(Qt::PinchGesture);
    QPinchGesture* pinch = static_cast<QPinchGesture*>(zoomGesture);

    if(!pinch){
        return;
    }
    CCPdfViewer::ZoomDirection directions;
    if(pinch->scaleFactor() < 1){
        directions = CCPdfViewer::ZoomDirection::ZOOM_OUT;
    }else{
        directions = CCPdfViewer::ZoomDirection::ZOOM_IN;
    }

    emit indicate_zoom(directions);
}

