#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsScene>
#include <QtGui>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

/**
 * @brief The MainScene class
 * This is the main graphics scene of the game
 * It is used to manage all the items (Cards and QPushButton) as well as the background
 */
class MainScene : public QGraphicsScene
{
private:

    /*Path to the back ground image*/
    const QString BG_FILE_NAME = ":/Images/PokerGameDesk.jpg";

    /*The prefix of the path to card images*/
    const QString CARD_FILE_NAME_PREFIX = ":/Images/PokerCard";

    /*The suffix of the path to card images*/
    const QString CARD_FILE_NAME_SUFFIX = ".png";

    /*The total number of cards*/
    const int MAXIMUM_CARD_NUMBER = 52;

    /*The Background Image Object*/
    QImage bgImage;

    /*A vetors of all possible card images*/
    QVector<QGraphicsPixmapItem *> crdImgs;

    /*A vetors of all five displayed card images*/
    QVector<QGraphicsPixmapItem *> crCrdIs;

    /*A vetors of all five displayed card images belong to dealer*/
    QVector<QGraphicsPixmapItem *> crDCdIs;

    /*
     * The default positions of five porker cards on the scene
     */
    QVector<QPoint> crdPoss;

    /*
     * The default positions of five dealer's cards on the scene
     */
    QVector<QPoint> dCdPoss;

    /*
     * The exchanged area that used for replacing cards
     */
    QGraphicsRectItem* exArea;

public:

    /**
     * The main constructor is uesed for initating all components in this scene
     */
    MainScene(QObject *parent = 0);

    /**
     * This function displays five poker cards on the scene
     * @brief displayCards
     * @param cardIds
     * @param isPlayer
     */
    void displayCards(QVector<int> cardIds, bool isPlayer = true);

    /**
     * This function checks the GUI (the Deck) for the card that need replacing
     * @brief getRCardIds
     * @return The Ids of cards need replacing
     */
    QVector<int> getRCardIds();

protected:
    /**
     * Overriding function from QGraphicsScene
     * This function will draw the background being one of three layers of the scene
     * @brief drawBackground
     * @param painter
     * @param rect
     */
    void drawBackground(QPainter *painter, const QRectF &rect);

private:

    /**
     * This function loads all 52 card images into a vector of pixmap items
     * @brief loadCardImages
     */
    void loadCardImages();

    /**
     * This function prepares default positions for the five porker cards on the desk
     * @brief assignCardSlots
     */
    void assignCardSlots();

    /**
     * This function prepares default positions for the five dealer's cards on the desk
     * @brief assignCardSlots
     */
    void assignDealerCardSlots();

    /**
     * Clean up the displayed cards before representing new ones on the UI
     * @brief removeCards
     * @param cImages
     */
    void removeCards(QVector<QGraphicsPixmapItem *>& cImages);

signals:

public slots:
};

#endif // MAINSCENE_H
