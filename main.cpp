#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(800, 600);
    w.setWindowTitle("Smart parking");
    w.show();
    return a.exec();
}