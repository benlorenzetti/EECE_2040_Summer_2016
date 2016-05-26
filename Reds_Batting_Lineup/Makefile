# Makefile for batting_lineup.cpp
all: batting_lineup
#
batting_lineup: batting_lineup.o batting_roster.o
	g++ batting_lineup.o batting_roster.o -o batting_lineup
#
batting_lineup.o: batting_lineup.cpp
	g++ -c batting_lineup.cpp
#
batting_roster.o: batting_roster.cpp
	g++ -c batting_roster.cpp
# end of Makefile
