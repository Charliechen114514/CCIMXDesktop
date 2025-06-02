#ifndef LEFTSIDEBAR_H
#define LEFTSIDEBAR_H
class TemperaryCacher;
#include <QWidget>

namespace Ui {
class LeftSideBar;
}

/**
 * @brief LeftSideBar is the left widget displays
 * 
 */
class LeftSideBar : public QWidget {
	Q_OBJECT

public:
	/**
	 * @brief Construct a new Left Side Bar object
	 * 
	 * @param parent 
	 */
	explicit LeftSideBar(QWidget* parent = nullptr);
	~LeftSideBar();
	QStringList temp_lables() const; ///< temp labels holdings
public slots:
	/**
	 * @brief slots for the en-managing the history
	 * 
	 * @param file 
	 */
	void enqueue_history_file(const QString& file);
	/**
	 * @brief slots for holding a temperary info
	 * 
	 * @param label label
	 * @param context markdown context
	 */
	void entemp(const QString& label, const QString& context);
	/**
	 * @brief remove a temp
	 * 
	 * @param label 
	 */
	void remove_temp(const QString& label);
	/**
	 * @brief query a temp sessions
	 * 
	 * @param label 
	 * @return std::optional<QString> 
	 */
	std::optional<QString> show_temp(const QString& label);
signals:
	/**
	 * @brief file request
	 * 
	 * @param file 
	 */
	void load_file(const QString file);
	/**
	 * @brief temp request
	 * 
	 * @param label 
	 */
	void load_temp(const QString label);

private slots:
	/**
	 * @brief btn clear hooks
	 * 
	 */
	void on_btn_clear_temp_clicked();
	/**
	 * @brief btn delete hooks
	 * 
	 */
	void on_btn_delete_clicked();

private:
	Ui::LeftSideBar* ui; ///< ui handle

	/* History Parts */
	QStringList history_file; ///< history file name list
	void updateHistoryList(); ///< this will update the history widget lists

	/* Temp part */
	TemperaryCacher* cacher; ///< tep cacher

	/**
	 * @brief init_connections setup the connections in the sidebar
	 */
	void init_connections();

	void update_templist(); ///< update the templist
};

#endif // LEFTSIDEBAR_H
