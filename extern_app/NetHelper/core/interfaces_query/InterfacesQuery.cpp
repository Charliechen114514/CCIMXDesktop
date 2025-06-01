#include "InterfacesQuery.h"
#include <QTimer>
#include <ranges>
InterfacesQuery::InterfacesQuery(QObject* parent)
	: QObject { parent } {
	setup_memory();
	timer->start();
}

std::optional<QNetworkInterface> InterfacesQuery::from_name_query(const QString& readable_name) const {
	auto result = std::find_if(
		cached_interfaces.cbegin(), cached_interfaces.cend(), [readable_name](const QNetworkInterface& a) {
			return a.humanReadableName() == readable_name;
		});

	if (result == cached_interfaces.cend()) {
		return std::nullopt;
	} else {
		return { *result };
	}
}

void InterfacesQuery::setup_memory() {
	timer = new QTimer(this);
	timer->setInterval(TIMELY_SCAN_S * 1000);
	connect(timer, &QTimer::timeout, this, &InterfacesQuery::process_query);
}

void InterfacesQuery::process_query() {
	cached_interfaces = QNetworkInterface::allInterfaces();
	QStringList names;
	for (const auto& iface : cached_interfaces | std::views::transform(&QNetworkInterface::humanReadableName)) {
		names << iface;
	}
	emit network_query_display(names);
}
