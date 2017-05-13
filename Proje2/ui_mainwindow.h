/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *labelCamera;
    QPushButton *Connect;
    QPushButton *stop;
    QTextBrowser *MessageBox;
    QLabel *labelMessageBox;
    QLabel *stopWatch;
    QGraphicsView *Camera;
    QLineEdit *ipText;
    QLineEdit *PortText;
    QLabel *label;
    QLabel *labelPort;
    QLabel *gtuLogo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1039, 607);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(1039, 607));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        labelCamera = new QLabel(centralwidget);
        labelCamera->setObjectName(QStringLiteral("labelCamera"));
        labelCamera->setGeometry(QRect(50, 20, 59, 14));
        Connect = new QPushButton(centralwidget);
        Connect->setObjectName(QStringLiteral("Connect"));
        Connect->setGeometry(QRect(740, 490, 111, 41));
        stop = new QPushButton(centralwidget);
        stop->setObjectName(QStringLiteral("stop"));
        stop->setGeometry(QRect(900, 490, 121, 41));
        MessageBox = new QTextBrowser(centralwidget);
        MessageBox->setObjectName(QStringLiteral("MessageBox"));
        MessageBox->setGeometry(QRect(710, 170, 321, 231));
        labelMessageBox = new QLabel(centralwidget);
        labelMessageBox->setObjectName(QStringLiteral("labelMessageBox"));
        labelMessageBox->setGeometry(QRect(720, 140, 171, 16));
        stopWatch = new QLabel(centralwidget);
        stopWatch->setObjectName(QStringLiteral("stopWatch"));
        stopWatch->setGeometry(QRect(950, 420, 71, 21));
        Camera = new QGraphicsView(centralwidget);
        Camera->setObjectName(QStringLiteral("Camera"));
        Camera->setGeometry(QRect(50, 40, 640, 480));
        sizePolicy.setHeightForWidth(Camera->sizePolicy().hasHeightForWidth());
        Camera->setSizePolicy(sizePolicy);
        Camera->setMaximumSize(QSize(640, 480));
        Camera->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        Camera->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        Camera->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        ipText = new QLineEdit(centralwidget);
        ipText->setObjectName(QStringLiteral("ipText"));
        ipText->setGeometry(QRect(800, 410, 113, 22));
        PortText = new QLineEdit(centralwidget);
        PortText->setObjectName(QStringLiteral("PortText"));
        PortText->setGeometry(QRect(800, 450, 113, 22));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(730, 410, 21, 16));
        labelPort = new QLabel(centralwidget);
        labelPort->setObjectName(QStringLiteral("labelPort"));
        labelPort->setGeometry(QRect(730, 450, 41, 16));
        gtuLogo = new QLabel(centralwidget);
        gtuLogo->setObjectName(QStringLiteral("gtuLogo"));
        gtuLogo->setGeometry(QRect(780, 9, 201, 111));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1039, 19));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        labelCamera->setText(QApplication::translate("MainWindow", "Camera", Q_NULLPTR));
        Connect->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        stop->setText(QApplication::translate("MainWindow", "Stop", Q_NULLPTR));
        labelMessageBox->setText(QApplication::translate("MainWindow", "Messages' ", Q_NULLPTR));
        stopWatch->setText(QApplication::translate("MainWindow", "0:0:0:0", Q_NULLPTR));
        ipText->setText(QApplication::translate("MainWindow", "192.168.1.33", Q_NULLPTR));
        PortText->setText(QApplication::translate("MainWindow", "14144", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "IP  :", Q_NULLPTR));
        labelPort->setText(QApplication::translate("MainWindow", "Port    :", Q_NULLPTR));
        gtuLogo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
