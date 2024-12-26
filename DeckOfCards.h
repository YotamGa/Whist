#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H

#include <set>
#include <string>
using namespace std;

enum Suit {
    CLUB,
    DIAMOND,
    HEART,
    SPADE,
    NO_TRUMP
};

enum Rank {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};

class Card {
    enum Suit mySuit;
    enum Rank myRank;
    public:
        Card();
        Card(int s, int n);
        Suit getSuit();
        Rank getNumber();
        bool operator<(const Card& other) const;
    
};

class Deck {
    Card deck[52];
    public:
        Deck();
        Card getCard(int i);
        void shuffleDeck();
        void printDeck();
        set<Card> dealThirteenCards(int start);
};

class Player {
    set<Card> hand;
    string playerName;
    int playerID;
    string password;
    int score;
    int tricks;
    public:
        Player();
        Player(string name);
        void getDealtHand(set<Card> newHand);
        string getPlayerName();
        int getPlayerScore();
        int getPlayerTricks();
// TODO
        
    //     Card playCard(Card card){
    //         TODO
    //     }
       
    //    Card[] passThreeCards(){}
       

};
class Game{
    Player players[4];
    Deck gameDeck;
    set<Card> discardPile;
    Card currentTrick[4];
    int gameID;
    int startingPlayer;
    public:
        Game(int id, Player player1, Player player2, Player player3, Player player4);
        void newGame();
        void bidding();
        void gamePlay();
        // Card getCardFromPlayer(Player playerID){
        //     //TODO
        //     return Card();
        // }

};

#endif