#include "CVTools.h"

void CVTools::display(const CVImage& image, const char* name) {
	DisplayParams params;
	params.name = name;
	return display(image, params);
}
