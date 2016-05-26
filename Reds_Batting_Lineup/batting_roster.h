/* batting_roster.h
 * 
 * Demonstration of C Structures Using Batting Statistics
 * Ben Lorenzetti
 * May 25, 2016
 * EECE 2040L Data Structures Programming
 *
 *   Data design is a player struct that contains a players name,
 * batting statistics, and space for a pointer for building dynamic
 * linked lists.
 *
 *   Function include an input parser for reading statistics from
 * a tab-separated text file, a linked-list print function, and a
 * linked-list swap function.
*/

#ifndef BATTING_ROSTER_H
#define BATTING_ROSTER_H

struct player;

/*  input_batting_statistics (1, 2, 3);
 *
 *  Reads a tab separated text file to import player stats and builds
 *  a stat roster, ie a linked list of player structs. Parameters are:
 *    1. text filename
 *    2. line number to begin reading
 *    3. pointer to be appended with linked list
 *  Returns new size of the linked list.
*/  
int input_batting_statistics (const char *, int, struct player *);

/*   print_roster (1);
 *
 *   Prints the linked list of players passed in as parameter 1.
 *     1. pointer to first player of the roster (linked list of players).
*/
void print_roster (const struct player *);

#endif
