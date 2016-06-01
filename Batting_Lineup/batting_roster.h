/* batting_roster.h
 * 
 * Demonstration of C Structures Using Batting Statistics
 * Ben Lorenzetti
 * May 31, 2016
 * EECE 2040L Data Structures Programming
*/

#ifndef BATTING_ROSTER_H
#define BATTING_ROSTER_H

const int MAX_NAME_LENGTH = 256;

/* The player structure is based on a row from the MLB batting statistics
 * table at:
 *   http://espn.go.com/mlb/team/stats/batting/_/name/cin/cincinnati-reds
 * It includes two character arrays for the players' name, numeric members
 * for each batting statistic, and pointers for building a linked lists.
*/
struct player
{
  char first_name[MAX_NAME_LENGTH];
  char last_name[MAX_NAME_LENGTH];
  int games_played;
  int at_bats;
  int runs;
  int hits;
  int doubles;
  int triples;
  int home_runs;
  int rbi;     // Runs Batted In
  int total_bases;
  int walks;
  int strikeouts;
  int stolen_bases;
  float batting_average;
  float obp;  // Slugging Percentage
  float slg;  // On-base Percentage
  float ops;  // OBP + SLG
  float owar; // Offensive Wins Above Replacement
  struct player *next_player;
  struct player *prev_player;
};

/* Parses batting statistics records from a tab-delimited text file and
 * constructs a linked list of player structs from the data. The data file
 * should have no header rows and the columns should correspond in order to
 * the members of the player struct.
 *
 * @param: filename containing tab-delimited batting stats copied from the
 *         table at
 *         http://espn.go.com/mlb/team/stats/batting/_/name/cin/cincinnati-reds
 * @param: pointer to be directed at a new linked list of players
 * return: number of lines read from the file / size of newly allocated
 *         linked list of players
*/
int import_tab_delimited_stats( const char *, struct player ** );

/* Prints a linked list of player structs in tabular form to standard output
 *
 * @param: A linked list of player structs to be printed
*/
void print_lineup( struct player * );

/* Use to reorder a player linked list by swapping two elements. Takes care of
 * all the pointers in the list that must be changed.
 *
 * @param: the first element of the linked list (may be changed by the swap)
 * @param: first player to be exchanged with the next parameter player.
 * @param: second player to be echanged.
 * return: a pointer advanced to the next player after the new player 1
*/
struct player* swap_players( struct player **, struct player *, struct player * );

/* Searches linearly in the forward direction to find highest batting average.
 *
 * @param: linked list of players to be searched
 * return: address of player with greatest batting average
*/
struct player* find_best_table_setter ( struct player * );

/* Searches linearly in the forward direction to find highest SLG.
 *
 * @param: linked list of players to be searched
 * return: address of player with best slugging ratio
*/
struct player* find_best_slugger ( struct player * );

/* Truncates a linked list and releases players after truncation point
 *
 * @param: first player to be released, i.e. the trucation point
*/
void free_list( struct player *list );


#endif
