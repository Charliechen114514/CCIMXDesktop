#include "CameraDeviceSelector.h"
#include <opencv.hpp>

QList<int> CameraDeviceSelector::scan_available_cameras(const int& start_index) {
	QList<int> result;
	for (int cur = start_index; cur <= start_index + MAX_CAMERA_SCAN; cur++) {
		cv::VideoCapture test(cur);
		if (test.isOpened()) {
			test.release();
			result << cur;
		}
	}
	return result;
}

QList<QString> CameraDeviceSelector::scan_available_camerasnames(const int& start_index) {
	QList<QString> result;
	for (int cur = start_index; cur <= start_index + MAX_CAMERA_SCAN; cur++) {
		cv::VideoCapture test(cur);
		if (test.isOpened()) {
			test.release();
			result << QString::number(cur);
		}
	}
	return result;
}
