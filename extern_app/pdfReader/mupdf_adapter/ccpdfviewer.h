#ifndef CCPDFVIEWER_H
#define CCPDFVIEWER_H

#include <QImage>
#include <QWidget>

/* Forward declarations */
class CCPdfDocument;
class QScrollArea;
class QLabel;

namespace Ui {
class CCPdfViewer;
}

/**
 * @class CCPdfViewer
 * @brief Provides a widget to view PDF documents at the page level.
 *
 * This class interacts with ccpdf_tools::page_renderer to render PDF pages.
 */
class CCPdfViewer : public QWidget {
    Q_OBJECT

public:
	/**
	 * @brief Constructs a new CCPdfViewer widget.
	 * @param parent The parent widget.
	 */
	explicit CCPdfViewer(QWidget* parent = nullptr);

	Q_DISABLE_COPY(CCPdfViewer);

	/**
	 * @brief Destructor.
	 */
	~CCPdfViewer();

	/**
	 * @brief Binds a PDF document to the viewer.
	 * @param bindDocument Pointer to the CCPdfDocument to bind.
	 * @return true if the document is successfully bound, false otherwise.
	 */
	bool bindDocument(CCPdfDocument* bindDocument);

	/**
	 * @brief Unbinds the currently bound document.
	 */
	void unbindDocument();

	/**
	 * @brief Returns the current zoom level.
	 * @return The current zoom factor.
	 */
	inline float current_zoom() const {
		return view_zoom;
	}

	/**
	 * @brief Sets the zoom step value.
	 * @param zoom_step The zoom increment or decrement per zoom action.
	 */
	inline void set_zoom_step(const float zoom_step) {
		this->zoom_step = zoom_step;
	}

	/**
	 * @enum ZoomDirection
	 * @brief Specifies the direction of zooming.
	 */
	enum class ZoomDirection {
		ZOOM_IN, /**< Zoom in */
		ZOOM_OUT /**< Zoom out */
	};

public slots:
	/**
	 * @brief Applies zoom in the specified direction.
	 * @param direction The direction of zoom (in or out).
	 */
	inline void zoom(const ZoomDirection direction) {
		switch (direction) {
		case ZoomDirection::ZOOM_IN:
			view_zoom += zoom_step;
			break;
		case ZoomDirection::ZOOM_OUT:
			view_zoom -= zoom_step;
			break;
		}
	}

	/**
	 * @brief Zooms and refreshes the rendered view.
	 * @param direction The direction to zoom.
	 */
	inline void fresh_zoom(const ZoomDirection direction) {
		zoom(direction);
		fresh_render();
	}

public slots:
	/**
	 * @brief Refreshes the rendered page view.
	 */
	void fresh_render();

private:
	Ui::CCPdfViewer* ui; /**< The UI interface pointer. */
	CCPdfDocument* document_for_view { nullptr }; /**< Pointer to the document being viewed. */
	float view_zoom { 1.0f }; /**< Current zoom level. */
	float zoom_step { 0.1f }; /**< Zoom increment step. */
	QImage cached_image; /**< Cached rendered image of the page. */
	QLabel* imageLabel; /**< Label used to display the image. */

	/**
	 * @brief Initializes internal components of the viewer.
	 */
	void init_internal(void);
};

#endif // CCPDFVIEWER_H
