#include "pokerhelper.h"
#include <QDebug>

/**
 * Reference to the constant declaration
 * @brief PokerHelper::SER_CONF_FILE_NAME
 */
const QString PokerHelper::GAME_RESULT_TITTLE = "Poker Game Result!" ;

/**
 * Reference to the constant declaration
 * @brief PokerHelper::IP_V4_ADDR_REG_EXPRESS
 */
const QString PokerHelper::IP_V4_ADDR_REG_EXPRESS = "^([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\.([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\.([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\.([01]?\\d\\d?|2[0-4]\\d|25[0-5])$";

/**
 * The default constructor
 * @brief PokerHelper::PokerHelper
 */
PokerHelper::PokerHelper()
{

}

/**
 * Reference to the function declaration
 * @brief PokerHelper::saveFile
 * @param fileName
 * @param bkRoll
 */
bool PokerHelper::saveFile(QString fileName, int bkRoll, int bet)
{
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly)){
        return false;
    }

    QDataStream datStrm(&file);
    datStrm << bkRoll;
    datStrm << bet;

    file.close();
    return true;

}

/**
 * Reference to the function declaration
 * @brief PokerHelper::loadFile
 * @param fileName
 * @return the current bank roll
 */
bool PokerHelper::loadFile(QString fileName, int& bkRoll, int& bet)
{
    QFile file(fileName);

    bkRoll = 1;
    bet = 1;

    if (!file.open(QFile::ReadOnly)){
        return false;
    }

    QDataStream datStrm(&file);
    datStrm >> bkRoll;
    datStrm >> bet;

    file.close();
    return true;
}

/**
 * Reference to the function declaration
 * @brief PokerHelper::validateIPv4Addr
 * @param ipAddr
 * @return
 */
bool PokerHelper::validateIPv4Addr(QString ipAddr)
{
    QRegularExpression regExpr(IP_V4_ADDR_REG_EXPRESS);

    if (regExpr.match(ipAddr).hasMatch()){
        return true;
    }

    return false;
}

