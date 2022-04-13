#ifndef POKERHELPER_H
#define POKERHELPER_H

#include <QFile>
#include <QDataStream>
#include <QRegularExpression>

class PokerHelper
{

public:

    /*
     * The top-left x position of the start button icon
     */
    static const int START_BUTTON_ICON_X = 400;

    /*
     * The top-left y position of the start button icon
     */
    static const int START_BUTTON_ICON_Y = 250;

    /*
     * The width of the start button icon
     */
    static const int START_BUTTON_ICON_W = 200;

    /*
     * The height of the start button icon
     */
    static const int START_BUTTON_ICON_H = 100;

    /*
     * The top-left x position of the deal button icon
     */
    static const int DEAL_BUTTON_ICON_X = 700;

    /*
     * The top-left y position of the deal button icon
     */
    static const int DEAL_BUTTON_ICON_Y = 40;

    /*
     * The width of the deal button icon
     */
    static const int DEAL_BUTTON_ICON_W = 180;

    /*
     * The height of the deal button icon
     */
    static const int DEAL_BUTTON_ICON_H = 80;

    /*
     * Initiated money a player can have
     */
    static const int MAX_BANK_ROLL = 100;

    /*
     * Out of money
     */
    static const int MIN_BANK_ROLL = 0;

    /*
     * The final game result tittle
     */
    static const QString GAME_RESULT_TITTLE;

    /*
     * The regular expression of an IPv4 Address
     */
    static const QString IP_V4_ADDR_REG_EXPRESS;

    /**
     * The boolean type for this program
     */
    static enum GAME_BOOL {
        DRAWN = -1, LOSE = 0, WIN = 1
    } GameBool;


public:
    /**
     * The default constructor
     * @brief PokerHelper
     */
    PokerHelper();

    /**
     * This function saves the current bank roll to a file
     * @brief saveFile
     * @param fileName
     * @param bkRoll : the current bank roll
     */
    static bool saveFile(QString fileName, int bkRoll, int bet);

    /**
     * This function reads all the content in the fileName for a subject
     * @brief loadFile
     * @param fileName
     * @return the content in the fileName
     */
    static bool loadFile(QString fileName, int& bkRoll, int& bet);

    /**
     * This function use a regular expression to validate the input string contains a valid IPv4 Address
     * @brief validateIPv4Addr
     * @param ipAddr
     * @return true/false
     */
    static bool validateIPv4Addr(QString ipAddr);

};

#endif // POKERHELPER_H
