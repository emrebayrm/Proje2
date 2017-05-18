#include "stickmanlocation.h"

void StickManLocation::run()
{
    struct sockaddr_in serverAddr;

    if ((dataSocket = socket(AF_INET,SOCK_STREAM,0)) == -1) {
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
    while(true) {
        readStickMan();
        emit stickManAddressFounded(this->addres);
        qApp->processEvents();
    }
}

void StickManLocation::readStickMan(){
    recv(dataSocket,&addres,sizeof(addres),0);
}
