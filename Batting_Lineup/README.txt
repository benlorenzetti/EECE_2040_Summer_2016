*******************************************************************************
EECE2040 Data Structures Programming
Homework 1: Demonstration of C structs using baseball batting statistics
Ben Lorenzetti
Jun. 01, 2016
*******************************************************************************


batting_roster.cpp  - Structure for storing player statistics and a set of
                      functions for building linked-lists of players, i.e. a
                      roster or batting lineup
batting_roster.h    - Interface and documentation for batting_roster.cpp
batting_lineup.cpp  - Program that uses batting_roster functions to create a
                      batting lineup using stats from a tab-delimted text file
Makefile            - for gcc
Reds_Statistics.txt - sample data file with proper format

*******************************************************************************


To compile and run on Linux:
    $ make
    $ ./batting_lineup Reds_Statistics.txt


*******************************************************************************

  The program batting_lineup.cpp demonstrates the use of structs in C/C++.

  It reads a whitespace delimited text file containing batting statistics for
any MLB team. The statisics should be in a headerless table with one row per
player and a total of 18 columns. Transposed, in order, the 18 should be:

_N_ _Type___	__Statistic__	_Abbreviation_
1.  (char*)	Player Name	Name
2.  (int)	Games Played	GP
3.  (int)	At Bats		AB
4.  (int)	Runs		R
5.  (int)	Hits		H
6.  (int)	Doubles		2B
7.  (int)	Triples		3B
8.  (int)	Home Runs	HR
9.  (int)	Runs Batted In	RBI
10. (int)	Total Bases	TB
11. (int)	Walks		BB
12. (int)	Strikeouts	SO
13. (int)	Stolen Bases	SB
14. (double)	Batting Average	BA
15. (double)	On-Base pct.	OBP
16. (double)	Slugging pct.	SLG
17. (double)	OBP + SLG =	OPS
18. (double)	Offensive Wins Above Replacement	OWAR

  The data design is a structure containing a player's name, stats, and
two pointers for building linked lists. There a functions for building
a linked list of players from a data file, for printing player lists,
for swapping elementss of a player list, for freeing/truncating lists,
and linear search functions for maximizing batting average and slugging pct.

  More documentation is in the interface file batting_roster.h.

