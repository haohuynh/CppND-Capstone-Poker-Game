#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include <QObject>
#include <mainwindow.h>
#include <pokercardtable.h>
#include <QMessageBox>
#include <bankroll.h>
#include <QStatusBar>
#include <QMenuBar>
#include <QFileDialog>
#include <QMediaPlayer>

/**
 * @brief The SceneController class
 * This is the primary controller of the GUI.
 * It controls all the behaviors on the main window and its scene
 */
class UIController : public QObject
{
    Q_OBJECT

private:

    /*Path to the back ground sound track*/
    const QString BG_S_FILE_NAME = "qrc:/SoundTracks/BGMusic.mp3";

    /*The media player of the back ground music*/
    QMediaPlayer *bgMusic;

    /*The main window of Poker Game*/
    MainWindow *mainWindow;

    /*The BankRoll dialog of Poker Game*/
    BankRoll* bankRoll;

    /*The Porker Card Table object*/
    PokerCardTable* pokTble;

    /*The current bank roll*/
    int crBkRoll = PokerHelper::MAX_BANK_ROLL;

    /*The current money that a player wants to bet*/
    int crrBet = 0;


public:

    /*The constructor of this main UI controller*/
    explicit UIController(QObject *parent = 0);

    /*The default destructor*/
    ~UIController();

private:

    /*This function shows the player the final result and interact with that player for further processing*/
    void finalizePokerGame();

    /*Update the status bar with the new message*/
    void updateStatus(QString message);

    /*Update the LCD with the new bank roll and bet values*/
    void updateLCDRoll();

signals:



public slots:

    /**
     * This function asks PokerCardTable to start a new game
     * and asks MainWindow to process porker card images
     * @brief startGame
     */
    void startGame();

    /**
     * This function handles the replace-card request from a player
     * @brief replaceCards
     */
    void replaceCards();

    /**
     * This function handles the bet value that user had chosen in the Bank Roll dialog
     * @brief processBetValue
     */
    void processBetValue();

    /**
     * This function handles the menu bar new game signal
     * @brief newGame
     */
    void newGame();

    /**
     * This function handles the menu bar save game signal
     * @brief saveGame
     */
    void saveGame();

    /**
     * This function handles the menu bar load game signal
     * @brief loadGame
     */
    void loadGame();

    /**
     * This function handles the menu bar exit game signal
     * @brief exitGame
     */
    void exitGame();

    /**
     * This function is called when the back ground music was stoped
     * @brief stateChanged
     * @param newState
     */
    void stateChanged(QMediaPlayer::State newState);

};

#endif // UICONTROLLER_H
