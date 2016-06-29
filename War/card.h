#ifndef CARD_H
#define CARD_H
/*
  Class to hold a playing card.
  You may change anything you like in this file!
*/
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>

using namespace std;

enum suit_t {DIAMONDS, SPADES, HEARTS, CLUBS, NO_TRUMP_SUIT};

class Card{
 private:
  suit_t suit;
  int rank;
  static suit_t trump_suit; // initialized to NO_TRUMP_SUIT
 public:
  const static int ACE_RANK = 14;

 public:
  
  Card(suit_t suit, int rank){
    // Four suits are allowed
    if(suit != DIAMONDS && suit != SPADES && suit != HEARTS && suit != CLUBS){
      throw logic_error("Suit not valid!");
    }
    this->suit = suit;
    // Rank is an interger between 2 and 13 or an ACE, which will usually be
    // declared as either 1 or 14 in ACE_RANK
    if((rank < 2 || rank > 13) && rank != ACE_RANK){
      throw logic_error("Rank out of range!");
    }
    this->rank = rank;
  }
  
  // Getters
  suit_t getSuit() const{ return suit;}
  int getRank() const{ return rank;}
  
  // string variants
  
  string getSuitString() const{
    switch(suit){
      case DIAMONDS: return "Diamonds";
      case SPADES: return "Spades";
      case HEARTS: return "Hearts";
      default: return "Clubs";
    }
  }
  
  string getRankString() const{
    switch(rank){
      case 11: return "Jack";
      case 12: return "Queen";
      case 13: return "King";
      case ACE_RANK: return "Ace";
      default: { 
        stringstream o;
        o << rank;
        return o.str();
      }
    }
  }
  
};

ostream& operator<< (ostream& out, const Card& card){
  out << card.getRankString() << " of " << card.getSuitString();
  return out;
}

// Initialize the trump suit for games which may not have the
// concept of trump suits
suit_t Card::trump_suit = NO_TRUMP_SUIT;


#endif
