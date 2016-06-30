#include <iostream>
#include <string>
/*
  The file implements main to simulate 100000 games of war.  It should print out
  a histogram of the game lengths from 0 to 1000 rounds (ok to have less detail)
  as well as the average game length.
*/
#include "war.h"

using namespace std;

const int NUMBER_OF_GAMES = 100000;

int main(){
  cout << "Games:\n  (1) Tic Tac Toe\n  (2) Thermo Nuclear War\n";
  cout << "Which game would you like to play (1 or 2)? ";
  string str1; 
  cin >> str1;
  long total_rounds = 0;
  for(int game = 0; game < NUMBER_OF_GAMES; game++) {
    cout << game << ".\t";
    total_rounds += runWar(1000);
  }
  cout << "\nThe average game length over " << NUMBER_OF_GAMES << " games was "
       << ((double)total_rounds) / NUMBER_OF_GAMES << ".\n";
  return 0;
}
