#ifndef APPWIDGET_H
#define APPWIDGET_H
#include <QIcon>
#include <QWidget>
class ApplicationWrapper;
namespace Ui {
class AppWidget;
}

/**
 * @brief The AppWidget class is the AppWidgets placing in the
 * desktop.
 */
class AppWidget : public QWidget {
    Q_OBJECT

public:
	explicit AppWidget(const QPixmap& icon, const QString& name, QWidget* parent = nullptr);
	void bindApp(ApplicationWrapper* wrapper) { this->app_internal = wrapper; }
	ApplicationWrapper* get_app() const { return this->app_internal; }
	void setIcon(const QPixmap& icon) noexcept;
	void setAppName(const QString& name) noexcept;

	/**
	 * @brief setDummy set the app visible only, and don't make any senses
	 * this will disable any possible real interactive of the depatchings
	 * @param dummy
	 */
	void setDummy(bool dummy);
	QPixmap icon() const;
	void showIconOnly(bool st);
	QString app_name() const;
	~AppWidget();

	enum class AppStatus {
		AppOk,
		AppNonExsits
	};

signals:
	void postAppStatus(AppWidget::AppStatus status);

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;

private:
	Ui::AppWidget* ui;
	bool dummy_state { false };
	ApplicationWrapper* app_internal { nullptr };
	/**
	 * @brief do_daptch. depatch the app wrappers
	 */
	void do_daptch();
};

#endif // APPWIDGET_H
