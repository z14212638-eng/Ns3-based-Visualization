#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    // 开启高 DPI 自适应
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication a(argc, argv);

    QFile f(":/qss/dark.qss");  
    // QFile f("qss/dark.qss"); 

    if (f.open(QFile::ReadOnly))
    {
        a.setStyleSheet(f.readAll());
        f.close();
    }

    MainWindow w;
    w.show();

    return a.exec();
}
