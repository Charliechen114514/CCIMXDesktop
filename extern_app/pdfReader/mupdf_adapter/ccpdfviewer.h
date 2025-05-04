#ifndef CCPDFVIEWER_H
#define CCPDFVIEWER_H
#include <QImage>
#include <QWidget>
/* preannounced of the documents */
class CCPdfDocument;
class QScrollArea;
class QLabel;
namespace Ui {
class CCPdfViewer;
}

/* CCPdfViewer really helps we view pdf in page level */
/* it actually interactive with ccpdf_tools::page_renderer */
class CCPdfViewer : public QWidget
{
    Q_OBJECT

public:
    explicit CCPdfViewer(QWidget *parent = nullptr);
    Q_DISABLE_COPY(CCPdfViewer);
    ~CCPdfViewer();
    /* if we can not bind the document, then returns failed */
    bool bindDocument(CCPdfDocument* bindDocument);
    void unbindDocument();
    inline float current_zoom() const {
        return view_zoom;
    }

    inline void set_zoom_step(const float zoom_step){
        this->zoom_step = zoom_step;
    }

    enum class ZoomDirection{
        ZOOM_IN,
        ZOOM_OUT
    };

public slots:
    inline void zoom(
        const ZoomDirection direction
    ){
        switch(direction){
        case ZoomDirection::ZOOM_IN:
            view_zoom += zoom_step;
        break;
        case ZoomDirection::ZOOM_OUT:
            view_zoom -= zoom_step;
        break;
        }
    }

    inline void fresh_zoom(const ZoomDirection direction){
        zoom(direction);
        /* make the fresh */
        fresh_render();
    }

public slots:
    /* call the rendering page */
    void fresh_render();

private:
    Ui::CCPdfViewer *ui;
    /* zooms sometimes overflow the page index, let them in scrollarea */
    CCPdfDocument*  document_for_view{nullptr};
    float           view_zoom{1.0f};
    float           zoom_step{0.1f};
    QImage          cached_image;
    QLabel*         imageLabel;
    void init_internal(void);
};

#endif // CCPDFVIEWER_H
