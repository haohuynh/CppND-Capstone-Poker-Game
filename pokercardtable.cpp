#include "PokerCardTable.h"
#include <time.h>
#include <QDebug>

/**
 * Reference to the declaration
 */
PokerCardTable::PokerCardTable() {

    //Seeding a value for the random function
    srand(time(NULL));

    //Creates a new TCP connection object
    pokClnt = new PokerClient();
}

/**
 * Reference to the declaration
 */
PokerCardTable::~PokerCardTable() {
    //Free all the allocated memories
    clean();
}

/**
 * Reference to the declaration
 */
void PokerCardTable::dealsCards() {

    //Clean up all components before dealing new sets of cards
    clean();

    //Deal card for both player and dealer
    for (int i = 0; i < FIVE_POKER_CARDS; i++) {
        crCards.push_back(dealsNewCard());
        crDCrds.push_back(dealsNewCard());
    }

}

/**
 * Reference to the declaration
 * @brief PokerCardTable::getCrCardIds
 * @return
 */
QVector<int> PokerCardTable::getCrCardIds()
{
    QVector<int> result;

    for (int i = 0; i < crCards.size(); ++i) {
        result.append(crCards[i]->id);
    }

    return result;
}

/**
 * Reference to the declaration
 * @brief PokerCardTable::getCrDCardIds
 * @return
 */
QVector<int> PokerCardTable::getCrDCardIds()
{
    QVector<int> result;

    for (int i = 0; i < crDCrds.size(); ++i) {
        result.append(crDCrds[i]->id);
    }

    return result;
}

/**
 * Reference to the declaration of this function
 * @brief PokerCardTable::replaceCards
 * @param repIds
 */
void PokerCardTable::replaceCards(QVector<int> repIds)
{
    /*
     * Create a copy of all current hand cards, because crCards will be used for
     * containing the first five cards and new cards for the replacement process.
     */
    QVector<Card*> bkCrCds(crCards);


    //Do actual replacements on bkCrCds
    //while use crCards to store all cards have been dealt
    for (int i = 0; i < repIds.size(); ++i) {
        bkCrCds[repIds[i]] = getNewCardForReplacement();
    }

    //Deallocate the memories of the replaced cards
    deleteCardsBy(crCards, repIds);

    //The replacement process is done and crCards show have a new combination of only five cards
    crCards = bkCrCds;

}

/**
 * Reference to the declaration
 * @brief PokerCardTable::getGameResult
 * @return
 */
PokerHelper::GAME_BOOL PokerCardTable::getGameResult(QString& message)
{
    PokerHelper::GAME_BOOL result = isPlayerWin();
    message = gRltMss;
    return result;
}

/**
 * Reference to the declaration
 * @param index
 * @return
 */
PokerCardTable::Card* PokerCardTable::populateCardBy(int id) {
    Card* card = new Card;
    card->id = id;
    card->suit = static_cast<CARD_SUITS> (id / RANKS_PER_SUIT);
    card->rank = static_cast<CARD_RANKS> (id % RANKS_PER_SUIT);
    return card;
}

/**
 * Reference to the declaration
 * @param index
 * @return
 */
bool PokerCardTable::isCardExistedBy(int id) {

    int index;
    int size = crCards.size();
    //Check all current player's cards
    for (index = 0; index < size; index++) {

        if (id == crCards[index]->id) {
            return true;
        }
    }

    size = crDCrds.size();
    //Check all current dealer 's cards
    for (index = 0; index < size; index++) {

        if (id == crDCrds[index]->id) {
            return true;
        }
    }

    return false;
}

/**
 * Reference to the declaration
 */
PokerCardTable::Card* PokerCardTable::dealsNewCard() {

    int randId;

    do {
        randId = rand() % CARDS_TOTAL;
    } while (isCardExistedBy(randId));

    return populateCardBy(randId);

}

/**
 * Reference to the declaration
 * @param index
 */
PokerCardTable::Card* PokerCardTable::getNewCardForReplacement() {
    Card* newCard = dealsNewCard();

    //Collecting all cards that have been dealt to assure that there is no duplication happens
    crCards.push_back(newCard);

    return newCard;
}

/**
 * Reference to the declaration
 * @brief PokerCardTable::sortCardsByRank
 * @param cards
 */
void PokerCardTable::sortCardsByRank(const QVector<Card*>& cards) {

    QVector<Card*>::iterator cardIt;
    crSRnks.clear();

    for (int i = 0; i < FIVE_POKER_CARDS; i++) {

        for (cardIt = crSRnks.begin(); (cardIt != crSRnks.end())
             && ((*cardIt)->rank < cards[i]->rank); cardIt++);

        crSRnks.insert(cardIt, cards[i]);
    }
}

/**
 * Reference to the declaration
 * @brief PokerCardTable::sortCardsBySuit
 * @param cards
 */
void PokerCardTable::sortCardsBySuit(const QVector<Card*>& cards) {

    QVector<Card*>::iterator cardIt;
    crSSuits.clear();

    for (int i = 0; i < FIVE_POKER_CARDS; i++) {

        for (cardIt = crSSuits.begin(); (cardIt != crSSuits.end())
             && ((*cardIt)->suit < cards[i]->suit); cardIt++);

        crSSuits.insert(cardIt, cards[i]);
    }
}

/**
 * Reference to the declaration
 * @return true/false
 */
bool PokerCardTable::isRoyalFlush() {
    return ((crSRnks[INDEX_4]->rank == ACE) && isStraightFlush());
}

/**
 * Reference to the declaration
 * @return true/false
 */
bool PokerCardTable::isStraightFlush() {
    return (isFlush() && isStraight());
}

/**
 * Reference to the declaration
 * @return true/false
 */
bool PokerCardTable::isFlush() {
    return (crSSuits[INDEX_0]->suit == crSSuits[INDEX_4]->suit);
}

/**
 * Reference to the declaration
 * @return true/false
 */
bool PokerCardTable::isStraight() {

    if (crSRnks[INDEX_4]->rank == ACE) { //Case 1 {TEN, JACK, QUEEN, KING, ACE}
        //or {TWO, THREE, FOUR, FIVE, ACE}

        if (crSRnks[INDEX_0]->rank == TEN && crSRnks[INDEX_1]->rank == JACK
                && crSRnks[INDEX_2]->rank == QUEEN && crSRnks[INDEX_3]->rank == KING) {
            return true;
        }

        if (crSRnks[INDEX_0]->rank == TWO && crSRnks[INDEX_1]->rank == THREE
                && crSRnks[INDEX_2]->rank == FOUR && crSRnks[INDEX_3]->rank == FIVE) {
            return true;
        }

        return false;

    } else {//Case 2 Continuously Increasing
        //rc: A rank counter
        for (int rc = (crSRnks[INDEX_0]->rank + 1), i = 1; i < FIVE_POKER_CARDS; rc++, i++) {
            if (rc != crSRnks[i]->rank) {
                return false;
            }
        }
        return true;
    }

}

/**
 * Reference to the declaration
 * @return true/false
 */
bool PokerCardTable::isFourOfAKind() {

    //Case: 4 + 1
    if ((crSRnks[INDEX_0]->rank == crSRnks[INDEX_1]->rank)
            && (crSRnks[INDEX_1]->rank == crSRnks[INDEX_2]->rank)
            && (crSRnks[INDEX_2]->rank == crSRnks[INDEX_3]->rank)) {
        return true;
    }

    //Case 1 + 4
    if ((crSRnks[INDEX_1]->rank == crSRnks[INDEX_2]->rank)
            && (crSRnks[INDEX_2]->rank == crSRnks[INDEX_3]->rank)
            && (crSRnks[INDEX_3]->rank == crSRnks[INDEX_4]->rank)) {
        return true;
    }

    return false;
}

/**
 * Reference to the declaration
 * @return true/false
 */
bool PokerCardTable::isFullHouse() {

    //Case 3 + 2
    if ((crSRnks[INDEX_0]->rank == crSRnks[INDEX_1]->rank)
            && (crSRnks[INDEX_1]->rank == crSRnks[INDEX_2]->rank)
            && (crSRnks[INDEX_3]->rank == crSRnks[INDEX_4]->rank)) {
        return true;
    }

    //Case 2 + 3
    if ((crSRnks[INDEX_0]->rank == crSRnks[INDEX_1]->rank)
            && (crSRnks[INDEX_2]->rank == crSRnks[INDEX_3]->rank)
            && (crSRnks[INDEX_3]->rank == crSRnks[INDEX_4]->rank)) {
        return true;
    }

    return false;
}

/**
 * Reference to the declaration
 * @return true/false
 */
bool PokerCardTable::isThreeOfAKind() {

    //Case 3 + 1 + 1
    if ((crSRnks[INDEX_0]->rank == crSRnks[INDEX_1]->rank)
            && (crSRnks[INDEX_1]->rank == crSRnks[INDEX_2]->rank)) {
        return true;
    }

    //Case 1 + 3 + 1
    if ((crSRnks[INDEX_1]->rank == crSRnks[INDEX_2]->rank)
            && (crSRnks[INDEX_2]->rank == crSRnks[INDEX_3]->rank)) {
        return true;
    }

    //Case 1 + 1 + 3
    if ((crSRnks[INDEX_2]->rank == crSRnks[INDEX_3]->rank)
            && (crSRnks[INDEX_3]->rank == crSRnks[INDEX_4]->rank)) {
        return true;
    }

    return false;
}

/**
 * Reference to the declaration
 * @return true/false
 */
bool PokerCardTable::isTwoPairs() {

    //Case 2 + 2 + 1
    if ((crSRnks[INDEX_0]->rank == crSRnks[INDEX_1]->rank)
            && (crSRnks[INDEX_2]->rank == crSRnks[INDEX_3]->rank)) {
        return true;
    }

    //Case 2 + 1 + 2
    if ((crSRnks[INDEX_0]->rank == crSRnks[INDEX_1]->rank)
            && (crSRnks[INDEX_3]->rank == crSRnks[INDEX_4]->rank)) {
        return true;
    }

    //Case 1 + 2 + 2
    if ((crSRnks[INDEX_1]->rank == crSRnks[INDEX_2]->rank)
            && (crSRnks[INDEX_3]->rank == crSRnks[INDEX_4]->rank)) {
        return true;
    }

    return false;
}

/**
 * Reference to the declaration
 * @return true/false
 */
bool PokerCardTable::isPair() {

    //Case: 2 + 1 + 1 + 1
    if (crSRnks[INDEX_0]->rank == crSRnks[INDEX_1]->rank) {
        return true;
    }

    //Case: 1 + 2 + 1 + 1
    if (crSRnks[INDEX_1]->rank == crSRnks[INDEX_2]->rank) {
        return true;
    }

    //Case: 1 + 1 + 2 + 1
    if (crSRnks[INDEX_2]->rank == crSRnks[INDEX_3]->rank) {
        return true;
    }

    //Case: 1 + 1 + 1 + 2
    if (crSRnks[INDEX_3]->rank == crSRnks[INDEX_4]->rank) {
        return true;
    }

    return false;
}

/**
 * Reference to the declaration
 * @return  -1/0/1:  /drawn/lose/win/
 */
PokerHelper::GAME_BOOL PokerCardTable::isPlayerWin() {

    gRltMss += "The player's result:\n";
    int plyrScr = calPokerScore(crCards); //Calculate the final score of the player
    gRltMss += "Poker score: " + QString::number(plyrScr);

    // Display dealer 's score
    gRltMss += "\n\nThe dealer's result:\n";
    int dlerScr = calPokerScore(crDCrds); //Calculate the final score of the dealer
    gRltMss += "Poker score: " + QString::number(dlerScr);


    if (plyrScr > dlerScr) {
        gRltMss += "\n\nCongratulation! You are the winner !!!\n";
        pokClnt->save("Player",plyrScr); // Implicit saving process for future analyzing
        return PokerHelper::WIN;

    } else if (plyrScr < dlerScr) {
        gRltMss += "\n\nYou lose!\n";
        pokClnt->save("Dealer",dlerScr); // Implicit saving process for future analyzing
        return PokerHelper::LOSE;
    }

    gRltMss += "\n\nDrawn game!!\n";
    return PokerHelper::DRAWN;
}

/**
 * Reference to the declaration
 * @param cards : a vector of Card Structure pointers
 * @param poss : a vector of positions in cards
 */
void PokerCardTable::deleteCardsBy(QVector<Card*>& cards, QVector<int> poss) {

    for (int i = 0; i < poss.size(); ++i) {
        delete cards[poss[i]];
    }

    poss.clear();
    cards.clear();
}

/**
 * Reference to the declaration
 * @param cards : a vector of Card Structure pointers
 */
void PokerCardTable::deleteCards(QVector<Card*>& cards) {
    int size = cards.size();

    for (int i = 0; i < size; i++) {
        delete cards[i];
    }

    cards.clear();
}

/**
 * Reference to the declaration
 */
void PokerCardTable::clean() {

    //Clean up crCards & cdDCards for a new game
    deleteCards(crCards);
    deleteCards(crDCrds);

    //Both crSRnks and crSSuits reference to the same memories in crCards
    crSRnks.clear();
    crSSuits.clear();

    //Clean up the game result message
    gRltMss = "";
}

/**
 * Reference to the declaration
 * @return
 */
int PokerCardTable::getRawScore()
{
    int sum = 0;

    for (int i = 0; i < crSRnks.size(); i++) {
        sum += crSRnks[i]->rank;
    }

    return sum;
}

/**
 * Reference to the declaration
 * @return
 */
int PokerCardTable::getHandScore() {

    int sum = crSRnks[INDEX_0]->rank;
    int e = BASE_SCORE;

    for (int i = 1; i < crSRnks.size(); i++) {
        sum += e * crSRnks[i]->rank;
        e *= BASE_SCORE;
    }

    return sum;
}

/**
 * Reference to the declaration
 * @return
 */
int PokerCardTable::getRoyalFlushScore() {
    return ROYAL_FLUSH_SCORE + getHandScore();
}

/**
 * Reference to the declaration
 * @return
 */
int PokerCardTable::getStraightFlushScore() {
    return STRAIGHT_FLUSH_SCORE + getHandScore();
}

/**
 * Reference to the declaration
 * @return
 */
int PokerCardTable::getFlushScore() {
    return FLUSH_SCORE + getHandScore();
}

/**
 * Reference to the declaration
 * @return
 */
int PokerCardTable::getStraightScore() {
    return STRAIGHT_SCORE + getHandScore();
}

/**
 * Reference to the declaration
 * @return
 */
int PokerCardTable::getFourOfAKindScore() {
    return FOUR_OF_A_KIND_SCORE + crSRnks[INDEX_2]->rank;
}

/**
 * Reference to the declaration
 * @return
 */
int PokerCardTable::getFullHouseScore() {
    return FULL_HOUSE_SCORE + crSRnks[INDEX_2]->rank;
}

/**
 * Reference to the declaration
 * @return
 */
int PokerCardTable::getThreeOfAKindScore() {
    return THREE_OF_A_KIND_SCORE + crSRnks[INDEX_2]->rank;
}

/**
 * Reference to the declaration
 * @return
 */
int PokerCardTable::getTwoPairScore() {
    int sum = 0;

    if ((crSRnks[INDEX_0]->rank == crSRnks[INDEX_1]->rank)
            && (crSRnks[INDEX_2]->rank == crSRnks[INDEX_3]->rank)) {
        //Case 2 + 2 + 1
        sum = crSRnks[INDEX_4]->rank + (BASE_SCORE * crSRnks[INDEX_0]->rank)
                + (BASE_SCORE * BASE_SCORE * crSRnks[INDEX_2]->rank);

    } else if ((crSRnks[INDEX_0]->rank == crSRnks[INDEX_1]->rank)
               && (crSRnks[INDEX_3]->rank == crSRnks[INDEX_4]->rank)) {
        //Case 2 + 1 + 2
        sum = crSRnks[INDEX_2]->rank + (BASE_SCORE * crSRnks[INDEX_0]->rank)
                + (BASE_SCORE * BASE_SCORE * crSRnks[INDEX_3]->rank);
        ;
    } else {//Case 1 + 2 + 2

        sum = crSRnks[INDEX_0]->rank + (BASE_SCORE * crSRnks[INDEX_1]->rank)
                + (BASE_SCORE * BASE_SCORE * crSRnks[INDEX_3]->rank);

    }

    return TWO_PAIR_SCORE + sum;
}

/**
 * Reference to the declaration
 * @return
 */
int PokerCardTable::getAPairScore() {

    int sum = 0;
    //Case: 2 + 1 + 1 + 1
    if (crSRnks[INDEX_0]->rank == crSRnks[INDEX_1]->rank) {

        sum = crSRnks[INDEX_2]->rank + BASE_SCORE * crSRnks[INDEX_3]->rank
                + BASE_SCORE * BASE_SCORE * crSRnks[INDEX_4]->rank
                + BASE_SCORE * BASE_SCORE * BASE_SCORE * crSRnks[INDEX_1]->rank;

    } else if (crSRnks[INDEX_1]->rank == crSRnks[INDEX_2]->rank) {
        //Case: 1 + 2 + 1 + 1
        sum = crSRnks[INDEX_0]->rank + BASE_SCORE * crSRnks[INDEX_3]->rank
                + BASE_SCORE * BASE_SCORE * crSRnks[INDEX_4]->rank
                + BASE_SCORE * BASE_SCORE * BASE_SCORE * crSRnks[INDEX_1]->rank;

    } else if (crSRnks[INDEX_2]->rank == crSRnks[INDEX_3]->rank) {
        //Case: 1 + 1 + 2 + 1
        sum = crSRnks[INDEX_0]->rank + BASE_SCORE * crSRnks[INDEX_1]->rank
                + BASE_SCORE * BASE_SCORE * crSRnks[INDEX_4]->rank
                + BASE_SCORE * BASE_SCORE * BASE_SCORE * crSRnks[INDEX_2]->rank;

    } else {
        //Case: 1 + 1 + 1 + 2
        sum = crSRnks[INDEX_0]->rank + BASE_SCORE * crSRnks[INDEX_1]->rank
                + BASE_SCORE * BASE_SCORE * crSRnks[INDEX_2]->rank
                + BASE_SCORE * BASE_SCORE * BASE_SCORE * crSRnks[INDEX_3]->rank;
    }

    return A_PAIR_SCORE + sum;
}

/**
 * Reference to the declaration
 * @param cards
 * @return
 */
int PokerCardTable::calPokerScore(const QVector<Card*>& cards) {
    //Sorting the current cards for checking a result
    sortCardsByRank(cards);
    sortCardsBySuit(cards);

    if (isRoyalFlush()) {

        gRltMss += "A Royal Flush!!!\n";
        return getRoyalFlushScore();

    }

    if (isStraightFlush()) {
        gRltMss += "A Straight Flush!!\n";
        return getStraightFlushScore();

    }

    if (isFlush()) {
        gRltMss += "A Flush!\n";
        return getFlushScore();
    }

    if (isStraight()) {
        gRltMss += "A Straight!\n";
        return getStraightScore();
    }

    if (isFourOfAKind()) {
        gRltMss += "Four of the same kind!\n";
        return getFourOfAKindScore();
    }

    if (isFullHouse()) {
        gRltMss += "Full house!\n";
        return getFullHouseScore();

    }

    if (isThreeOfAKind()) {
        gRltMss += "Three of the same kind!\n";
        return getThreeOfAKindScore();
    }

    if (isTwoPairs()) {
        gRltMss += "Two pairs!\n";
        return getTwoPairScore();
    }

    if (isPair()) {
        gRltMss += "A pair!\n";
        return getAPairScore();
    }

    gRltMss += "Raw ";
    return getRawScore();

}
