#ifndef POKERCARDTABLE_H
#define	POKERCARDTABLE_H

#include <QVector>
#include <QString>
#include "pokerhelper.h"
#include "pokerclient.h"

/*
 * This class is used for managing user's cards base on the below logical mapping table
 *
 *              0   1   2   3   4   5   6   7   8   9    10    11    12
 * Suits/Ranks  2   3   4   5   6   7   8   9   10  Jack Queen King Ace
 * 0 Hearts     0   1   2   3   4   5   6   7   8   9    10    11    12
 * 1 Diamonds   13  14  15  16  17  18  19  20  21  22   23    24    25
 * 2 Clubs      26  27  28  29  30  31  32  33  34  35   36    37    38
 * 3 Spades     39  40  41  42  43  44  45  46  47  48   49    50    51
 */
class PokerCardTable {

private:

    /*
     * There are thirteen ranks per suit: from Ace to King.
     */
    enum CARD_RANKS {
        TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE
    };

    /*
     * There are four suits in fifty two desk cards.
     */
    enum CARD_SUITS {
        HEARTS, DIAMONDS, CLUBS, SPADES
    };

    /*
     * The total of cards are 52
     */
    static const int CARDS_TOTAL = 52;

    /*
     * There are thirteen ranks per suit.
     */
    static const int RANKS_PER_SUIT = 13;

    /*
     * Maximum poker cards for each player.
     */
    static const int FIVE_POKER_CARDS = 5;

    /*
     * There are 4 suits in 52 desk cards.
     */
    static const int SUIT_MAX = 4;

    /*
     * The first poker card index
     */
    static const int INDEX_0 = 0;

    /*
     * The second poker card index
     */
    static const int INDEX_1 = 1;

    /*
     * The third poker card index
     */
    static const int INDEX_2 = 2;

    /*
     * The fourth poker card index
     */
    static const int INDEX_3 = 3;

    /*
     * The fifth poker card index
     */
    static const int INDEX_4 = 4;

    /*
     * The base score of a royal flush
     */
    static const int ROYAL_FLUSH_SCORE = 10000000;

    /*
     * The base score of a straight flush
     */
    static const int STRAIGHT_FLUSH_SCORE = 9000000;

    /*
     * The base score of Four of a Kind
     */
    static const int FOUR_OF_A_KIND_SCORE = 8000000;

    /*
     * The base score of Full House
     */
    static const int FULL_HOUSE_SCORE = 7000000;

    /*
     * The base score of a Flush
     */
    static const int FLUSH_SCORE = 6000000;

    /*
     * The base score of a Straight
     */
    static const int STRAIGHT_SCORE = 5000000;

    /*
     * The base score of Three of a Kind
     */
    static const int THREE_OF_A_KIND_SCORE = 4000000;

    /*
     * The base score of Two Pairs
     */
    static const int TWO_PAIR_SCORE = 3000000;

    /*
     * The base score of a Pair
     */
    static const int A_PAIR_SCORE = 2000000;

    /*
     * The coefficient is used for calculating a player's score
     */
    static const int BASE_SCORE = 10;

    /*
     * A card is defined by a combination of rank and suit.
     * The id is the index of a card in fifty two desk cards
     */
    typedef struct CARD {
        int id;
        CARD_SUITS suit;
        CARD_RANKS rank;

    } Card;

    /*
     * Vector contains all the user's current cards
     */
    QVector<Card*> crCards;

    /*
     * Vector contains all the current dealer cards
     */
    QVector<Card*> crDCrds;

    /*
     * Vector contains all the user's current cards sorted by rank
     */
    QVector<Card*> crSRnks;

    /*
     * Vector contains all the user's current cards sorted by suit
     */
    QVector<Card*> crSSuits;

    /*
     *  The message is used to notify the player for game result
     */
    QString gRltMss = "";

    /*
     * The Poker client that manages the TCP connections to the Poker server
     */
    PokerClient* pokClnt;

public:

    /**
     * The default constructor of PokerCardTable
     */
    PokerCardTable();

    /**
     * The default destructor of PokerCardTable
     */
    ~PokerCardTable();

    /**
     * This function deals first five poker cards for the player as well as the dealer
     */
    void dealsCards();

    /**
     * This function returns the Ids of all current player's cards
     * @brief getCrCardIds
     * @return a vector of the current card Ids
     */
    QVector<int> getCrCardIds();

    /**
     * This function returns the Ids of all current dealer's cards
     * @brief getCrCardIds
     * @return a vector of the current card Ids
     */
    QVector<int> getCrDCardIds();

    /**
     * This functions collects all the cards user want to replace and
     * replaces them with new ones
     * @brief replaceCards
     * @param repIds : The Ids of cards that need replacing
     */
    void replaceCards(QVector<int> repIds);

    /**
     * The game result message getter
     * @brief getGameResult
     * @return the final game result message
     */
    PokerHelper::GAME_BOOL getGameResult(QString& message);

private:
    /**
     * This function create a Card by mapping the id to a Card structure through
     * the logical Card Table
     * @param id
     * @return Card
     */
    Card* populateCardBy(int id);

    /**
     * This function uses the id to check if a card has been dealt
     * @param id : the Card Table index
     * @return true/false : A card is existed or not
     */
    bool isCardExistedBy(int id);

    /**
     * This function generates a new card for the replacing process.
     * The new one should not be duplicated with any card in the current hand
     * @return a new Card structure
     */
    Card* dealsNewCard();

    /**
     * This function generates a new one that has not been dealt before
     * for the replacement process
     * @return a new Card structure
     */
    Card* getNewCardForReplacement();

    /**
     * This functions creates a list of current hand cards sorted by rank.
     */
    void sortCardsByRank(const QVector<Card*>& cards);

    /**
     * This functions creates a list of current hand cards sorted by suit.
     */
    void sortCardsBySuit(const QVector<Card*>& cards);

    /**
     * This functions check if there is an ACE, and all five poker cards are flush and straight
     * @return true/false
     */
    bool isRoyalFlush();

    /**
     * This functions check if all five poker card are flush and straight
     * @return true/false
     */
    bool isStraightFlush();

    /**
     * This function checks if all five poker cards have the same suit.
     * After sorting by suit, if the lowest card has the same suit as the highest one,
     * then all five poker cards will have the same suit.
     * @return true/false
     */
    bool isFlush();

    /**
     * This function checks if all five poker cards make a straight:
     * Case 1: There is an ACE and the other fours are {TEN, JACK, QUEEN, KING}
     *                                              or {TWO, THREE, FOUR, FIVE}
     * Case 2: The ranks of all cards are increasing continuously
     * @return true/false
     */
    bool isStraight();

    /**
     * This function checks for four of the same card in a rank
     * Two cases: 4 + 1 or 1 + 4
     * @return true/false
     */
    bool isFourOfAKind();

    /**
     * This function checks for 3 of the same card in a rank
     * and 2 of the same card in another rank
     * Two cases: 3 + 2 or 2 + 3
     * @return true/false
     */
    bool isFullHouse();

    /**
     * This function checks for 3 of the same card after checking four of a kind and full house.
     * Three cases: 3 + 1 + 1 or
     *              1 + 3 + 1 or
     *              1 + 1 + 3.
     * @return true/false
     */
    bool isThreeOfAKind();

    /**
     * This function checks for 2 different pairs after checking four of a kind, full house,
     * and three of a kind.
     * Three cases: 2 + 2 + 1 or
     *              2 + 1 + 2 or
     *              1 + 2 + 2.
     * @return true/false
     */
    bool isTwoPairs();

    /**
     * This function checks for two of the same card after checking four of a kind, full house,
     * three of a kind and two pairs
     * Four cases: 2 + 1 + 1 + 1 or
     *             1 + 2 + 1 + 1 or
     *             1 + 1 + 2 + 1 or
     *             1 + 1 + 1 + 2 or
     * @return true/false
     */
    bool isPair();

    /**
     * This function checks if the current hand win or lose
     * @return  -1/0/1:  /drawn/lose/win/
     */
    PokerHelper::GAME_BOOL isPlayerWin();

    /**
     * This function deallocates the memories of a set of elements in cards and clears the cards
     * @param cards : a vector of Card Structure pointers
     * @param poss : a set of positions in cards
     */
    void deleteCardsBy(QVector<Card*>& cards, QVector<int> poss);

    /**
     * This function deallocates the memories of all elements in cards and clears the cards
     * @param cards : a vector of Card Structure pointers
     */
    void deleteCards(QVector<Card*>& cards);

    /**
     *  This function reset all the current cards for a new game
     */
    void clean();

    /**
     * This function calculates the total raw score of cards in a hand base on CARD_RANKS enum
     * @param cards
     * @return the total raw score of cards in a hand
     */
    int getRawScore();

    /**
     * This function calculates the total score of cards in a hand by:
     * 10^4*the-first-highest-rank + 10^3*the-second-highest-rank
     * + 10^2*the-third-highest-rank + 10^1-the-fourth-highest-rank + the-lowest-rank
     * @param cards
     * @return the total score of cards in a hand
     */
    int getHandScore();

    /**
     * This function calculates the total Royal Flush score of cards in a hand
     * @param cards
     * @return
     */
    int getRoyalFlushScore();

    /**
     * This function calculates the total Straight Flush score of cards in a hand
     * @param cards
     * @return
     */
    int getStraightFlushScore();

    /**
     * This function calculates the total Flush score of cards in a hand
     * @param cards
     * @return
     */
    int getFlushScore();

    /**
     * This function calculates the total Flush score of cards in a hand
     * @param cards
     * @return
     */
    int getStraightScore();

    /**
     * This function calculates the total Four Of A Kind score of cards in a hand
     * @param cards
     * @return
     */
    int getFourOfAKindScore();

    /**
     * This function calculates the total Full House score of cards in a hand
     * @param cards
     * @return
     */
    int getFullHouseScore();

    /**
     * This function calculates the total Three Of A Kind score of cards in a hand
     * @param cards
     * @return
     */
    int getThreeOfAKindScore();

    /**
     * This function calculates the total Two Pair score of cards in a hand by:
     * TWO_PAIR_SCORE + 10^2*First-High-Two-Pair + 10*Second-High-Two-Pair +  Low-Card
     * @param cards
     * @return
     */
    int getTwoPairScore();

    /**
     * This function calculates the total Pair score of cards in a hand by:
     * A_PAIR_SCORE + 10^3*A-Pair + 10^2*First-High-Card + 10*Second-High-Card + Low-Card
     * @param cards
     * @return
     */
    int getAPairScore();

    /**
     * This function calculates the final Poker score of cards in a hand base on the wining conditions
     * @param cards
     * @return The final Poker score
     */
    int calPokerScore(const QVector<Card*>& cards);

};

#endif	/* POKERCARDTABLE_H */

