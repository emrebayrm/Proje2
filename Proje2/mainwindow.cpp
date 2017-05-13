#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QImage logo("./gtuLogo500.png");
    ui->gtuLogo->setPixmap(QPixmap::fromImage(logo.scaled(201,111)));

//    vid = new cv::VideoCapture(0);
    setWindowTitle(tr("Proje 2"));
    isRunning = false;
    QTimer *timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(stopWatch()));
    timer->start(1);

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
        StartTime = QDateTime::currentDateTime();
        isRunning = true;
        QString ip =  ui->ipText->text();
        QString port = ui->PortText->text();
        ui->MessageBox->append("Connecting ...");
        ui->MessageBox->append("Ip : " + ip);
        ui->MessageBox->append("Port number " + port);

        socket = new QTcpSocket(this);

        connect(socket,SIGNAL(readyRead()),this,SLOT(ReadTcpData()));

        socket->connectToHost(ip,port.toInt());
        socket->waitForConnected();
        if(socket->state() == socket->ConnectedState)
            ui->MessageBox->append("Connected ");
    }

}

void MainWindow::stop()
{
    isRunning = false;
    socket->close();
}


void MainWindow::ReadTcpData()
{
    qint64 ret;
    if(dataSize == 0){
        socket->read((char *)&dataSize,sizeof(int));
        std::cerr << dataSize;
        dataTcp= new uchar[dataSize];
    }
    std::cerr <<"Readed :: " << (int)(ret = socket->read((char *)dataTcp,dataSize)) << std::endl;
    char dead = 'N';
    socket->write((char *)&dead);
    if(ret == dataSize){
        cv::Mat frame(540,960,CV_8U,dataTcp);
        cv::imshow("asd",frame);
        QImage image(frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888);
        //image = QImage::fromData(dataTcp,QImage::Format_BGR30);

    /*        cv::Mat frame;
    (*vid) >> frame;
    cv::cvtColor(frame,frame,CV_BGR2RGB);
    QImage image(frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888);
    */
        image.scaledToHeight(480);
        image.scaledToWidth(640);

        QPixmap pixmap = QPixmap::fromImage(image);
        QGraphicsScene *scene = new QGraphicsScene(this);
        scene->addPixmap(pixmap);
        scene->setSceneRect(pixmap.rect());
        ui->Camera->setScene(scene);
    }
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
        //TODO: Network
    }
}
