#ifndef WALLPAPERANIMATIONHANDLER_H
#define WALLPAPERANIMATIONHANDLER_H

#include <QObject>
#include <QStringList>
#include "desktopmainwindow.h"
#include <functional>

/* this class is expected to do the wallpaper switch */
struct WallPaperAnimationHandler : public QObject
{
    Q_OBJECT
public:
    explicit WallPaperAnimationHandler(QObject *parent = nullptr);

    struct ImagePoolEngine{
        QStringList*     image_list{nullptr}; /* tells where to select */
        std::function<int(QStringList*)>    selector{nullptr};
    };

    /* filling the blank and make process */
    static void process_switch(
        const DesktopMainWindow::WallPaperGroup& group,
        ImagePoolEngine& engine);
};

#endif // WALLPAPERANIMATIONHANDLER_H
