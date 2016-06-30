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
  Deck player1;
  player1.add_52_cards();
  player1.print_deck();
  cout << "Shuffling...\n";
  player1.shuffle_deck();
  player1.print_deck();
  return 0;
}
