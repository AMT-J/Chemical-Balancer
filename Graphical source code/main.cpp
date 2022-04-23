#include "mainwindow.h"
#include <QApplication>
#include <windows.h>
int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    qreal  cx = GetSystemMetrics(SM_CXSCREEN);
    qreal scale = cx/1920*1.25;
    if (scale < 1)
        scale=1.0;
    qputenv("QT_SCALE_FACTOR", QString::number(scale).toLatin1());
    //QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
