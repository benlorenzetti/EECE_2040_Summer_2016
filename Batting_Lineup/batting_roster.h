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

/* 
 * @param: filename containing tab-delimited batting stats copied from the
 *         table at
 *         http://espn.go.com/mlb/team/stats/batting/_/name/cin/cincinnati-reds
 * @param: pointer to be directed at a new linked list of players
 * return: number of lines read from the file / size of newly allocated
 *         linked list of players
*/
int import_tab_delimited_stats( const char *, struct player ** );

/*
 * @param: A linked list of player structs to be printed
*/
void print_lineup( struct player * );

/*
 * @param: pointer to pointer looking at the first element of the linked list
 * @param: first player to be exchanged with the 2nd parameter player in a list
 * @param: second player to be echanged with parameter 1.
 * return: pointer to the linked list
*/
struct player* swap_players( struct player **, struct player *, struct player * );




#endif
