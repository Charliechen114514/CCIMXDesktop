#ifndef CAMERADEVICESELECTOR_H
#define CAMERADEVICESELECTOR_H
#include <QList>
#include <QtClassHelperMacros>
/* We need to refer the max available devices */

class CameraDeviceSelector {
public:
	static constexpr const int MAX_CAMERA_SCAN = 5;
	CameraDeviceSelector() = default;
	Q_DISABLE_COPY(CameraDeviceSelector);
	static QList<int> scan_available_cameras(const int& start_index = 0);
	static QList<QString> scan_available_camerasnames(const int& start_index = 0);
};

#endif // CAMERADEVICESELECTOR_H
