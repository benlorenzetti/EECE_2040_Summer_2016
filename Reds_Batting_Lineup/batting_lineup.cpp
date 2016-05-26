/* batting_lineup.cpp
 *
*/

#include <iostream>
#include "batting_roster.h"

int main (int argc, char *argv[])
{
  if (argc != 3) {
    std::cout << "Error: Usage should be:\n" << argv[0] << " <filename> <start_line>\n";
    std::cout << "where <filename> is the name of a tab separated table of players' batting statistics\n";
    std::cout << "and <start_line> is the line number of the first data record in <filename>.\n";
    return 0;
  }
}
