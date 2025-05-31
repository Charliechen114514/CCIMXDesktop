#ifndef SIMPLEDRAWINGSCENE_H
#define SIMPLEDRAWINGSCENE_H
#include <QGraphicsScene>
#include <QPainterPath>

/**
 * @class SimpleDrawingScene
 * @brief A QGraphicsScene subclass that provides simple drawing capabilities
 *
 * This class implements a drawing canvas with multiple shape types, undo/redo
 * functionality, and different interaction modes.
 */
class SimpleDrawingScene : public QGraphicsScene {
public:
	/**
	 * @enum DrawingMode
	 * @brief Defines the interaction modes for the scene
	 */
	enum class DrawingMode {
		DrawingMode, ///< Default mode for creating new items
		EditMode ///< Mode for selecting and modifying existing items
	};

	/**
	 * @enum SupportItemItem
	 * @brief The types of drawable shapes supported by the scene
	 */
	enum class SupportItemItem {
		Line, ///< Straight line between two points
		Rect, ///< Rectangle shape
		Ellipse, ///< Ellipse or circle shape
		FreeHand ///< Free-form drawing with mouse movement
	};

	/**
	 * @brief Constructs a SimpleDrawingScene
	 * @param parent The parent QObject (optional)
	 */
	explicit SimpleDrawingScene(QObject* parent = nullptr);

	// Property setters/getters
	/**
	 * @brief Sets the current drawing color
	 * @param color The color to use for new drawings
	 */
	inline void setColor(const QColor& color) { currentColor = color; }

	/**
	 * @brief Gets the current drawing color
	 * @return The current drawing color
	 */
	inline QColor getColor() const { return currentColor; }

	/**
	 * @brief Sets the pen width for drawing
	 * @param penWidth The width in pixels for new drawings
	 */
	inline void setPenWidth(const short penWidth) { this->penWidth = penWidth; }

	/**
	 * @brief Gets the current pen width
	 * @return The current pen width in pixels
	 */
	inline short getPenWidth() const { return penWidth; }

	/**
	 * @brief Sets the current drawing item type
	 * @param i The shape type to create (from SupportItemItem enum)
	 */
	inline void setItemType(const SupportItemItem i) { itemType = i; }

	/**
	 * @brief Sets the interaction mode
	 * @param m The mode to set (from DrawingMode enum)
	 */
	void setMode(const DrawingMode m);

	/**
	 * @brief Exports the current scene as an image
	 * @return QImage containing the rendered scene
	 */
	QImage exportImage();

public slots:
	/**
	 * @brief Undoes the last drawing operation
	 */
	void undo();

	/**
	 * @brief Redoes the last undone operation
	 */
	void redo();

protected:
	/**
	 * @brief Handles mouse press events for drawing
	 */
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

	/**
	 * @brief Handles mouse move events for drawing
	 */
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

	/**
	 * @brief Handles mouse release events for drawing
	 */
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
	/**
	 * @brief Creates a QGraphicsItem based on current settings
	 * @param pen The pen style to use for the item
	 * @return Pointer to the created graphics item
	 */
	QGraphicsItem* create_from_types(QPen& pen);

	/**
	 * @brief Processes drawing during mouse movement
	 * @param currentPos The current mouse position
	 */
	void process_drawing_moving(const QPointF& currentPos);

	/// Current freehand drawing path (for FreeHand mode)
	QPainterPath currentPath;

	/// Pointer to the current path item being drawn
	QGraphicsPathItem* pathItem = nullptr;

	/// Current drawing color
	QColor currentColor;

	/// Current pen width
	short penWidth;

	/// Temporary item during creation
	QGraphicsItem* tempItem { nullptr };

	/// Starting position for shape creation
	QPointF startPos {};

	/// Current interaction mode
	DrawingMode mode { DrawingMode::DrawingMode };

	/// Current shape type to create
	SupportItemItem itemType { SupportItemItem::Line };

	/// Stack of drawn items for undo functionality
	QList<QGraphicsItem*> itemsStack;

	/// Stack of undone items for redo functionality
	QList<QGraphicsItem*> redoStack;
};

#endif // SIMPLEDRAWINGSCENE_H
