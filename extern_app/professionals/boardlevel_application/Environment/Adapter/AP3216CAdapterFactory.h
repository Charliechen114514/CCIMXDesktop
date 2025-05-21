#ifndef AP3216CADAPTERFACTORY_H
#define AP3216CADAPTERFACTORY_H

#include "ap3216c.h"
#include <QObject>

#ifdef USE_REAL_ADAPTER
#include "ap3216c_adapter.h"
#else
#include "PesudoAP3216C.h"
#endif

/// @class AP3216CAdapterFactory
/// @brief Provides an abstraction layer to request sensor data from AP3216C.
/// @note Supports real and pseudo backends depending on the build configuration.
class AP3216CAdapterFactory : public QObject {
	Q_OBJECT

public:
	/// @brief Constructor.
	explicit AP3216CAdapterFactory(QObject* parent = nullptr);

	/// @brief Binds to a device file path.
	/// @param file_path Device file path.
	/// @return True if successfully bound, false otherwise.
	bool bind_file(const QString& file_path);

	/// @brief Triggers an asynchronous data request.
	void request_data();

	/// @brief Performs a synchronous data request.
	/// @return Optional sensor data, empty if reading fails.
	std::optional<AP3216CData> sync_request_data();

signals:
	/// @brief Emitted when data is successfully read.
	/// @param data The sensor data.
	void request_finish(const AP3216CData data);

	/// @brief Emitted when there is an error reading data.
	void request_error();

	/// @brief Internal signal for triggering the asynchronous request.
	void __internal_async_request();

private slots:
	/// @brief Slot to handle internal asynchronous requests.
	void process_request();

private:
#ifdef USE_REAL_ADAPTER
	AP3216CAdapter adapter; ///< Adapter for the real AP3216C device.
#else
	PesudoAP3216C adapter; ///< Pseudo device adapter that generates random data.
#endif
};

#endif // AP3216CADAPTERFACTORY_H
