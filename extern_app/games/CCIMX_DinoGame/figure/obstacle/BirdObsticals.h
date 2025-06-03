#ifndef BIRDOBSTICALS_H
#define BIRDOBSTICALS_H

#include "Obsticals.h"

class BirdFrameFetch;

/**
 * @class BirdObsticals
 * @brief Represents bird obstacles in the game
 */
class BirdObsticals : public Obsticals {
    Q_OBJECT
public:
	/**
	 * @enum FlyHeight
	 * @brief Possible flying heights for birds
	 */
	enum class FlyHeight {
		LOW, ///< Low flying height
		MED, ///< Medium flying height
		HIG ///< High flying height
	};

	/**
	 * @enum BirdType
	 * @brief Possible sizes for birds
	 */
	enum class BirdType {
		SMALL, ///< Small bird size
		MEDIUM, ///< Medium bird size
		LARGE ///< Large bird size
	};

	/// Maximum number of height types
	static constexpr unsigned short HEIGHT_SIZE_TYPE_MAX = static_cast<unsigned short>(FlyHeight::HIG) + 1;

	/// Maximum number of size types
	static constexpr unsigned short SZ_SIZE_TYPE_MAX = static_cast<unsigned short>(BirdType::LARGE) + 1;

	/**
	 * @brief Constructs a BirdObsticals object
	 * @param parent Parent QObject
	 */
	explicit BirdObsticals(QObject* parent = nullptr);

	/**
	 * @brief Sets flying height
	 * @param h Desired flying height
	 */
	void setHeight(FlyHeight h);

	/**
	 * @brief Gets current flying height
	 * @return Current FlyHeight
	 */
	FlyHeight getHeight() const { return h; }

	/**
	 * @brief Sets bird size
	 * @param t Desired bird size
	 */
	void setSize(BirdType t);

	/**
	 * @brief Gets current bird size
	 * @return Current BirdType
	 */
	BirdType getSize() const { return type; }

	/**
	 * @brief Enables/disables automatic height updates
	 * @param st True to enable auto-update
	 */
	void inline setAutoUpdateHeightRandomly(bool st) { auto_update_height = st; }

	/**
	 * @brief Checks if height auto-update is enabled
	 * @return True if auto-update is enabled
	 */
	inline bool autoheightUpdateSzRandomly() const { return auto_update_height; }

	/**
	 * @brief Enables/disables automatic size updates
	 * @param st True to enable auto-update
	 */
	void inline setAutoUpdateSzRandomly(bool st) { auto_update_size = st; }

	/**
	 * @brief Checks if size auto-update is enabled
	 * @return True if auto-update is enabled
	 */
	inline bool autoUpdateSzRandomly() const { return auto_update_size; }

	/// Default destructor
	~BirdObsticals() = default;

	/**
	 * @brief Provides current collision bounding rect
	 * @return Reference to current QRect
	 */
	QRect& provide_current_bounding_rect() override;

	/**
	 * @brief Provides current drawing frame
	 * @return Reference to current QPixmap
	 */
	QPixmap& provide_drawing_srcframe() override;

private:
	bool auto_update_height { true }; ///< Auto-update height flag
	bool auto_update_size { true }; ///< Auto-update size flag
	BirdFrameFetch* bird_frame_provider; ///< Frame provider for bird animation
	FlyHeight h { FlyHeight::LOW }; ///< Current flying height
	BirdType type { BirdType::SMALL }; ///< Current bird size

	/**
	 * @brief Initializes resources
	 */
	void init_memory();

	/**
	 * @brief Updates current animation frame
	 */
	void update_frame();
};

#endif // BIRDOBSTICALS_H
