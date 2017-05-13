//
// Created by mpolatcan-gyte_cse on 04.03.2017.
//
#include <opencv2/opencv.hpp>
#include <vector>
#include <sstream>

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

int regionPixelCounting(Mat image, int firstBegin, int firstEnd, int secondBegin, int secondEnd);
void detectStickMan(Mat clippedStickMan);
void showOrientation(int firstRegion, int secondRegion, int thirdRegion, int fourthRegion);
void *setupNetwork(void *){
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[1025];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(14144);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listenfd, 10);
    cerr << "Waiting" << endl;
    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    cerr << "Connection started" << endl;
    int dataSize;
    Mat willSend;
    dataSize = frame.rows * frame.cols;
    cerr << dataSize ;
    write(connfd,&dataSize,sizeof(int));
    char dead;
    int ret=1;
    while(1)
    {
        if(ret > 0) {
            pthread_mutex_lock(&mutex);
                frame.copyTo(willSend);
            pthread_mutex_unlock(&mutex);

            cerr << "Write :" << send(connfd,willSend.data,dataSize,0);
            ret = read(connfd, &dead, sizeof(int));
            cerr << "Next Data";
            sleep(1);
        }
        else{
            connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
            write(connfd,&dataSize,sizeof(int));
        }
    }
}

int main(void) {
    VideoCapture video(0);

    // Set capture device properties
//    video.set(CV_CAP_PROP_FRAME_WIDTH, 640);
//    video.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

    // check for failure
    if (!video.isOpened()) {
        printf("Failed to open a video device or video file!\n");
        return 1;
    }
    pthread_t id;
   // pthread_create(&id,NULL,setupNetwork,NULL);

    while (true) {
        pthread_mutex_lock(&mutex);
        video >> frame;

        GaussianBlur(frame,frame,Size(3,3),2);
        Canny(frame,binary,50,200,3);
        dilate(binary,binary,getStructuringElement(MORPH_RECT,Size(5,5)));
       // cerr << frame.rows << "   " << frame.cols << endl;
        vector<vector<Point>> contours;
        findContours(binary,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);

        cvtColor(binary,coloredBinary,COLOR_GRAY2BGR);

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
                line(coloredBinary, rect_points[j], rect_points[(j + 1) % 4], Scalar(0, 0, 255), 1, 8);
            }

            rectangle(coloredBinary,stickmanContour,Scalar(0,255,0));
            clippedStickMan = binary(Rect(stickmanContour.x,stickmanContour.y,stickmanContour.width,stickmanContour.height));
        }

        detectStickMan(clippedStickMan);

        angleResult = abs(angleResult);

        ostringstream oss;
        oss << angleResult;

        putText(coloredBinary,oss.str(), Point(stickmanContour.x+stickmanContour.width,
                                               stickmanContour.y+stickmanContour.height),CV_FONT_HERSHEY_SIMPLEX,1.0,Scalar(0,0,255));
        pthread_mutex_unlock(&mutex);
        imshow("Original",coloredBinary);
        imshow("Frame",frame);
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
