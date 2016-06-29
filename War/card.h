#ifndef CARD_H
#define CARD_H
/*
  Class to hold a playing card.
*/
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
using namespace std;

enum suit_t {DIAMONDS, SPADES, HEARTS, CLUBS, NO_TRUMP_SUIT};

class Card{
  private:
    int rank;
    suit_t suit;
    static suit_t trump_suit;
    const static int ACE_RANK = 14; // should be set to either 1 or 14
  
  public:

  /* Card Constructor
     param1: the suit, either DIAMONDS, SPADES, HEARTS, or CLUBS
     param2: number of the card, or 1 for Ace, 11=Jack, 12=Queen, 13=King
  */
  Card(suit_t,int);
  
  // Getters
  suit_t getSuit() const /*....................*/ {return suit;}
  int getRank() const /*.......................*/ {return rank;}
  string getSuitString() const;
  string getRankString() const;
 
  // Setters
  static void setTrumpSuit(suit_t trump) /*....*/ {trump_suit = trump;}
   
  /* Compare Cards
   
  */
  int compare(const Card &rhs) const;

  bool operator<(const Card &rhs) const /*.....*/ {return (compare(rhs) < 0);}
  bool operator>(const Card &rhs) const /*.....*/ {return (compare(rhs) > 0);}
  bool operator==(const Card &rhs) const /*....*/ {return (compare(rhs) == 0);}
  bool operator<=(const Card &rhs) const /*....*/ {return (compare(rhs) <= 0);}
  bool operator>=(const Card &rhs) const /*....*/ {return (compare(rhs) >= 0);}
};

// Initialize trump_suit for games which may not have the  concept of trump
suit_t Card::trump_suit = NO_TRUMP_SUIT;

// Overload of the stream operator for printing cards
ostream& operator<< (ostream& out, const Card& card){
  out << card.getRankString() << " of " << card.getSuitString();
  return out;
}

// Longer Function Implementations

Card::Card(suit_t suit, int rank){
  // Four suits are allowed
  if(suit != DIAMONDS && suit != SPADES && suit != HEARTS && suit != CLUBS){
    throw logic_error("Suit not valid!");
  }
  this->suit = suit;
  // Rank is an interger between 2 and 13 or an ACE, which will usually be
  // declared as either 1 or 14 in ACE_RANK
  if(rank == 1 || rank == 14){
    this->rank = ACE_RANK;
  }
  else if(rank >= 2 && rank <= 13){
    this->rank = rank;
  }
  else{
    throw logic_error("Rank out of range!");
  }
}
  
 
string Card::getSuitString() const{
  switch(suit){
    case DIAMONDS: return "Diamonds";
    case SPADES: return "Spades";
    case HEARTS: return "Hearts";
    default: return "Clubs";
  }
}
  
string Card::getRankString() const{
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
  
int Card::compare(const Card &rhs) const{
  int lhs_val = rank + (suit == trump_suit ? 16 : 0);
  int rhs_val = rhs.rank + (rhs.suit == trump_suit ? 16 : 0);
  return lhs_val - rhs_val;
}

#endif
