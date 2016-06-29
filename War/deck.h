#ifndef DECK_H
#define DECK_H
/*
  The Deck class implements a random deck of 52 cards.
*/
#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <stack>
#include "card.h"

using namespace std;

class Deck{  
  private:
  stack<Card> d;

  public:

  int getSize() const {return d.size();}
  void print_deck() const;

  void add_52_cards();
  void shuffle_deck();
  void swap_decks(Deck &);

  Card draw() {Card c = d.top(); d.pop(); return c;}
  void collect(Card c) {d.push(c);}
};

void Deck::add_52_cards() {
  for(int i=0; i<52; i++) {
    int rank = i % 13 + 1;
    suit_t suit;
    switch (i/13) {
      case 0: suit = DIAMONDS; break;
      case 1: suit = SPADES; break;
      case 2: suit = HEARTS; break;
      case 3: suit = CLUBS; break;
    }
    d.push(Card(suit, rank));
  }
}

void Deck::print_deck() const{
  stack<Card> d_copy = d;
  while( !d_copy.empty() ){
    cout << d_copy.top() << endl;
    d_copy.pop();
  }
}

void Deck::shuffle_deck() {

}

void Deck::swap_decks (Deck &d2) {
  stack<Card> inverted_d1, inverted_d2;
  while( !d.empty() ){
    inverted_d1.push( d.top() );
    d.pop();
  }
  while( !d2.d.empty() ){
    inverted_d2.push( d2.d.top() );
    d2.d.pop();
  }
  while( !inverted_d1.empty() ){
    d.push( inverted_d1.top() );
    inverted_d1.pop();
  }
  while( !inverted_d2.empty() ){
    d2.d.push( inverted_d2.top() );
    inverted_d2.pop();
  }
}

#endif
