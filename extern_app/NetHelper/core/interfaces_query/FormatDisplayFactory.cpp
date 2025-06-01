#include "FormatDisplayFactory.h"
#include <QNetworkInterface>
namespace {
QString from_type(const QNetworkInterface::InterfaceType iface) {
	QString typeStr;
	switch (iface) {
	case QNetworkInterface::InterfaceType::Unknown:
		typeStr = "Unknown";
		break;
	case QNetworkInterface::InterfaceType::Ethernet:
		typeStr = "Ethernet";
		break;
	case QNetworkInterface::InterfaceType::Virtual:
		typeStr = "Virtual";
		break;
	case QNetworkInterface::InterfaceType::Loopback:
		typeStr = "Loopback";
		break;
	case QNetworkInterface::InterfaceType::Wifi:
		typeStr = "Wifi";
		break;
	default:
		typeStr = "Others";
		break;
	}
	return typeStr;
}

QString status_strings(const QFlags<QNetworkInterface::InterfaceFlag>& flags) {
	QString statusStr;
	statusStr += flags.testFlag(QNetworkInterface::IsUp) ? "Up " : "Down ";
	statusStr += flags.testFlag(QNetworkInterface::IsRunning) ? "Running " : "";
	statusStr += flags.testFlag(QNetworkInterface::CanBroadcast) ? "Broadcast " : "";
	statusStr += flags.testFlag(QNetworkInterface::IsLoopBack) ? "Loopback " : "";
	statusStr += flags.testFlag(QNetworkInterface::IsPointToPoint) ? "PointToPoint " : "";
	statusStr += flags.testFlag(QNetworkInterface::CanMulticast) ? "Multicast " : "";
	return statusStr;
}

QStringList entries_string(const QNetworkInterface& interface) {
	QString ipAddresses;
	QString netmasks;
	QString broadcasts;
	for (const QNetworkAddressEntry& entry : interface.addressEntries()) {
		ipAddresses += entry.ip().toString() + "\n";
		netmasks += entry.netmask().toString() + "\n";
		broadcasts += entry.broadcast().toString() + "\n";
	}

	QStringList result;
	result << ipAddresses << netmasks << broadcasts;
	return result;
}

}

QList<QPair<FormatDisplayFactory::Property,
			FormatDisplayFactory::Value>>
FormatDisplayFactory::details(const QNetworkInterface& interface) {
	QList<QPair<Property,
				Value>>
		result;
	auto entry_result_strings = entries_string(interface);
	result << QPair("Interface Name", interface.name())
		   << QPair("MAC Address", interface.hardwareAddress())
		   << QPair("Type", from_type(interface.type()))
		   << QPair("Status", status_strings(interface.flags()))
		   << QPair("ip list", entry_result_strings[0])
		   << QPair("netmasks", entry_result_strings[1])
		   << QPair("broadcasts", entry_result_strings[2]);
	return result;
}
