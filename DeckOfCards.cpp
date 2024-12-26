#include <iostream>
#include <random>
#include <set>
#include <cstdlib>
#include <vector>
#include <string>
#include "DeckOfCards.h"
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
        Card() {
            mySuit = static_cast<Suit>(4);
            myRank = static_cast<Rank>(0);
        }
        Card(int s, int n) {
            mySuit = static_cast<Suit>(s);
            myRank = static_cast<Rank>(n);
        }
        Suit getSuit(){
            return mySuit;
        }
        Rank getNumber(){
            return myRank;
        }
        bool operator<(const Card& other) const{
            if(mySuit == other.mySuit){
                return myRank < other.myRank;
            }
            return mySuit < other.mySuit;
        }
    
};

class Deck {
    Card deck[52];
    public:
        Deck() {
            for(int i = 0; i < 52; i++){
                deck[i] = Card(i/13, i%13);
            }
        }
        Card getCard(int i) {
            return deck[i];
        }
        void shuffleDeck(){
            for (int i =0; i < 52; ++i) {
                int spot = rand()%52;
                Card temp = deck[spot];
                deck[spot] =  deck[i];
                deck[i] = temp;
            }

        }
        void printDeck(){
            cout << "Deck is:\n";
            for(int i = 0; i < 52; i++){
                Card card = getCard(i);
                cout << "card is: " << card.getNumber() << " of " << card.getSuit() << "\n";
            }
        }
        set<Card> dealThirteenCards(int start){//makesure it can only be one of the 4ths of the deck
            set<Card> hand;
            for(int i = start; i < start + 13; i++){
                hand.insert(getCard(i));
            }
            return hand;
        }
};

class Player {
    set<Card> hand;
    string playerName;
    int playerID;
    string password;
    int score;
    int tricks;
    public:
        Player(){
            playerName = "NoPlayer";
        }
        Player(string name) {
            playerName = name;
            score = 0;
            tricks = 0;
        }
        void getDealtHand(set<Card> newHand){
            hand = newHand;
        }
        string getPlayerName(){
            return playerName;
        }
        int getPlayerScore(){
            return score;
        }
        int getPlayerTricks(){
            return tricks;
        }
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
        Game(int id, Player player1, Player player2, Player player3, Player player4){
            gameID = id;
            gameDeck = Deck();
            players[0] = player1;
            players[1] = player2;
            players[2] = player3;
            players[3] = player4;
        }
        void newGame(){
            gameDeck.shuffleDeck();
            discardPile.clear();
            players[0].getDealtHand(gameDeck.dealThirteenCards(0));
            players[1].getDealtHand(gameDeck.dealThirteenCards(13));
            players[2].getDealtHand(gameDeck.dealThirteenCards(26));
            players[3].getDealtHand(gameDeck.dealThirteenCards(39));
        }
        void bidding(){
            //TODO
        }
        void gamePlay(){

        }
        // Card getCardFromPlayer(Player playerID){
        //     //TODO
        //     return Card();
        // }

};


int main(){
}