/* batting_lineup.cpp
 *
*/

#include <iostream>
#include "batting_roster.h"

int main (int argc, char *argv[])
{
  if (argc != 2) {
    std::cout << "Error: Usage should be:\n" << argv[0] << " <filename>\n";
    std::cout << "where <filename> is a tab-delimited text file of batting statistics\n";
    return -1;
  }

  struct player *lineup;
  int number_of_players = 0;

  number_of_players = import_tab_delimited_stats( argv[1], &lineup );
  if (!number_of_players) {
    std::cout << "Error: no player records were imported.\n";
    return -1;
  }

  print_lineup (lineup);
}
