#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    timer->start(1);

    connect(timer, SIGNAL(timeout()), this, SLOT(stopWatch()));
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

        frameStreamerWorker = new FrameStreamerWorker(ip,port.toInt());
        connect(frameStreamerWorker,SIGNAL(frameAcquired(cv::Mat)),this,SLOT(updateFrame(cv::Mat)),Qt::QueuedConnection);
        frameStreamerWorker->start();
    }

}

void MainWindow::stop()
{
    isRunning = false;
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

void MainWindow::updateFrame(cv::Mat frame) {
    std::cout << "Update " << std::endl;

    QImage image(frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888);

    image.scaledToHeight(480);
    image.scaledToWidth(640);

    QPixmap pixmap = QPixmap::fromImage(image);

    if (scene == NULL) {
        scene = new QGraphicsScene(this);
    } else {
        delete scene;
        scene = new QGraphicsScene(this);
    }

    scene->addPixmap(pixmap);
    scene->setSceneRect(pixmap.rect());
    ui->Camera->setScene(scene);
}
