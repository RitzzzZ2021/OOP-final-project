#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <include/infomanager.h>
#include <include/editmanager.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*应用样式表*/
    QString qss;
    QFile qssFile(":/Ubuntu.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }

    MainWindow w;
    w.show();

    return a.exec();
}
