#ifndef INTERFACESQUERY_H
#define INTERFACESQUERY_H
#include <QNetworkInterface>
#include <QObject>
class QTimer;
class InterfacesQuery : public QObject {
	Q_OBJECT
	static constexpr const unsigned short TIMELY_SCAN_S = 1; ///< peroid of scan

public:
	/**
	 * @brief InterfacesQuery creator
	 * @param parent
	 */
	explicit InterfacesQuery(QObject* parent = nullptr);
	/**
	 * @brief interfaces_cached returns the sync query of the netcard interfaces
	 * @return cached_interfaces
	 */
	const QList<QNetworkInterface>& interfaces_cached() const { return cached_interfaces; }

	/**
	 * @brief from_name_query query from the network card readable name, using in select
	 * list widgets
	 * @param readable_name
	 * @return
	 */
	std::optional<QNetworkInterface> from_name_query(const QString& readable_name) const;

signals:
	/**
	 * @brief network_query_display is just the signals
	 * @param interfaces queried underlevel
	 */
	void network_query_display(const QStringList interfaces);

private:
	QTimer* timer; ///< timely timer
	QList<QNetworkInterface> cached_interfaces; ///< cached interfaces
	void setup_memory(); ///< setup memory issue
	void process_query(); ///< impl for the real query
};

#endif // INTERFACESQUERY_H
