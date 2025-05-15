#include "AP3216CAdapterFactory.h"

AP3216CAdapterFactory::AP3216CAdapterFactory(QObject* parent)
	: QObject { parent } {
	connect(this, &AP3216CAdapterFactory::__internal_async_request,
			this, &AP3216CAdapterFactory::process_request);
}

bool AP3216CAdapterFactory::bind_file(const QString& file_path) {
	return adapter.bind_file(file_path.toStdString());
}

void AP3216CAdapterFactory::request_data() {
	emit __internal_async_request();
}

std::optional<AP3216CData> AP3216CAdapterFactory::sync_request_data() {
	return adapter.sync_read_once();
}

void AP3216CAdapterFactory::process_request() {
	std::optional<AP3216CData> data = sync_request_data();
	if (data.has_value()) {
		emit request_finish(data.value());
	} else {
		emit request_error();
	}
}
