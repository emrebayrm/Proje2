#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QtNetwork/QTcpSocket>
#include "framestreamerthread.h"
#include "stickmanlocation.h"

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
    void updateFrame(cv::Mat frame);
    void stickManFounded(StickmanAddres_t addr);
private:
    bool isDataReady =false;
    bool isRunning;
    FrameStreamerWorker *frameStreamerWorker;
    StickManLocation *stickmanLocaterTh;
    Ui::MainWindow *ui;
    QDateTime StartTime;
    cv::VideoCapture *vid;
    QGraphicsScene *scene;
};


#endif // MAINWINDOW_H
