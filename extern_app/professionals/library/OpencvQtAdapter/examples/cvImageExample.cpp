#include "core_library/cvimage/CVImage.h"
#include "core_library/cvimage/CVTools.h"
#include <iostream>
#define DEF_IMAGE TEST_IMAGE_DIR "/test.png"
int main(int argc, char* argv[]) {
	const char* image_path = nullptr;
	if (argc < 2) {
		std::cout << "Provide less then 2 args, using default image" << std::endl;
		image_path = DEF_IMAGE;
	} else {
		image_path = argv[1];
	}

	CVImage image;
	image.loadFile(image_path);

	if (!image.image_valid()) {
		std::cerr << "Invalid image data!" << std::endl;
		return 3;
	}

	std::cout << "Press any key can quit the display!";
	CVTools::display(image, "Charlies CVImage");
	return 0;
}
