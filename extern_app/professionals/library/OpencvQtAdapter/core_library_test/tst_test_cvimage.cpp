#include "core_library/cvimage/CVImage.h"
#include <gtest/gtest.h>
#include <string>

/*
 *  Hello! Developers!
 *  This is a test of the CVImage Library, if you
 *  wrapped your image processing library and using the CVImage
 *  to be your operating frontend, the test file will be the case for you.
 *  Author Charliechen114514 is using OpenCV as the default backend, thus,
 *  if you just wanna test the CVImage library, please make sure you have OpenCV
 *  installed. and can be right-clicked running at once so that the test exe file
 *  can run happily :)
 *      Written in the day with exhausting rain finally went away
 *          on May 8th 2025
 */

using namespace testing;
bool is_valid(const CVImage& img) {
    return img.image_valid();
}

TEST(CVImageTest, InvalidPathHandling) {
	std::string path_empty = std::string(TEST_IMAGE_DIR) + "/"; // Empty path
	CVImage img_empty_path;
	img_empty_path.loadFile(path_empty.c_str());
	EXPECT_FALSE(is_valid(img_empty_path)) << "Empty path should result in invalid image.";

	std::string path_invalid = std::string(TEST_IMAGE_DIR) + "/not_exist_file.png"; // Invalid path
	CVImage img_invalid_path;
	img_invalid_path.loadFile(path_invalid.c_str());
	EXPECT_FALSE(is_valid(img_invalid_path)) << "Non-existent file path should result in invalid image.";
}

TEST(CVImageTest, RepeatedLoading) {
	std::string path_1 = std::string(TEST_IMAGE_DIR) + "/test.png"; // First image
	CVImage img;
	img.loadFile(path_1.c_str());
	EXPECT_TRUE(is_valid(img)) << "First image should be valid.";

	std::string path_2 = std::string(TEST_IMAGE_DIR) + "/test2.png"; // Second image
	img.loadFile(path_2.c_str());
	EXPECT_TRUE(is_valid(img)) << "Second image should still be valid.";
}

TEST(CVImageTest, CopyConstructor) {
	std::string path = std::string(TEST_IMAGE_DIR) + "/test.png"; // Valid image path
	CVImage img_src;
	img_src.loadFile(path.c_str());
	EXPECT_TRUE(is_valid(img_src)) << "Source image should be valid.";

	CVImage img_copy(img_src);
	EXPECT_TRUE(is_valid(img_copy)) << "Copy constructed image should be valid.";
}

TEST(CVImageTest, EmptyImageCopyAndAssign) {
	CVImage img_empty;

	CVImage img_assigned;
	img_assigned = img_empty;
	EXPECT_FALSE(is_valid(img_assigned)) << "Assigned from empty image should be invalid.";

	CVImage img_copy_empty(img_empty);
	EXPECT_FALSE(is_valid(img_copy_empty)) << "Copied from empty image should be invalid.";
}

TEST(CVImageTest, DestructionScope) {
	{
		std::string path = std::string(TEST_IMAGE_DIR) + "/test.png"; // Valid image path
		CVImage img;
		img.loadFile(path.c_str());
		EXPECT_TRUE(is_valid(img)) << "Image inside scoped block should be valid.";
	}
	SUCCEED() << "Image should be destroyed cleanly with no crash or leak.";
}
