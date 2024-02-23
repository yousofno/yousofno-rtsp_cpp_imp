//
// Created by Yousof on 2/3/2024 AD.
//

#ifndef RAMEZANI_DOORBIN_ASKING_PICTURE_FROM_SERVER_H
#define RAMEZANI_DOORBIN_ASKING_PICTURE_FROM_SERVER_H
#include <QUdpSocket>
#include <QObject>
#include <QTcpServer>
#include <QHostAddress>
#include <QTcpSocket>
#include <QRegularExpression>
#include <QCryptographicHash>
#include<QDateTime>
class asking_picture_from_server : public QObject {
Q_OBJECT
public:
    asking_picture_from_server(QObject * parent = 0);
    bool connect_to_camera(const QString& host , quint64 port);


private slots:
    void rtsp_handshake();
    void getting_nounce();
    void getting_thrd();
    void getting_forth();
    void getting_fifth();
    void getting_sixth();
    void getting_seventh();

private:
    QTcpSocket* socket;
    QString relem = "Login to d1e75fb3badd384098f52c76e0a1df91";
    QString nonceValue;
    QString session;


};


#endif //RAMEZANI_DOORBIN_ASKING_PICTURE_FROM_SERVER_H
