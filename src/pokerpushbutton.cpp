#include "pokerpushbutton.h"
#include "mainwindow.h"

/**
 * Reference to the function declaration
 * @brief PokerPushButton::PokerPushButton
 * @param ifName: the icon file name
 * @param parent
 */
PokerPushButton::PokerPushButton(const QString ifName, QWidget* parent):QPushButton(parent)
{

    //Make the border transparent
    setFlat(true);

    //Change the currsor symbol
    setCursor(QCursor(Qt::PointingHandCursor));

    //Update the icon if possible
    if (!ifName.isNull()){

        iMovie = new QMovie(ifName);
        connect(iMovie,SIGNAL(frameChanged(int)),this,SLOT(updateIcon(int)));
        iMovie->start();
    }


}

/**
 * Reference to the function declaration
 * @brief PokerPushButton::~PokerPushButton
 */
PokerPushButton::~PokerPushButton()
{
    iMovie->stop();
    disconnect(iMovie,SIGNAL(frameChanged(int)),this,SLOT(updateIcon(int)));
    delete iMovie;
}

/**
 * Reference to the function declaration
 * @brief PokerPushButton::updateIcon
 * @param cFrame
 */
void PokerPushButton::updateIcon(int cFrame)
{
    setIcon(QIcon(iMovie->currentPixmap()));
}





