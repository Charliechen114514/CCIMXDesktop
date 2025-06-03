/**
 * @class CactusObsticals
 * @brief Represents cactus-type obstacles with variable size and rendering support.
 */

#ifndef CACTUSOBSTICALS_H
#define CACTUSOBSTICALS_H
#include "Obsticals.h"

/**
 * @brief CactusObsticals inherits from Obsticals and provides size and rendering control.
 */
class CactusObsticals : public Obsticals {
    Q_OBJECT
public:
	/**
	 * @brief Constructor for CactusObsticals.
	 * @param parent The parent QObject, default is nullptr.
	 */
	explicit CactusObsticals(QObject* parent = nullptr);

	/**
	 * @brief Default destructor.
	 */
	~CactusObsticals() = default;

	/**
	 * @brief Enumeration for cactus size types.
	 */
	enum class Size {
		SMALL, ///< Small size
		MEDIUM, ///< Medium size
		LARGE ///< Large size
	};

	/**
	 * @brief Constant representing the number of size types.
	 */
	static constexpr const short SIZE_TYPE_MAX = static_cast<short>(Size::LARGE) + 1;

	/**
	 * @brief Sets the cactus size.
	 * @param s The size to be set.
	 */
	void setSize(Size s);

	/**
	 * @brief Returns the current size of the cactus.
	 * @return The current size.
	 */
	Size getSize() const { return size; }

	/**
	 * @brief Enables or disables automatic random size update.
	 * @param st Boolean flag to enable or disable.
	 */
	void inline setAutoUpdateSzRandomly(bool st) { auto_update_sz = st; }

	/**
	 * @brief Checks if automatic random size update is enabled.
	 * @return True if enabled, false otherwise.
	 */
	inline bool autoUpdateSzRandomly() const { return auto_update_sz; }

	/**
	 * @brief Provides the current bounding rectangle of the cactus.
	 * @return Reference to the QRect representing the bounding box.
	 */
	QRect& provide_current_bounding_rect() override;

	/**
	 * @brief Provides the drawing source frame (QPixmap) for the cactus.
	 * @return Reference to the QPixmap to be drawn.
	 */
	QPixmap& provide_drawing_srcframe() override;

private:
	/**
	 * @brief Pointer to the cactus frame provider for rendering.
	 */
	CactusFrameFetch* cactus_frame_provider;

	/**
	 * @brief Current size of the cactus.
	 */
	Size size;

	/**
	 * @brief Flag indicating whether size is updated randomly.
	 */
	bool auto_update_sz { false };

	/**
	 * @brief Initializes internal memory/resources.
	 */
	void init_memory();

	/**
	 * @brief Updates the current drawing frame of the cactus.
	 */
	void update_frame();
};

#endif // CACTUSOBSTICALS_H
