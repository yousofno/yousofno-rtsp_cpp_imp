#include "asking_picture_from_server.h"

asking_picture_from_server::asking_picture_from_server(QObject *parent) {
  this->socket = new QTcpSocket();
  connect(this->socket,SIGNAL(connected()) , this , SLOT(rtsp_handshake()));

}

bool asking_picture_from_server::connect_to_camera(const QString &host, quint64 port) {
    this->socket->connectToHost(host , port);
    return this->socket->waitForConnected();
}


void asking_picture_from_server::rtsp_handshake(){
    qDebug()<<"we are in rtsp handshake";
    QString val = "OPTIONS rtsp://192.168.136.185:554/cam/realmonitor?channel=1&subtype=0 RTSP/1.0\r\n"
                  "CSeq: 2\r\n"
                  "User-Agent: LibVLC/3.0.20 (LIVE555 Streaming Media v2016.11.28)\r\n"
                  "\r\n";
    this->socket->write(val.toStdString().c_str() , val.size());
    if(!this->socket->waitForBytesWritten()){
        qDebug()<<"cant wait for sending data";
        return;
    }
    connect(this->socket , SIGNAL(readyRead()) , this , SLOT(getting_nounce()));
}

void asking_picture_from_server::getting_nounce() {

    disconnect(this->socket , SIGNAL(readyRead()) , 0 , 0);
    QString response = this->socket->readAll();
    qDebug()<<"camera response is "<<response;
    QString pattern = "nonce=\\\"([a-fA-F0-9]+)\\\"";
    QRegularExpression regex(pattern);
    QRegularExpressionMatch match_nonce = regex.match(response);

    //finind nonce
    if (!match_nonce.hasMatch()) {
        qDebug()<<"cant find nonce value";
        return;
    }
    nonceValue = match_nonce.captured(1);



    QString raw_frst_hash = QString("%1:%2:%3").arg("admin").arg(relem).arg("951233Alii");
    QString frst_hash = QString(QCryptographicHash::hash((raw_frst_hash.toStdString().c_str()),QCryptographicHash::Md5).toHex());

    QString raw_sncd_hash = QString("%1:%2").arg("OPTIONS")
            .arg("rtsp://192.168.136.185:554/cam/realmonitor?channel=1&subtype=0");
    QString scnd_hash = QString(QCryptographicHash::hash((raw_sncd_hash.toStdString().c_str()),QCryptographicHash::Md5).toHex());

    QString final_raw_hash = QString("%1:%2:%3").arg(frst_hash).arg(nonceValue).arg(scnd_hash);
    QString final_hash = QString(QCryptographicHash::hash((final_raw_hash.toStdString().c_str()),QCryptographicHash::Md5).toHex());


    QString final_val = QString("OPTIONS rtsp://192.168.136.185:554/cam/realmonitor?channel=1&subtype=0 RTSP/1.0\r\n"
                                "CSeq: 3\r\n"
                                "Authorization: Digest username=\"admin\", realm=\"Login to d1e75fb3badd384098f52c76e0a1df91\", nonce=\"%1\", uri=\"rtsp://192.168.136.185:554/cam/realmonitor?channel=1&subtype=0\", response=\"%2\"\r\n"
                                "User-Agent: LibVLC/3.0.20 (LIVE555 Streaming Media v2016.11.28)\r\n"
                                "\r\n").arg(nonceValue).arg(final_hash);



    connect(this->socket , SIGNAL(readyRead()) , this , SLOT(getting_thrd()));
    this->socket->write(final_val.toStdString().c_str() , final_val.size());
    if(!this->socket->waitForBytesWritten()){
        qDebug()<<"cant wait for sending data";
        return;
    }

}

void asking_picture_from_server::getting_thrd() {
    disconnect(this->socket , SIGNAL(readyRead()) , 0 , 0);
    qDebug()<<"camera response is "<<this->socket->readAll();
    QString raw_frst_hash = QString("%1:%2:%3").arg("admin").arg(relem).arg("951233Alii");
    QString frst_hash = QString(QCryptographicHash::hash((raw_frst_hash.toStdString().c_str()),QCryptographicHash::Md5).toHex());

    QString raw_sncd_hash = QString("%1:%2").arg("DESCRIBE")
            .arg("rtsp://192.168.136.185:554/cam/realmonitor?channel=1&subtype=0");
    QString scnd_hash = QString(QCryptographicHash::hash((raw_sncd_hash.toStdString().c_str()),QCryptographicHash::Md5).toHex());

    QString final_raw_hash = QString("%1:%2:%3").arg(frst_hash).arg(nonceValue).arg(scnd_hash);
    QString final_hash = QString(QCryptographicHash::hash((final_raw_hash.toStdString().c_str()),QCryptographicHash::Md5).toHex());


    QString final_val = QString("DESCRIBE rtsp://192.168.136.185:554/cam/realmonitor?channel=1&subtype=0 RTSP/1.0\r\n"
                                "CSeq: 4\r\n"
                                "Authorization: Digest username=\"admin\", realm=\"Login to d1e75fb3badd384098f52c76e0a1df91\", nonce=\"%1\", uri=\"rtsp://192.168.136.185:554/cam/realmonitor?channel=1&subtype=0\", response=\"%2\"\r\n"
                                "User-Agent: LibVLC/3.0.20 (LIVE555 Streaming Media v2016.11.28)\r\n"
                                "Accept: application/sdp\r\n"
                                "\r\n").arg(nonceValue).arg(final_hash);


    connect(this->socket , SIGNAL(readyRead()) , this , SLOT(getting_forth()));
    this->socket->write(final_val.toStdString().c_str() , final_val.size());
    if(!this->socket->waitForBytesWritten()){
        qDebug()<<"cant wait for sending data";
        return;
    }



}


void asking_picture_from_server::getting_forth() {
    disconnect(this->socket , SIGNAL(readyRead()) , 0 , 0);
    qDebug()<<"camera response is "<<this->socket->readAll();
    QString raw_frst_hash = QString("%1:%2:%3").arg("admin").arg(relem).arg("951233Alii");
    QString frst_hash = QString(QCryptographicHash::hash((raw_frst_hash.toStdString().c_str()),QCryptographicHash::Md5).toHex());

    QString raw_sncd_hash = QString("%1:%2").arg("SETUP")
            .arg("rtsp://192.168.136.185:554/cam/realmonitor?channel=1&subtype=0");
    QString scnd_hash = QString(QCryptographicHash::hash((raw_sncd_hash.toStdString().c_str()),QCryptographicHash::Md5).toHex());

    QString final_raw_hash = QString("%1:%2:%3").arg(frst_hash).arg(nonceValue).arg(scnd_hash);
    QString final_hash = QString(QCryptographicHash::hash((final_raw_hash.toStdString().c_str()),QCryptographicHash::Md5).toHex());


    QString final_val = QString("SETUP rtsp://192.168.136.185:554/cam/realmonitor?channel=1&subtype=0/trackID=0 RTSP/1.0\r\n"
                                "CSeq: 5\r\n"
                                "Authorization: Digest username=\"admin\", realm=\"Login to d1e75fb3badd384098f52c76e0a1df91\", nonce=\"%1\", uri=\"rtsp://192.168.136.185:554/cam/realmonitor?channel=1&subtype=0\", response=\"%2\"\r\n"
                                "User-Agent: LibVLC/3.0.20 (LIVE555 Streaming Media v2016.11.28)\r\n"
                                "Transport: RTP/AVP/TCP;unicast;interleaved=0-1\r\n"
                                "\r\n").arg(nonceValue).arg(final_hash);


    connect(this->socket , SIGNAL(readyRead()) , this , SLOT(getting_fifth()));
    this->socket->write(final_val.toStdString().c_str() , final_val.size());
    if(!this->socket->waitForBytesWritten()){
        qDebug()<<"cant wait for sending data";
        return;
    }

}


void asking_picture_from_server::getting_fifth() {
    disconnect(this->socket , SIGNAL(readyRead()) , 0 , 0);
    QString response = this->socket->readAll();
    qDebug()<<"camera response is "<<response;


    QRegularExpression regex("Session:\\s*(\\d+)");
    QRegularExpressionMatch match = regex.match(response);

    if (!match.hasMatch()) {
        qDebug()<<"cant find session";
        return;
    }


    session = match.captured(1);



    QString raw_frst_hash = QString("%1:%2:%3").arg("admin").arg(relem).arg("951233Alii");
    QString frst_hash = QString(QCryptographicHash::hash((raw_frst_hash.toStdString().c_str()),QCryptographicHash::Md5).toHex());

    QString raw_sncd_hash = QString("%1:%2").arg("SETUP")
            .arg("rtsp://192.168.136.185:554/cam/realmonitor?channel=1&subtype=0");
    QString scnd_hash = QString(QCryptographicHash::hash((raw_sncd_hash.toStdString().c_str()),QCryptographicHash::Md5).toHex());

    QString final_raw_hash = QString("%1:%2:%3").arg(frst_hash).arg(nonceValue).arg(scnd_hash);
    QString final_hash = QString(QCryptographicHash::hash((final_raw_hash.toStdString().c_str()),QCryptographicHash::Md5).toHex());


    QString final_val = QString("SETUP rtsp://192.168.136.185:554/cam/realmonitor?channel=1&subtype=0/trackID=0 RTSP/1.0\r\n"
                                "CSeq: 6\r\n"
                                "Authorization: Digest username=\"admin\", realm=\"Login to d1e75fb3badd384098f52c76e0a1df91\", nonce=\"%1\", uri=\"rtsp://192.168.136.185:554/cam/realmonitor?channel=1&subtype=0\", response=\"%2\"\r\n"
                                "User-Agent: LibVLC/3.0.20 (LIVE555 Streaming Media v2016.11.28)\r\n"
                                "Transport: RTP/AVP/TCP;unicast;interleaved=2-3\r\n"
                                "Session: %3\r\n"
                                "\r\n").arg(nonceValue).arg(final_hash).arg(session);


    connect(this->socket , SIGNAL(readyRead()) , this , SLOT(getting_sixth()));
    this->socket->write(final_val.toStdString().c_str() , final_val.size());
    if(!this->socket->waitForBytesWritten()){
        qDebug()<<"cant wait for sending data";
        return;
    }
}


void asking_picture_from_server::getting_sixth(){

    disconnect(this->socket , SIGNAL(readyRead()) , 0 , 0);
    QString response = this->socket->readAll();
    qDebug()<<"camera response is "<<response;


    QString raw_frst_hash = QString("%1:%2:%3").arg("admin").arg(relem).arg("951233Alii");
    QString frst_hash = QString(QCryptographicHash::hash((raw_frst_hash.toStdString().c_str()),QCryptographicHash::Md5).toHex());

    QString raw_sncd_hash = QString("%1:%2").arg("PLAY")
            .arg("rtsp://192.168.136.185:554/cam/realmonitor?channel=1&subtype=0");
    QString scnd_hash = QString(QCryptographicHash::hash((raw_sncd_hash.toStdString().c_str()),QCryptographicHash::Md5).toHex());

    QString final_raw_hash = QString("%1:%2:%3").arg(frst_hash).arg(nonceValue).arg(scnd_hash);
    QString final_hash = QString(QCryptographicHash::hash((final_raw_hash.toStdString().c_str()),QCryptographicHash::Md5).toHex());


    QString final_val = QString("PLAY rtsp://192.168.136.185:554/cam/realmonitor?channel=1&subtype=0/trackID=0 RTSP/1.0\r\n"
                                "CSeq: 7\r\n"
                                "Authorization: Digest username=\"admin\", realm=\"Login to d1e75fb3badd384098f52c76e0a1df91\", nonce=\"%1\", uri=\"rtsp://192.168.136.185:554/cam/realmonitor?channel=1&subtype=0\", response=\"%2\"\r\n"
                                "User-Agent: LibVLC/3.0.20 (LIVE555 Streaming Media v2016.11.28)\r\n"
                                "Session: %3\r\n"
                                "Range: npt=0.000-\r\n"
                                "\r\n").arg(nonceValue).arg(final_hash).arg(session);


    connect(this->socket , SIGNAL(readyRead()) , this , SLOT(getting_seventh()));
    this->socket->write(final_val.toStdString().c_str() , final_val.size());
    if(!this->socket->waitForBytesWritten()){
        qDebug()<<"cant wait for sending data";
        return;
    }


}


void asking_picture_from_server::getting_seventh() {

   qDebug()<<QString(this->socket->readAll());

}
















