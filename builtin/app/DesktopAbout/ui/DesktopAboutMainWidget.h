#ifndef DESKTOPABOUTMAINWIDGET_H
#define DESKTOPABOUTMAINWIDGET_H

#include <QWidget>

namespace Ui {
class DesktopAboutMainWidget;
}

class DesktopAboutMainWidget : public QWidget {
	Q_OBJECT
	static constexpr const unsigned short PIX_SZ = 300;

public:
	explicit DesktopAboutMainWidget(QWidget* parent = nullptr);
	void setLogo(const QIcon& icon);
	void setTitle(const QString& title);
	void setDescriptions(const QString& descriptions);
	void setMoreInfo(const QString& info);
	void setVersionString(const QString& version_string);
	~DesktopAboutMainWidget();

private:
	Ui::DesktopAboutMainWidget* ui;
};

#endif // DESKTOPABOUTMAINWIDGET_H
