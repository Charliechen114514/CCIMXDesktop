#ifndef CCPDFSCROLLAREA_H
#define CCPDFSCROLLAREA_H

#include "ccpdfviewer.h"
#include <QGestureEvent>
#include <QScrollArea>
#include <QTouchEvent>

/// @class CCPdfScrollArea
/// @brief A custom scroll area that supports gesture-based zooming for PDF viewing.
class CCPdfScrollArea : public QScrollArea {
	Q_OBJECT
public:
	/**
	 * @brief Constructs a CCPdfScrollArea with optional parent widget.
	 *
	 * Enables touch event handling and pinch gesture recognition.
	 *
	 * @param parent The parent widget.
	 */
	explicit CCPdfScrollArea(QWidget* parent = nullptr)
		: QScrollArea(parent) {
		setAttribute(Qt::WA_AcceptTouchEvents);
		grabGesture(Qt::PinchGesture);
	}

signals:
	/// Emitted when a zoom gesture is detected.
	void indicate_zoom(CCPdfViewer::ZoomDirection);

protected:
	/**
	 * @brief Records initial press position when mouse is pressed.
	 * @param event Mouse press event.
	 */
	void mousePressEvent(QMouseEvent* event) override;

	/**
	 * @brief Ends click state when mouse is released.
	 * @param event Mouse release event.
	 */
	void mouseReleaseEvent(QMouseEvent* event) override;

	/**
	 * @brief Processes dragging or scrolling when mouse is moved.
	 * @param event Mouse move event.
	 */
	void mouseMoveEvent(QMouseEvent* event) override;

	/**
	 * @brief Handles gesture events such as pinch-to-zoom.
	 * @param event Gesture event object.
	 */
	void handleGestureEvent(QGestureEvent* event);

private:
	bool is_usr_clicked { false }; ///< Indicates if the user has clicked (for drag tracking).
	QPoint prev_point; ///< Stores previous mouse position for move calculations.
};

#endif // CCPDFSCROLLAREA_H
