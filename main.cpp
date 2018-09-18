

#include <QtWidgets/QApplication>
#include <QFile>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication qapp(argc, argv);

    QFile file("resources/stylesheet.qss");
    if (file.open(QFile::ReadOnly)) {
        QString sheet = QLatin1String(file.readAll());
        qDebug() << qPrintable(sheet);
        qapp.setStyleSheet(sheet);
    }
    MainWindow w;
    w.show();
    return qapp.exec();
}
