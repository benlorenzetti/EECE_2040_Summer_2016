/* batting_lineup.cpp
 *
*/

#include <iostream>
#include "batting_roster.h"

int main (int argc, char *argv[])
{
  // Get a batting stats data file from the user
  if (argc != 2) {
    std::cout << "Error: Usage should be:\n" << argv[0] << " <filename>\n";
    std::cout << "where <filename> is a tab-delimited text file of batting statistics\n";
    return -1;
  }

  // Import batting statistics records from the data file into a player
  // linked-list
  struct player *lineup;
  int number_of_players = 0;

  number_of_players = import_tab_delimited_stats( argv[1], &lineup );
  if ( number_of_players < 9 )
  {
    std::cout << "Error: only " << number_of_players << " players were found in "
    << argv[1] << ". Need 9 for a lineup.\n";
    return -1;
  }
  
  // Find the two best batting average player and move them to top of the list
  struct player *starting_point = lineup;
  struct player *best_player = NULL; 
  for ( int i = 0; i < 2; i++ )
  {
    best_player = find_best_table_setter( starting_point );
    starting_point = swap_players( &lineup, starting_point, best_player );
  }

  // Find the 3 best sluggers and move them right up to the starting point
  // after the two table setters
  for ( int i = 0; i < 3; i++ )
  {
    best_player = find_best_slugger( starting_point );
    starting_point = swap_players( &lineup, starting_point, best_player );
  }

  // For the remaining 4 slots, again go by batting average
  for ( int i = 0; i < 4; i++ )
  {
    best_player = find_best_table_setter( starting_point );
    starting_point = swap_players( &lineup, starting_point, best_player );
  }

  // Truncate the list after 9 players
  free_list ( starting_point );
  
  // Print the sorted batting lineup
  print_lineup (lineup);
}
