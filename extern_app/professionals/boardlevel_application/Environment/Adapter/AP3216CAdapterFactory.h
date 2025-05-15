#ifndef AP3216CADAPTERFACTORY_H
#define AP3216CADAPTERFACTORY_H
#include "ap3216c.h"
#include <QObject>
#ifdef USE_REAL_ADAPTER
#include "ap3216c_adapter.h"
#else
#include "PesudoAP3216C.h"
#endif

/*
 * This factory Class really handle the Data Factorize
 * which, you should query the AP3216CAdapterFactory
 * for the data instead of direct hook, which enabled
 * no matter platformed fetch of datas
 */
class AP3216CAdapterFactory : public QObject {
	Q_OBJECT
public:
	explicit AP3216CAdapterFactory(QObject* parent = nullptr);
	/* default we provide pesudos */
	bool bind_file(const QString& file_path);
	/* invoke this for the Data */
	void request_data();
	/* or request sync */
	std::optional<AP3216CData> sync_request_data();
signals:
	/* async request */
	void request_finish(const AP3216CData data);
	/* error for the request */
	void request_error();
	/* internal async */
	void __internal_async_request();
private slots:
	void process_request();

private:
#ifdef USE_REAL_ADAPTER
	AP3216CAdapter
#else
	PesudoAP3216C
#endif
		adapter;
};

#endif // AP3216CADAPTERFACTORY_H
