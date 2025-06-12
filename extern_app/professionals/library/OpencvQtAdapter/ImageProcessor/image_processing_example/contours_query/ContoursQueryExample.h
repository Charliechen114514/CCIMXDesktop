#ifndef CONTOURSQUERYEXAMPLE_H
#define CONTOURSQUERYEXAMPLE_H

#include <QWidget>

namespace Ui {
class ContoursQueryExample;
}

/**
 * @brief The ContoursQueryExample class
 * Widget for demonstrating contour detection and querying methods.
 */
class ContoursQueryExample : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Construct a new ContoursQueryExample widget
     * @param parent The parent widget, or nullptr if none
     */
    explicit ContoursQueryExample(QWidget* parent = nullptr);

    /**
     * @brief Process the image using contour querying algorithms
     */
    void process_image_session();

    /**
     * @brief Destroy the ContoursQueryExample widget
     */
    ~ContoursQueryExample();

private:
    /**
     * @brief Pointer to the UI elements generated from the .ui file
     */
    Ui::ContoursQueryExample* ui;
};

#endif // CONTOURSQUERYEXAMPLE_H
