#include "udpreceiver.h"

UdpReceiver::UdpReceiver(QObject *parent)
    : QObject{parent}
{
}

bool UdpReceiver::start(uint16_t port) {
    this->port = port;
    socket = new QUdpSocket(this);
    if (!socket->bind(QHostAddress::Any, port)) {
        return false;
    }

    connect(socket, &QUdpSocket::readyRead, this, &UdpReceiver::onReadyRead);

    return true;
}

void UdpReceiver::onReadyRead() {
    while (socket->hasPendingDatagrams()) {
        QByteArray data;
        int datagramSize = socket->pendingDatagramSize();
        data.resize(datagramSize);

        qint64 readLen = socket->readDatagram(data.data(), data.size());
        if (readLen == -1) return;
        process(data);
    }
}

void UdpReceiver::process(QByteArray data) {
    QDataStream in(data);
    in.setVersion(16);
    in.setByteOrder(QDataStream::BigEndian);

    in >> magic >> schema >> message_type;

    switch (message_type) {
        case Heartbeat:
            in >> id >> max_schema_number >> version >> revision;
            emit heartbeat();
        break;

        case QSOLogged:
            in >> id >> time_off >> dx_call >> dx_grid >> tx_frequency_hz >> mode >> report_sent >> report_received >> tx_power >> comments >> name >> time_on >> operator_call >> my_call >> my_grid >> exchange_sent >> exchange_rcvd >> propmode;
            emit logged();
        break;
    }
}
