#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * Reference to the function declaration
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Set a permanent size for this main window and its graphics view
    setFixedSize(geometry().width(),geometry().height());
    ui->graphicsView->setFixedSize(ui->graphicsView->geometry().width()
                                   ,ui->graphicsView->geometry().height());

    //Setting up the main scene in the graphics view of this window
    mainScene = new MainScene(this);
    mainScene->setSceneRect(ui->graphicsView->geometry().topLeft().x()
                            ,ui->graphicsView->geometry().topLeft().y()
                            ,ui->graphicsView->geometry().width()
                            ,ui->graphicsView->geometry().height());

    //Connect the main scene to a view
    ui->graphicsView->setScene(mainScene);

    //Place the Play button on the window
    addPlayButton();

    //Connecting the menu bar actions to the equivalent signals
    connect(ui->actionNew_Game, SIGNAL(triggered()), this, SIGNAL(newGame()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SIGNAL(saveGame()));
    connect(ui->actionLoad_Game, SIGNAL(triggered()), this, SIGNAL(loadGame()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SIGNAL(exitGame()));

    //Set up labels for the bank roll and bet values
    ui->bkLabel->setStyleSheet("QLabel {color: red; }");
    ui->betLabel->setStyleSheet("QLabel {color: red; }");
}

/**
 * Reference to the function declaration
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Reference to the function declaration
 * @brief MainWindow::displayCards
 */
void MainWindow::displayCards(QVector<int> cardIds, bool isPlayer)
{
    mainScene->displayCards(cardIds, isPlayer);
}

/**
 * Reference to the function declaration
 * @brief MainWindow::getRCardIds
 * @return
 */
QVector<int> MainWindow::getRCardIds()
{
    return mainScene->getRCardIds();
}

/**
 * Reference to the function declaration
 * @brief MainWindow::restartUI
 */
void MainWindow::restartUI()
{
    //Clean up main scene by an empty list of Ids
    QVector<int> emptyId;
    mainScene->displayCards(emptyId);
    mainScene->displayCards(emptyId,false);

    //Hide the deal button from the main window
    if (dealBtn != NULL){
        dealBtn->setVisible(false);
    }

    //Place the Play button on the window
    addPlayButton();

    //Clean up the status bar
    ui->statusBar->showMessage("");

    //Clean up the bet value LCD
    ui->betLCD->display(0);

    //Reenable the window
    setEnabled(true);
}


/**
 * Reference to the function declaration
 * @brief MainWindow::getStartButton
 * @return
 */
void MainWindow::addPlayButton()
{
    if (playBtn == NULL){

        playBtn = new PokerPushButton(SBI_FILE_NAME,this);

        //Setting up geometry attributes
        playBtn->setGeometry(QRect(PokerHelper::START_BUTTON_ICON_X,PokerHelper::START_BUTTON_ICON_Y,
                                   PokerHelper::START_BUTTON_ICON_W,PokerHelper::START_BUTTON_ICON_H));

        playBtn->setIconSize(QSize(PokerHelper::START_BUTTON_ICON_W,PokerHelper::START_BUTTON_ICON_H));

        //Register with the Play button to receive the mouse clicked event
        connect(playBtn, SIGNAL(clicked()),this, SLOT(processPlayClicked()));

    }

    playBtn->setVisible(true);

}

/**
 * Reference to the function declaration
 * @brief MainWindow::addDealButton
 */
void MainWindow::addDealButton()
{
    if (dealBtn == NULL){

        dealBtn = new PokerPushButton(DBI_FILE_NAME,this);

        //Setting up geometry attributes
        dealBtn->setGeometry(QRect(PokerHelper::DEAL_BUTTON_ICON_X,PokerHelper::DEAL_BUTTON_ICON_Y,
                                   PokerHelper::DEAL_BUTTON_ICON_W,PokerHelper::DEAL_BUTTON_ICON_H));

        dealBtn->setIconSize(QSize(PokerHelper::DEAL_BUTTON_ICON_W,PokerHelper::DEAL_BUTTON_ICON_H));

        //Display the button on this ui
        dealBtn->show();

        //Register with the Deal button to receive the mouse clicked event
        connect(dealBtn, SIGNAL(clicked()),this, SLOT(processDealClicked()));

    }

    dealBtn->setVisible(true);

}

/**
 * Reference to the function declaration
 * @brief MainWindow::updateLCD
 */
void MainWindow::updateLCD(int bkRoll, int crBet)
{
    ui->bkLCD->display(bkRoll);
    ui->betLCD->display(crBet);
}

/**
 * Reference to the function declaration
 * @brief MainWindow::processPlayClicked
 */
void MainWindow::processPlayClicked()
{
    //Hide the play button from the main window
    playBtn->setVisible(false);

    //Notify the UIController for a game-started signal
    emit startGame();

}

/**
 * Reference to the function declaration
 * @brief MainWindow::processDealClicked
 */
void MainWindow::processDealClicked()
{
    //Notify the UIController for a replace-card signal
    emit replaceCards();
}
