#include <iostream>

/*
  The file implements main to simulate 100000 games of war.  It should print out
  a histogram of the game lengths from 0 to 1000 rounds (ok to have less detail)
  as well as the average game length.
*/

#include "deck.h"
#include "war.h"

using namespace std;

int main(){
  Card::setTrumpSuit(SPADES);
  Card c1(HEARTS, 1);
  Card c2(SPADES, 2);
  cout << (c1 > c2) << endl;
  return 0;
}
