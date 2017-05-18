#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    qRegisterMetaType<cv::Mat>("cv::Mat");
    w.show();

    return a.exec();
}
