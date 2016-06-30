#ifndef WAR_H
#define WAR_H
/*
  This runWar function runs a game of war between 2 automated players
  and returns the number of rounds (both put a card down 
  once per round) until someone won.  An integer is given 
  as an upper limit to how many rounds a game can go on for.
*/
#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <stack>
#include <queue>

#include "deck.h"

using namespace std;

long runWar(int limit){
  // Get a fresh deck, shuffle it, and deal it evenly into 2 piles on the table
  Deck dealer, table1, table2;
  dealer.add_52_cards();
  dealer.shuffle_deck();
  while(dealer.get_size()){
    if(dealer.get_size() % 2)
      table1.collect(dealer.draw());
    else
      table2.collect(dealer.draw());
  }
  // Player 1 and 2 pick up their decks
  Deck player1, player2;
  player1.collect_deck(table1);
  player2.collect_deck(table2);

  // Begin Play, quiting when either player runs out of cards or
  // the round limit is reached
  long round = 0;
  while(player1.get_size() && player2.get_size() && round < limit)
  {
    // Place fighting cards on the table
    table1.collect(player1.draw());
    table2.collect(player2.draw());
    // Compare fighting cards and winner collects the table cards
    if(table1.table_top() > table2.table_top()) {
      player1.collect_deck(table1);
      player1.collect_deck(table2);
    }
    else if(table2.table_top() > table1.table_top()) {
      player2.collect_deck(table1);
      player2.collect_deck(table2);
    }
    else /* (cards are equal) */ 
    {
      // Declare WAR loudly and with much fanfare.
      // Bury 3 cards if you can then continue round in the next iteration
      if(player1.get_size() <= 3 || player2.get_size() <= 3) {
        // At least one player does not have enough cards, so declare winner
        if(player1.get_size() > player2.get_size()) {
          cout << "Player 1 wins (during a war) after " << round << " rounds" << endl;
          return round;
        }
        else if(player2.get_size() > player1.get_size()) {
          cout << "Player 2 wins (during a war) after " << round << " rounds" << endl;
          return round;
        }
        else {
          cout << "         Tie (both players run out of cards during a war)";
          cout << " during round " << round << endl;
          return round;
        }
      }
      // Both players have > 3 cards so bury 3 cards
      for(int i=0; i<3; i++) {
        table1.collect(player1.draw());
        table2.collect(player2.draw());
      }
      // Continue this round's war in the next iteration
      continue;
    }// end table1.top == table2.top aka WAR
    round++;
  }// end round loop
  // Determine who won and report results
  if (player1.get_size() > player2.get_size()) {
    cout << "Player 1 wins after " << round << " rounds." << endl;
  }
  else if(player2.get_size() > player1.get_size()) {
    cout << "Player 2 wins after " << round << " rounds." << endl;
  }
  else {
    cout << "         Tie game after " << round << " rounds." << endl;
  }
  return round;
}
#endif
