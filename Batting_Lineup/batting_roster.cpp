/* batting_roster.cpp
 * 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "batting_roster.h"

int import_tab_delimited_stats (const char *filename, struct player **ret_ptr)
{
  // Open the File
  FILE *fp;
  if ( !( fp = fopen( filename, "r") ) )
  {
    printf ("Error: the file %s could not be opened.\n", filename);
    return 0;
  }

  /* Allocate a struct, fill it with stats from the current file line,
   * and repeat until end of file.
  */
  int player_count = 0;
  struct player *plr = NULL;
  struct player **linked_list_ptr = ret_ptr;
  do
  {
    // Allocate new player struct
    if ( !( plr = (struct player*) malloc ( sizeof(struct player) ) ) )
    {
      printf ("Error: malloc() failure./n");
      exit (EXIT_FAILURE);
    }

    // Scan in stats from current line, there should be 19 columns per line
    int scan_error = 0;
    if ( 2 != fscanf( fp, "%s %s", &plr->first_name, &plr->last_name ) )
      scan_error = 1;
    if ( 2 != fscanf( fp, "%d %d", &plr->games_played, &plr->at_bats ) )
      scan_error = 1;
    if ( 2 != fscanf( fp, "%d %d", &plr->runs, &plr->hits ) )
      scan_error = 1;
    if ( 2 != fscanf( fp, "%d %d", &plr->doubles, &plr->triples ) )
      scan_error = 1;
    if ( 2 != fscanf( fp, "%d %d", &plr->home_runs, &plr->rbi ) )
      scan_error = 1;
    if ( 2 != fscanf( fp, "%d %d", &plr->total_bases, &plr->walks ) )
      scan_error = 1;
    if ( 2 != fscanf( fp, "%d %d", &plr->strikeouts, &plr->stolen_bases ) )
      scan_error = 1;
    if ( 2 != fscanf( fp, "%f %f", &plr->batting_average, &plr->obp ) )
      scan_error = 1;
    if ( 2 != fscanf( fp, "%f %f", &plr->slg, &plr->ops ) )
      scan_error = 1;
    if ( 1 != fscanf( fp, "%f", &plr->owar ) )
      scan_error = 1;
    if (scan_error)
    {
      printf( "Warning: Unexpected table format on line %d.\n", player_count);
      free (plr); // release the incomplete record and then
      *linked_list_ptr = NULL; // terminate the linked list
      return player_count;
    }

    // Add plr to the linked list and increment the pointer and player_count
    *linked_list_ptr = plr;
    linked_list_ptr = &( plr->next_player );
    player_count++;
  
    // Test if there is more in the file, if so then repeat
  } while ( !feof( fp ) );

  // Terminate the linked list, close the file, and return
  plr->next_player = NULL;
  fclose (fp);
  return player_count;
}

void print_lineup (struct player *batting_list)
{
  // Print a Header Row
  printf ("\n%-12s %-12s ", "Player", "Name");
  printf ("%3s %3s %3s %3s %3s %3s ", "GP", "AB", "R", "H", "2B", "3B");
  printf ("%3s %3s %3s %3s %3s %3s ", "HR", "RBI", "TB", "BB", "SO", "SB");
  printf ("\t%s \t%s \t%s \t%s \t%s \n", "BA", "OBP", "SLG", "OPS", "OWAR");

  // Print each player in the linked list
  struct player *plr = batting_list;
  while (plr)
  {
    // Print stats from the current player struct
    printf ("%-12s %-12s ", plr->first_name, plr->last_name);
    printf ("%3d %3d %3d ", plr->games_played, plr->at_bats, plr->runs);
    printf ("%3d %3d %3d ", plr->hits, plr->doubles, plr->triples);
    printf ("%3d %3d %3d ", plr->home_runs, plr->rbi, plr->total_bases);
    printf ("%3d %3d %3d ", plr->walks, plr->strikeouts, plr->stolen_bases);
    printf ("\t%.4g\t%.4g", plr->batting_average, plr->obp);
    printf ("\t%.4g\t%.4g\t%.4g\n", plr->slg, plr->ops, plr->owar);
    // Advance to the next player
    plr = plr->next_player;
  } 
  return;
}

