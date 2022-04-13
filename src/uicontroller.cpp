#include "uicontroller.h"
#include <QDebug>

/**
 * Reference to the function declaration
 * @brief UIController::UIController
 * @param parent
 */
UIController::UIController(QObject *parent) : QObject(parent)
{
    //Initialize the main window with its components
    mainWindow = new MainWindow();
    mainWindow->show();

    //Initialize the Bank Roll dialog with its components
    bankRoll = new BankRoll(mainWindow);

    //Register with the mainWindow to receive a game-started signal
    connect(mainWindow,SIGNAL(startGame()),this, SLOT(startGame()));

    //Register with the mainWindow to receive a card-replace signal
    connect(mainWindow,SIGNAL(replaceCards()),this, SLOT(replaceCards()));

    //Register with the mainWindow to receive all menubar-action signals
    connect(mainWindow,SIGNAL(newGame()),this, SLOT(newGame()));
    connect(mainWindow,SIGNAL(saveGame()),this, SLOT(saveGame()));
    connect(mainWindow,SIGNAL(loadGame()),this, SLOT(loadGame()));
    connect(mainWindow,SIGNAL(exitGame()),this, SLOT(exitGame()));

    //Register with the bankRoll to receive a bet-value signal
    connect(bankRoll,SIGNAL(processBetValue()),this, SLOT(processBetValue()));

    //Initialize the object that manage the logic of this game
    pokTble = new PokerCardTable();

    //Setup the multimedia players
    bgMusic = new QMediaPlayer();
    bgMusic->setMedia(QUrl(BG_S_FILE_NAME));

    //Using SIGNAL-SLOT to replay the back ground music
    connect(bgMusic,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(stateChanged(QMediaPlayer::State)));
    //Start playing the back ground music
    bgMusic->play();
}

/**
 * @brief UIController::~UIController
 */
UIController::~UIController()
{
    //Stop using SIGNAL-SLOT to replay the back ground music
    disconnect(bgMusic,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(stateChanged(QMediaPlayer::State)));
    bgMusic->stop();
}

/**
 * Reference to the function declaration
 * @brief UIController::finalizePokerGame
 */
void UIController::finalizePokerGame()
{
    //Ask the Poker Card Table for the final result
    QString message;
    PokerHelper::GAME_BOOL result = pokTble->getGameResult(message);

    //Update the bank roll
    if (result == PokerHelper::WIN) { //The player win a game
        crBkRoll += crrBet;
    } else if (result == PokerHelper::LOSE) {//The player lose a game
        crBkRoll -= crrBet;
    }
    updateLCDRoll();

    //Notify the new bank to the player
    if (crBkRoll > PokerHelper::MIN_BANK_ROLL){// The player still have money and want to continue on the game
        message += "Your current bank roll is: " + QString::number(crBkRoll);
        message += "\nWould you like to continue ?\n";

    }else{//The player is out of money
        message += "\nOut of money!! You have to start a new game ?";
    }

    // Lock the main windows to wait for user's input
    mainWindow->setEnabled(false);

    //Ask user to continue on the game
    if ( QMessageBox::question(mainWindow,PokerHelper::GAME_RESULT_TITTLE,message,QMessageBox::Yes | QMessageBox::No) == QMessageBox::No){
        exit(0);
    }

    //The user was out of money and accepted to start a new game
    if (crBkRoll <= PokerHelper::MIN_BANK_ROLL){
        crBkRoll = PokerHelper::MAX_BANK_ROLL;
        updateLCDRoll();
    }

    //Restart the mainWindow for a new game
    mainWindow->restartUI();

}

/**
 * Reference to the function declaration
 * @brief UIController::updateBRStatus
 */
void UIController::updateStatus(QString message)
{
    mainWindow->statusBar()->showMessage(message);
}

/**
 * Reference to the function declaration
 * @brief UIController::updateRollLCD
 */
void UIController::updateLCDRoll()
{
    mainWindow->updateLCD(crBkRoll,crrBet);
}

/**
 * Reference to the function declaration
 * @brief UIController::startGame
 */
void UIController::startGame()
{
    //Lock the menu bar until Bank Roll dialog has been processed
    mainWindow->menuBar()->setEnabled(false);

    //Show Bank Roll Dialog
    bankRoll->populateUI(crBkRoll);
    bankRoll->show();
}

/**
 * Reference to the function declaration
 * @brief UIController::replaceCards
 */
void UIController::replaceCards()
{
    QVector<int> repIds = mainWindow->getRCardIds();

    if (!repIds.empty()){
        pokTble->replaceCards(repIds);
    }

    //Show new sets of cards after the replacing process
    mainWindow->displayCards(pokTble->getCrCardIds());
    mainWindow->displayCards(pokTble->getCrDCardIds(), false);

    //Checking the result
    finalizePokerGame();
}

/**
 * Reference to the function declaration
 * @brief UIController::processBetValue
 */
void UIController::processBetValue()
{
    //Update the new bet value
    crrBet = bankRoll->getBetValue();
    updateLCDRoll();

    //Actually start the game
    pokTble->dealsCards();
    mainWindow->displayCards(pokTble->getCrCardIds());

    //Let the Deal button appear
    mainWindow->addDealButton();

    //Enable the menu bar
    mainWindow->menuBar()->setEnabled(true);
}

/**
 * Reference to the function declaration
 * @brief UIController::newGame
 */
void UIController::newGame()
{
    crBkRoll = PokerHelper::MAX_BANK_ROLL;
    updateLCDRoll();
    mainWindow->restartUI();
}

/**
 * Reference to the function declaration
 * @brief UIController::saveGame
 */
void UIController::saveGame()
{
    QString fileName = QFileDialog::getSaveFileName(mainWindow,
                                                    "Save BankRoll", ".",
                                                    "Poker files (*.pk)");

    if (!fileName.isEmpty()){
        if (PokerHelper::saveFile(fileName,crBkRoll, crrBet)){
            updateStatus(fileName + " saved.");
        }else {
            updateStatus(fileName + " cannot be saved!");
        }
    }

}

/**
 * Reference to the function declaration
 * @brief UIController::loadGame
 */
void UIController::loadGame()
{
    QString fileName = QFileDialog::getOpenFileName(mainWindow,
                                                    "Load BankRoll", ".",
                                                    "Poker files (*.pk)");
    if (!fileName.isEmpty()){

        if (PokerHelper::loadFile(fileName,crBkRoll,crrBet)){
            updateStatus(fileName + " loaded.");
        }else{
            updateStatus(fileName + " cannot be loaded! BankRoll = 1");
        }

    }

    updateLCDRoll();
}

/**
 * @brief UIController::exitGame
 */
void UIController::exitGame()
{
    exit(0);
}

/**
 * Reference to the function declaration
 * @brief UIController::stateChanged
 * @param newState
 */
void UIController::stateChanged(QMediaPlayer::State newState)
{
    if (newState == QMediaPlayer::StoppedState){
        bgMusic->play(); // Replay the music
    }
}

