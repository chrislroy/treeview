

#include <QtWidgets/QApplication>
#include <QFile>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication qapp(argc, argv);

    QFile File("stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    qapp.setStyleSheet(StyleSheet);
    MainWindow w;
    w.show();
    return qapp.exec();
}
