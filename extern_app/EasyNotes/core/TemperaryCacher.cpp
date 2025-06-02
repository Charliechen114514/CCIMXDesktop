#include "TemperaryCacher.h"

void TemperaryCacher::ensub_labels(const QString& label, const QString& text) {
	label_context_map[label] = text;
}

void TemperaryCacher::remove_label(const QString& label) {
	label_context_map.remove(label);
}

std::optional<QString> TemperaryCacher::query(const QString& label) {
	auto it = label_context_map.find(label);
	if (it == label_context_map.cend()) {
		return std::nullopt;
	} else {
		return { *it };
	}
}
