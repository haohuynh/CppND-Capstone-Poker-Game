#include "pokerclient.h"

/**
 * Reference to the function declaration
 * @brief PokerClient::PokerClient
 */
PokerClient::PokerClient()
{
    tcpSocket = new QTcpSocket();

    //Handle connected event
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(sendData()));

    //Handle connection errors
    connect(tcpSocket, SIGNAL(disconnected()),
            this, SLOT(processError()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(processError()));
}

/**
 * Reference to the function declaration
 * @brief PokerClient::save
 * @param object
 * @param score
 */
void PokerClient::save(QString object, int score)
{
    this->object = object;
    this->score = QString::number(score);
    tcpSocket->connectToHost(QHostAddress::LocalHost, 2015);
}

/**
 * Reference to the function declaration
 * @brief PokerClient::sendData
 */
void PokerClient::sendData()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out << object << score;

    tcpSocket->write(block);
    tcpSocket->close();
}

/**
 * Reference to the function declaration
 * @brief PokerClient::processError
 */
void PokerClient::processError()
{
    tcpSocket->close();
}

