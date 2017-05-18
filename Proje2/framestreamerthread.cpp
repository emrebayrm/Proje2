#include "framestreamerthread.h"

void FrameStreamerWorker::run()
{
    struct sockaddr_in serverAddr;

    if ((dataSocket = socket(AF_INET,SOCK_STREAM,0)) == -1) {
        cout << "Could not create socket" << endl;
        exit(1);
    }

    if ((dataSizeSocket = socket(AF_INET,SOCK_STREAM,0)) == -1) {
        cout << "Could not create socket" << endl;
        exit(1);
    }

    serverAddr.sin_addr.s_addr= inet_addr(ip.toStdString().c_str());
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (::connect(dataSocket,(const sockaddr *)&serverAddr,sizeof(serverAddr)) != 0) {
        cout << "Failed to establish connection with server" << endl;
        exit(1);
    }

    if (::connect(dataSizeSocket,(const sockaddr *)&serverAddr,sizeof(serverAddr)) != 0) {
        cout << "Failed to establish connection with server" << endl;
        exit(1);
    }

    while(true) {
        readFrameSize();
        readFrameData();
        emit frameAcquired(frame);
        qApp->processEvents();
    }
}

void FrameStreamerWorker::readFrameSize() {
    memset(frameSizeBuffer,0,sizeof(frameSizeBuffer));
    recv(dataSizeSocket,frameSizeBuffer,sizeof(frameSizeBuffer),0);
    send(dataSizeSocket,"OK",strlen("OK"),0);

    frameSize = atoi(frameSizeBuffer);

    cout << "Frame size: " << frameSize << endl;
}

void FrameStreamerWorker::readFrameData() {
    frameDataBuffer = new char[frameSize];

    int readedBytes = 0;

    /* -------- Get data from device ----------*/
    for (int i = 0; i < frameSize; i += readedBytes) {
        readedBytes = recv(dataSocket,frameDataBuffer + i, frameSize - i, 0);
        if (readedBytes != 0) {
            cerr << "Received bytes: " << readedBytes << endl;
        }
        int sendedBytes = send(dataSocket,"OK",strlen("OK"),0);
        cerr << "Sended bytes: " << sendedBytes << endl;
    }

    vector<char> data(frameDataBuffer, frameDataBuffer + frameSize);
    Mat encodedFrame(data);
    encodedFrame.reshape(0,1);
    imdecode(encodedFrame,CV_LOAD_IMAGE_COLOR,&frame);

    cout << "Frame Acquired" << endl;
}
