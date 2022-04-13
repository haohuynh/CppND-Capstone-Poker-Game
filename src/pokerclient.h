#ifndef POKERCLIENT_H
#define POKERCLIENT_H

#include <QTcpSocket>
#include <QDataStream>
#include <QtNetwork>

/**
 * This class creates a TCP connection to the PokerServer.
 * Then it sends that server the information of the winner and the score
 * @brief The PokerClient class
 */
class PokerClient : public QObject
{
    Q_OBJECT

private:

    /**
     * The main object that manages a TCP connection
     * @brief tcpSocket
     */
    QTcpSocket* tcpSocket;

    /**
     * The object can be a player or a dealer
     * @brief object
     */
    QString object;

    /**
     * The final score
     * @brief score
     */
    QString score;

public:
    /**
     * A default constructor
     * @brief PokerClient
     */
    PokerClient();

    /**
     * Save a record the database
     * @brief save
     * @param object
     * @param score
     */
    void save(QString object, int score);

private slots:

    /**
     * Send statistics data to the server
     * @brief sendData
     */
    void sendData();

    /**
     * Process the connection error
     * @brief processError
     */
    void processError();
};

#endif // POKERCLIENT_H
