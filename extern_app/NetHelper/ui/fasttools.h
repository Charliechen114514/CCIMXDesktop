#ifndef UI_FASTTOOLS_H
#define UI_FASTTOOLS_H
#include <QWidget>
/**
 * @brief hide_childrens fast hide all widgets
 * @param w parent widgets
 */
inline void hide_childrens(QWidget* w) {
	for (const auto& widget : w->children()) {
		QWidget* possible_widget = dynamic_cast<QWidget*>(widget);
		if (!possible_widget)
			continue;
		possible_widget->hide();
	}
}

#endif // UI_FASTTOOLS_H
