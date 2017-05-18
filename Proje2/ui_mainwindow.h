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
    QLabel *ElapsedLabel;
    QGraphicsView *virtualScene;
    QLabel *VirtualSceneLabel;
    QLabel *sagCetvel;
    QLabel *solCetvel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1300, 600);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(1366, 600));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        labelCamera = new QLabel(centralwidget);
        labelCamera->setObjectName(QStringLiteral("labelCamera"));
        labelCamera->setGeometry(QRect(50, 20, 59, 14));
        Connect = new QPushButton(centralwidget);
        Connect->setObjectName(QStringLiteral("Connect"));
        Connect->setGeometry(QRect(850, 500, 111, 41));
        stop = new QPushButton(centralwidget);
        stop->setObjectName(QStringLiteral("stop"));
        stop->setGeometry(QRect(1060, 500, 121, 41));
        MessageBox = new QTextBrowser(centralwidget);
        MessageBox->setObjectName(QStringLiteral("MessageBox"));
        MessageBox->setGeometry(QRect(1010, 340, 271, 121));
        labelMessageBox = new QLabel(centralwidget);
        labelMessageBox->setObjectName(QStringLiteral("labelMessageBox"));
        labelMessageBox->setGeometry(QRect(980, 320, 81, 21));
        stopWatch = new QLabel(centralwidget);
        stopWatch->setObjectName(QStringLiteral("stopWatch"));
        stopWatch->setGeometry(QRect(1200, 470, 71, 21));
        Camera = new QGraphicsView(centralwidget);
        Camera->setObjectName(QStringLiteral("Camera"));
        Camera->setGeometry(QRect(50, 40, 660, 500));
        sizePolicy.setHeightForWidth(Camera->sizePolicy().hasHeightForWidth());
        Camera->setSizePolicy(sizePolicy);
        Camera->setMaximumSize(QSize(660, 500));
        Camera->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        Camera->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        Camera->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        ipText = new QLineEdit(centralwidget);
        ipText->setObjectName(QStringLiteral("ipText"));
        ipText->setGeometry(QRect(770, 470, 113, 22));
        PortText = new QLineEdit(centralwidget);
        PortText->setObjectName(QStringLiteral("PortText"));
        PortText->setGeometry(QRect(970, 470, 113, 22));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(730, 470, 21, 16));
        labelPort = new QLabel(centralwidget);
        labelPort->setObjectName(QStringLiteral("labelPort"));
        labelPort->setGeometry(QRect(900, 470, 51, 21));
        gtuLogo = new QLabel(centralwidget);
        gtuLogo->setObjectName(QStringLiteral("gtuLogo"));
        gtuLogo->setGeometry(QRect(750, 340, 201, 111));
        ElapsedLabel = new QLabel(centralwidget);
        ElapsedLabel->setObjectName(QStringLiteral("ElapsedLabel"));
        ElapsedLabel->setGeometry(QRect(1090, 470, 91, 21));
        virtualScene = new QGraphicsView(centralwidget);
        virtualScene->setObjectName(QStringLiteral("virtualScene"));
        virtualScene->setGeometry(QRect(790, 40, 501, 271));
        VirtualSceneLabel = new QLabel(centralwidget);
        VirtualSceneLabel->setObjectName(QStringLiteral("VirtualSceneLabel"));
        VirtualSceneLabel->setGeometry(QRect(680, 20, 111, 16));
        sagCetvel = new QLabel(centralwidget);
        sagCetvel->setObjectName(QStringLiteral("sagCetvel"));
        sagCetvel->setGeometry(QRect(790, 10, 500, 23));
        solCetvel = new QLabel(centralwidget);
        solCetvel->setObjectName(QStringLiteral("solCetvel"));
        solCetvel->setGeometry(QRect(760, 40, 23, 271));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1300, 19));
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
        ElapsedLabel->setText(QApplication::translate("MainWindow", "Elapsed Time : ", Q_NULLPTR));
        VirtualSceneLabel->setText(QApplication::translate("MainWindow", "Virtual Scene :", Q_NULLPTR));
        sagCetvel->setText(QString());
        solCetvel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
