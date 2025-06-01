#ifndef TOOLBOXS_H
#define TOOLBOXS_H

#include <QWidget>

namespace Ui {
class ToolBoxs;
}

/**
 * @brief The ToolBoxs class
 */
class ToolBoxs : public QWidget {
	Q_OBJECT

public:
	/**
	 * @brief The ShowType enum
	 */
	enum class ShowType {
		PINGER, ///< pinger
		SCANNER, ///< scanner
		INTERFACES ///< show interfaces
	};
	/**
	 * @brief ToolBoxs
	 * @param parent
	 */
	explicit ToolBoxs(QWidget* parent = nullptr);
	~ToolBoxs();

signals:
	/**
	 * @brief indicate_show oh, show what?
	 * @param type
	 */
	void indicate_show(const ShowType type);

private:
	Ui::ToolBoxs* ui; ///< ui handle
	/**
	 * @brief setup_connections
	 */
	void setup_connections();
};

#endif // TOOLBOXS_H
