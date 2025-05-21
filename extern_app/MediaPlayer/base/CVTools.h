#ifndef CVTOOLS_H
#define CVTOOLS_H
#include "CVImage.h"
#include <utility>
/* CVTools make sense in debuging */

/**
 * @brief The CVTools namespace provides the tools
 * @note Most of the implementations, for management
 * reason, are supposed to place in the impl
 * files, instead of the current cpp file
 */
namespace CVTools {

/**
 * @brief WAIT_FOREVER is the default wait time
 */
static constexpr const short WAIT_FOREVER = 0;

/**
 * @brief The DisplayParams struct provides the display
 * parameters for the display
 */
struct DisplayParams {
	const char* name { nullptr }; ///< the display name for window
	std::pair<int, int> window_size { 640, 480 }; ///< the window size
	int waitTime { WAIT_FOREVER }; ///< default we wait forever
};

/**
 * @brief display the image with the default parameters
 * @param image the image to display
 * @param name the window name
 * @note this will use the default parameters
 */
void display(const CVImage& image, const char* name);

/**
 * @brief display the image with the default parameters
 * @param image the image to display
 * @param params the display parameters
 */
void display(const CVImage& image, const DisplayParams& params);

};

#endif // CVTOOLS_H
