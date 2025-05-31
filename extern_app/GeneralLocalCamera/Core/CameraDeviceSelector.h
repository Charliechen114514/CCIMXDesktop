#ifndef CAMERADEVICESELECTOR_H
#define CAMERADEVICESELECTOR_H

#include <QList>
#include <QString>
#include <QtClassHelperMacros>

/**
 * @brief The CameraDeviceSelector class provides camera scanning utilities.
 */
class CameraDeviceSelector {
public:
	/**
	 * @brief max camera enums times
	 */
	static constexpr int MAX_CAMERA_SCAN = 5;
	/**
	 * @brief def constructor
	 */
	CameraDeviceSelector() = default;

	/**
	 * @brief Q_DISABLE_COPY disables copy constructor and assignment operator.
	 */
	Q_DISABLE_COPY(CameraDeviceSelector);

	/**
	 * @brief scan_available_cameras scans available camera indices.
	 * @param start_index Starting index for scanning. Default is 0.
	 * @return List of available camera indices.
	 */
	static QList<int> scan_available_cameras(int start_index = 0);

	/**
	 * @brief scan_available_camerasnames scans available camera names.
	 * @param start_index Starting index for scanning. Default is 0.
	 * @return List of available camera names.
	 */
	static QList<QString> scan_available_camerasnames(int start_index = 0);
};

#endif // CAMERADEVICESELECTOR_H
