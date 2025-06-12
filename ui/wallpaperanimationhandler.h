#ifndef WALLPAPERANIMATIONHANDLER_H
#define WALLPAPERANIMATIONHANDLER_H

#include "desktopmainwindow.h"
#include <QObject>
#include <QStringList>
#include <functional>

/* this class is expected to do the wallpaper switch */

/**
 * @brief The WallPaperAnimationHandler class is the animation holder
 * for the wallpaper, it is used to animate the wallpaper switching
 */
struct WallPaperAnimationHandler : public QObject {
    Q_OBJECT
public:
	/**
	 * @brief Construct a new Wall Paper Animation Handler object
     *
     * @param parent
	 */
    explicit WallPaperAnimationHandler(QObject* parent = nullptr);

	/**
	 * @brief The ImagePoolEngine class makes a image selection
	 * as an engine, WallPaperAnimationHandler requires the engine to
	 * make the wallpaper switch(that is, select with how to select the
	 * image for display)
	 */
	struct ImagePoolEngine {
		QStringList* image_list { nullptr }; ///< image list of the src
		/**
		 * @brief selector make sense in deciding how to select from the
		 * image list, if not set, then it will be random as default issue
		 */
		std::function<int(QStringList*)> selector { nullptr };
        /**
         * @brief default_selections makes the default random selections
         * @param list the list pool of selectings
         * @return the selected images
         */
        static QString default_selections(const QStringList& list);
        /**
         * @brief default_index makes the default random selections
         * @param list the list pool of selectings
         * @return the index offset of the list
         */
        static int default_index(const QStringList& list);
    };

	/**
	 * @brief process_switch makes the real switch async, invoke this
	 * for the real switching.
	 * @param group WallPaperGroup from MainWindow
	 * @param engine the engine switching requires
	 */
	static void process_switch(
        const WallPaperEngine* group,
        ImagePoolEngine& engine);
};

#endif // WALLPAPERANIMATIONHANDLER_H
