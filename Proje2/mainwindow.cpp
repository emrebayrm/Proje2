#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vid = new cv::VideoCapture(0);
    setWindowTitle(tr("Proje 2"));
    isRunning = false;
    QTimer *timer = new QTimer(this);
    QTimer *videoTimer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(stopWatch()));
    timer->start(1);

    connect(videoTimer, SIGNAL(timeout()),this,SLOT(UpdateFrame()));
    videoTimer->start(1);

    connect( ui->Connect, SIGNAL( clicked() ), this, SLOT( start() ) );
    connect( ui->stop, SIGNAL( clicked() ), this, SLOT( stop() ) );
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::start()
{
    if(!isRunning){
        statusBar()->showMessage("message");
        StartTime = QDateTime::currentDateTime();
        isRunning = true;
    }
    else{
        QString ip =  ui->ipText->text();
        QString port = ui->PortText->text();
        socket = new QTcpSocket(this);
        connect(socket,SIGNAL(readyRead()),this,SLOT(ReadTcpData()));

        socket->connectToHost(ip,port.toInt());
        socket->waitForConnected();
    }
}

void MainWindow::stop()
{
    isRunning = false;
}

void MainWindow::UpdateFrame()
{
    if(isRunning){
/*        QImage image;
        QPixmap pixmap;
        if(isDataReady){
            img = QImage.fromData(dataTcp,QImage::Format_RGB888);
            isDataReady = false;
        }
*/
        cv::Mat frame;
        (*vid) >> frame;
        cv::cvtColor(frame,frame,CV_BGR2RGB);
        QImage image(frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888);
        image.scaledToHeight(480);
        image.scaledToWidth(640);

        QPixmap pixmap = QPixmap::fromImage(image);
        QGraphicsScene *scene = new QGraphicsScene(this);
        scene->addPixmap(pixmap);
        scene->setSceneRect(pixmap.rect());
        ui->Camera->setScene(scene);
    }
}

void MainWindow::ReadTcpData()
{
    dataTcp = socket->readAll();
    isDataReady = true;
}

void MainWindow::stopWatch()
{
    QString diff;
    if(isRunning)
    {
        qint64 ms = StartTime.msecsTo(QDateTime::currentDateTime());
        int h = ms / 1000 / 60 / 60;
        int m = (ms / 1000 / 60) - (h * 60);
        int s = (ms / 1000) - (m * 60);
        ms = ms - (s * 1000);
        ms = ms / 10;
        if(ms  < 10)
           diff = QString("%1:%2:%3:0%4").arg(h).arg(m).arg(s).arg(ms);
        else
           diff = QString("%1:%2:%3:%4").arg(h).arg(m).arg(s).arg(ms);
        ui->stopWatch->setText(diff);
        socket->close();
    }
}
