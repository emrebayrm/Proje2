#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QtNetwork/QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void stopWatch();
    void start();
    void stop();
    void ReadTcpData();

private:
    int dataSize = 0;
    uchar* dataTcp;
    cv::VideoCapture *vid;
    bool isDataReady =false;
    QTcpSocket *socket;
    Ui::MainWindow *ui;
    bool isRunning;
    QDateTime StartTime;

};


#endif // MAINWINDOW_H
