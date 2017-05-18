#ifndef FRAMESTREAMERTHREAD_H
#define FRAMESTREAMERTHREAD_H

#include <QThread>
#include <opencv2/opencv.hpp>
#include "ui_mainwindow.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <QApplication>

using namespace cv;
using namespace std;

class FrameStreamerWorker : public QThread
{
    Q_OBJECT
public:
    FrameStreamerWorker(QString ip, int port) {
        this->ip = ip;
        this->port = port;
    }

signals:
    void frameAcquired(cv::Mat frame);

protected:
    void run();


private:
    void readFrameSize();
    void readFrameData();
    Mat frame;
    int port;
    QString ip;
    int dataSocket;
    int dataSizeSocket;
    int frameSize = 0;
    char frameSizeBuffer[128];
    char* frameDataBuffer;
};

#endif // FRAMESTREAMERTHREAD_H
