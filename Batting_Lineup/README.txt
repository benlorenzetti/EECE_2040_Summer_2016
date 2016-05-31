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

There is a Makefile for compiling the program with gcc on Linux.

The program reads in the batting statistics and then creates a list
of player structures corresponding to each row from the data file.
The list is sorted into a good batting lineup and then printed.

To run, pass as an arguement the name of the text data file.

$ make
$ ./batting_lineup Reds_Batting_Statistics.txt
