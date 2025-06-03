#ifndef FIGUREOBJECT_H
#define FIGUREOBJECT_H

#include <QObject>

/**
 * @class FigureObject
 * @brief Abstract base class for all drawable game objects
 */
class FigureObject : public QObject {
    Q_OBJECT
public:
	/**
	 * @brief Constructs a FigureObject
	 * @param parent Parent QObject
	 */
	explicit FigureObject(QObject* parent = nullptr);

	/**
	 * @brief Virtual destructor
	 */
	virtual ~FigureObject() = default;

public: /* interfaces */
	/**
	 * @brief Gets the current bounding rectangle for collision detection
	 * @return Reference to the current bounding QRect
	 * @note Pure virtual function must be implemented by derived classes
	 */
	virtual QRect& provide_current_bounding_rect() = 0;

	/**
	 * @brief Gets the current image frame for rendering
	 * @return Reference to the current QPixmap frame
	 * @note Pure virtual function must be implemented by derived classes
	 */
	virtual QPixmap& provide_drawing_srcframe() = 0;
};

#endif // FIGUREOBJECT_H
