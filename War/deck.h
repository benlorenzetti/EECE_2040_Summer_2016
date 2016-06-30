#ifndef DECK_H
#define DECK_H
/*
  The Deck class implements a random deck of 52 cards.
*/
#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <queue>
#include <vector>   // for shuffle only
#include <stdlib.h> // for rand()
#include "card.h"

using namespace std;

class Deck{  
  private:
  queue<Card> d;

  public:

  unsigned int get_size() const {return d.size();}
  void print_deck() const;

  void add_52_cards();
  void shuffle_deck();
  void collect_deck(Deck &);

  Card draw() {Card c = d.front(); d.pop(); return c;}
  void collect(Card c) {d.push(c);}
  Card table_top() {return d.back();}
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
  queue<Card> d_copy = d;
  while( !d_copy.empty() ){
    cout << d_copy.front() << endl;
    d_copy.pop();
  }
}

void Deck::shuffle_deck() {
  // Copy the stack into a shuffling vector
  vector<Card> shuffle_vector;
  while( !d.empty() ){
    shuffle_vector.push_back(d.front());
    d.pop();
  }
  // The shuffle operation swaps two random cards in the vector and
  // this is repeated n times.
  const int n = 1000;
  for(int i=0; i<n; i++){
    int index1 = rand() % shuffle_vector.size();
    int index2 = rand() % shuffle_vector.size();
    Card temp = shuffle_vector[index1];
    shuffle_vector[index1] = shuffle_vector[index2];
    shuffle_vector[index2] = temp;
  }
  // Copy the cards from the vector back into the stack
  while( !shuffle_vector.empty() ){
    d.push(shuffle_vector.back());
    shuffle_vector.pop_back();
  }
}

void Deck::collect_deck (Deck &d2) {
  while(!d2.d.empty()) {
    d.push(d2.d.front());
    d2.d.pop();
  }
}

#endif
