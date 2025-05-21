#ifndef CVTOOLS_H
#define CVTOOLS_H
#include "CVImage.h"
#include <utility>
/* CVTools make sense in debuging */

/* Most of the implementations, for management
 * reason, are supposed to place in the impl
 * files, instead of the current cpp file
 */
namespace CVTools {

static constexpr const short WAIT_FOREVER = 0;

struct DisplayParams {
	const char* name { nullptr };
	std::pair<int, int> window_size { 640, 480 };
	int waitTime { WAIT_FOREVER }; /* default we wait forever */
};

/* using the default display issue make sense */
void display(const CVImage& image, const char* name);

/* display impl should be in private impl file */
void display(const CVImage& image, const DisplayParams& params);

};

#endif // CVTOOLS_H
