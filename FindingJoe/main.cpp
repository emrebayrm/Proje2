//
// Created by mpolatcan-gyte_cse on 04.03.2017.
//
#include <opencv2/opencv.hpp>
#include <vector>
#include <sstream>
#include "StepMotor.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>

using namespace cv;
using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
Mat frame;
double angleResult;
Mat binary;
Mat coloredBinary;
Mat clippedStickMan;
RotatedRect angleContour;
Rect stickmanContour;
bool firstWhite = false;
char ACKNOWLEDGE[2];

/* ------------ FRAME STREAMER VARIABLES ------------ */
int mainSocket;
int dataSocket;
int dataSizeSocket;
struct sockaddr_in serverAddr;
int iSockOpt = 1;
/* -------------------------------------------------- */


void *motorMovement(void *);
int regionPixelCounting(Mat image, int firstBegin, int firstEnd, int secondBegin, int secondEnd);
void detectStickMan(Mat clippedStickMan);
void showOrientation(int firstRegion, int secondRegion, int thirdRegion, int fourthRegion);
void setupNetwork();

void *frameStreamerTask(void *){
    dataSocket = accept(mainSocket,(struct sockaddr *)NULL, NULL);
    dataSizeSocket = accept(mainSocket,(struct sockaddr *)NULL, NULL);

    while(1)
    {
        ostringstream dataSizeStr;

        vector<uchar> encodedImage;
        vector<int> compressionParams;
        compressionParams.push_back((int &&) CV_IMWRITE_JPEG_QUALITY);
        compressionParams.push_back(50);
        imencode(".jpg",frame,encodedImage,compressionParams);

        dataSizeStr << encodedImage.size();

        const char *dataSize = dataSizeStr.str().c_str();

        send(dataSizeSocket,dataSize,strlen(dataSize),0);
        recv(dataSizeSocket,ACKNOWLEDGE,sizeof(ACKNOWLEDGE),0);
        /* ---------------------------------------------------- */

        char *data = new char[encodedImage.size()];

        for (int i = 0; i < encodedImage.size(); ++i) {
            data[i] = encodedImage.at(i);
        }

        int sendedBytes = 0;
        int receivedBytes;
        for (int i = 0; i < encodedImage.size(); i += sendedBytes) {
            sendedBytes = send(dataSocket, data + i, encodedImage.size() - i, 0);
           cout << "Sended bytes: " << sendedBytes << endl;
            receivedBytes = recv(dataSocket, ACKNOWLEDGE, 2,0);
           cout << "Received bytes: " << receivedBytes << endl;
        }
    }
}

int main(void) {
    VideoCapture video(0);
    if (!video.isOpened()) {
        printf("Failed to open a video device or video file!\n");
        return 1;
    }

    setupNetwork();
    pthread_t id;
    pthread_t motorThid;
    pthread_create(&id,NULL,frameStreamerTask,NULL);
//    pthread_create(&motorThid,NULL,motorMovement,NULL);
    while (true) {
        video >> frame;
        cvtColor(frame,frame,CV_BGR2RGB);
        GaussianBlur(frame,frame,Size(3,3),2);
        Canny(frame,binary,50,200,3);
        dilate(binary,binary,getStructuringElement(MORPH_RECT,Size(5,5)));
       // cerr << frame.rows << "   " << frame.cols << endl;
        vector<vector<Point>> contours;
        findContours(binary,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);

        cvtColor(binary,coloredBinary,COLOR_GRAY2BGR);
        if(!firstWhite) {
            for (int  i = 0; i < coloredBinary.rows; ++i) {
                for(int j = 0; j < coloredBinary.cols; ++j){
                        Vec3b a =  coloredBinary.at<Vec3b>(Point(j,i));
                        if(a.val[0] == 255 && a.val[1] == 255 && a.val[2] == 255 )
                        {
                            firstWhite = true;
                        }

                }
            }
        }
        /// Find the rotated rectangles
        vector<RotatedRect> minRect(contours.size());

        for( int i = 0; i < contours.size(); i++ ) {
            stickmanContour = boundingRect(contours.at(i));
            minRect[i] = minAreaRect(Mat(contours[i]));
        }

        for (int i = 0; i < contours.size(); ++i) {
            Point2f rect_points[4];
            minRect[i].points(rect_points);

            angleContour = minRect[i];

            for(int j = 0; j < 4; j++ ) {
                line(frame, rect_points[j], rect_points[(j + 1) % 4], Scalar(255, 0, 0), 2, LINE_AA);
            }

            rectangle(frame,stickmanContour,Scalar(0,255,0),2);
            clippedStickMan = binary(Rect(stickmanContour.x,stickmanContour.y,stickmanContour.width,stickmanContour.height));
        }

        detectStickMan(clippedStickMan);

        angleResult = abs(angleResult);

        ostringstream oss;
        oss << angleResult;

        putText(frame,oss.str(), Point(stickmanContour.x+stickmanContour.width,
                                               stickmanContour.y+stickmanContour.height),CV_FONT_HERSHEY_SIMPLEX,1.0,Scalar(0,255,0),2);

        imshow("Frame",frame);
        imshow("Colored",coloredBinary);
        waitKey(10);
    }
}

int regionPixelCounting(Mat image, int firstBegin, int firstEnd, int secondBegin, int secondEnd) {
    int result = 0;

    for (int i = firstBegin; i < firstEnd; ++i) {
        for (int j = secondBegin; j < secondEnd; ++j) {
            if (image.at<uchar>(i,j) == 255) {
                ++result;
            }
        }
    }

    return result;
}

void detectStickMan(Mat clippedStickMan) {
    int firstRegion, secondRegion, thirdRegion, fourthRegion;

    firstRegion = regionPixelCounting(clippedStickMan, 0, clippedStickMan.rows / 2, 0, clippedStickMan.cols / 2);
    secondRegion = regionPixelCounting(clippedStickMan, 0, clippedStickMan.rows / 2, clippedStickMan.cols / 2, clippedStickMan.cols);
    thirdRegion = regionPixelCounting(clippedStickMan, clippedStickMan.rows / 2, clippedStickMan.rows, 0, clippedStickMan.cols / 2);
    fourthRegion = regionPixelCounting(clippedStickMan, clippedStickMan.rows / 2, clippedStickMan.rows, clippedStickMan.cols / 2, clippedStickMan.cols);

    showOrientation(firstRegion,secondRegion,thirdRegion,fourthRegion);
}

void showOrientation(int firstRegion, int secondRegion, int thirdRegion, int fourthRegion) {
    int regionCounts[] = {firstRegion, secondRegion, thirdRegion, fourthRegion};

    int maxIndex = 0;
    int max = regionCounts[0];

    for (int i = 1; i < 4; ++i) {
        if (regionCounts[i] > max) {
            max = regionCounts[i];
            maxIndex = i;
        }
    }

    if (maxIndex == 0) {
        angleResult = angleContour.angle - 90;
    } else if (maxIndex == 1) {
        angleResult = angleContour.angle;
    } else if (maxIndex == 2) {
        angleResult = angleContour.angle - 180;
    } else if (maxIndex == 3) {
        angleResult = angleContour.angle - 270;
    }
}

void *motorMovement(void *){
    int ustEnablePin = 16;
    int ustStepPin = 20;
    int ustDirPin = 21;
    int altEnablePin = 13;
    int altStepPin = 19;
    int altDirPin = 26;
    int i,j;
    StepMotor ustMotor(ustEnablePin,ustStepPin,ustDirPin);
    StepMotor altMotor(altEnablePin,altStepPin,altDirPin);

    bool direcMotor1= false;
    for(j = 0; j < 5; ++j){
        for(i = 0; i < 400;i++){
            if(firstWhite){
                break;
            }
            ustMotor.GoStep(1,direcMotor1);
        }
        if(firstWhite){
            break;
        }
        direcMotor1 = direcMotor1 ? false : true;
        altMotor.GoStep(175,false);
    }

}

void setupNetwork() {
    string ip;
    int port = 14144;
    if ((mainSocket = socket(AF_INET,SOCK_STREAM,0)) == -1) {
        cout << "Could not create socket" << endl;
        exit(1);
    }

    if (setsockopt(mainSocket,SOL_SOCKET,SO_REUSEADDR,&iSockOpt,sizeof(int)) == -1) {
        cout << "Socket options can't be applied!" << endl;
        exit(1);
    }

    serverAddr.sin_addr.s_addr = (INADDR_ANY);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (bind(mainSocket,(struct sockaddr *)&serverAddr,sizeof(serverAddr))) {
        cout << "Socket can't be binded" << endl;
        exit(1);
    }

    if (listen(mainSocket,10) == -1) {
        cout << "Socket can't be listened" << endl;
        exit(1);
    }
}
