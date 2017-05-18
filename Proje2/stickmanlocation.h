#ifndef STICKMANLOCATION_H
#define STICKMANLOCATION_H

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
typedef struct{
    int x;
    int y;
    double angle;
}StickmanAddres_t;

class StickManLocation : public QThread
{
    Q_OBJECT
public:
    StickManLocation(QString ip, int port) {
        this->ip = ip;
        this->port = port;
    }

signals:
    void stickManAddressFounded(StickmanAddres_t addres);

protected:
    void run();
private:
    void readStickMan();
    int port;
    QString ip;
    int dataSocket;
    StickmanAddres_t addres;
};

#endif // STICKMANLOCATION_H
