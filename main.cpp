#include <QCoreApplication>
#include "asking_picture_from_server.h"

#include <QBuffer>
#include <QDebug>



int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    asking_picture_from_server* video = new asking_picture_from_server();
    video->connect_to_camera("192.168.136.100",1234);
    return QCoreApplication::exec();
}
