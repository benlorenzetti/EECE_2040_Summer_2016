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
  do
  {
    // Save the current end of the linked list before allocating a new element
    struct player *prev_plr = plr;

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
      free (plr); // release incomplete record and return what was successful
      return player_count;
    }

    // Add plr to the linked list
    if (!prev_plr) // if the first element, then there is no prev_plr.
    {
      *ret_ptr = plr;
      plr->prev_player = NULL;
    }
    else
    {
      prev_plr->next_player = plr;
      plr->prev_player = prev_plr;
    }
    
    // Increment the player count for a useful return value
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
  printf ("%-12s %-12s ", "Player", "Name");
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

struct player* swap_players (
  struct player **list,
  struct player *plr1,
  struct player *plr2)
{
  printf ("player_swap(): ");

  // Make local copies of the 4 prev and next pointers of plr1 and plr2
  struct player *plr1_next_cpy = plr1->next_player;
  struct player *plr1_prev_cpy = plr1->prev_player;
  struct player *plr2_next_cpy = plr2->next_player;
  struct player *plr2_prev_cpy = plr2->prev_player;

  // Update pointers of all 4 players on either side of plr1 and 2
  if ( plr1_next_cpy ) // is there a player after plr1 to update?
  {
    (plr1->next_player)->prev_player = plr2;
  }
  if ( plr1_prev_cpy ) // is there a player before plr1 to update?
  {
    (plr1->prev_player)->next_player = plr2;
  }
  if ( plr2_next_cpy ) // is there a player after plr2 to update?
  {
    (plr2->next_player)->prev_player = plr1;
  }
  if ( plr2_prev_cpy ) // is there a player before plr2 to update?
  {
    (plr2->prev_player)->next_player = plr1;
  }

  // Update the list if the first element will change
  if ( plr1 == *list )
  {
    *list = plr2;
  }
  else if ( plr2 == *list )
  {
    *list = plr1;
  }

  // Update/swap the 4 pointers in plr1 and plr2
  plr1->next_player = plr2_next_cpy;
  plr1->prev_player = plr2_prev_cpy; 
  plr2->next_player = plr1_next_cpy;
  plr2->prev_player = plr1_prev_cpy; 

  // If plr1 and plr2 were already next to one another, need to fix
  // the self referencing pointers the were created
  if ( plr1->next_player == plr1 )
  {
    plr1->next_player = plr2;
  }
  if ( plr1->prev_player == plr1 )
  {
    plr1->prev_player = plr2;
  }
  if ( plr2->next_player == plr2 )
  {
    plr2->next_player = plr1;
  }
  if ( plr2->prev_player == plr2 )
  {
    plr2->prev_player = plr1;
  }

  printf ("swapped %s %s with ", plr2->first_name, plr2->last_name);
  printf ("%s %s, ", plr1->first_name, plr1->last_name);

  // Advance pointer the the next player after the new player 1 and return
  struct player *ret_ptr = plr2->next_player;
  printf ("and returning pointer to %s %s\n", ret_ptr->first_name, ret_ptr->last_name);
  return ret_ptr;
}

struct player* find_best_table_setter ( struct player *search_ptr )
{
  if ( !search_ptr )
  {
    printf ("Warning: find_best_table_settler() called on NULL list.\n");
    return NULL;
  }
  printf ("find_best_table_setter(): starting at ");
  printf ("%s %s, ", search_ptr->first_name, search_ptr->last_name);
  struct player *best_setter = NULL;
  double best_batting_average = 0;
  while( search_ptr )
  {
    if ( best_batting_average < search_ptr->batting_average )
    {
      best_batting_average = search_ptr->batting_average;
      best_setter = search_ptr;
    }
    search_ptr = search_ptr->next_player;
  }
  printf ("the best setter is %s ", best_setter->first_name);
  printf ("%s (BA = %.3f)\n", best_setter->last_name, best_setter->batting_average);
  return best_setter;
}


struct player* find_best_slugger ( struct player *search_ptr )
{
  if ( !search_ptr )
  {
    printf ("Warning: find_best_slugger() called on NULL list.\n");
    return NULL;
  }
  printf ("find_best_slugger(): starting at ");
  printf ("%s %s, ", search_ptr->first_name, search_ptr->last_name);
  struct player *best_slugger = NULL;
  double best_slg = 0;
  while( search_ptr )
  {
    if ( best_slg < search_ptr->slg )
    {
      best_slg = search_ptr->slg;
      best_slugger = search_ptr;
    }
    search_ptr = search_ptr->next_player;
  }
  printf ("the best slugger is %s ", best_slugger->first_name);
  printf ("%s (SLG = %.3f)\n", best_slugger->last_name, best_slugger->batting_average);
  return best_slugger;
}

void free_list( struct player *list )
{
  if ( !list )
  {
    return;
  }
  printf ("free_list(): freeing list starting at ");
  printf ("%s %s\n", list->first_name, list->last_name);

  // Terminate pointer of previous element, if exists
  if ( list->prev_player )
  {
    list->prev_player->next_player = NULL;
  }

  // Free each element of the list
  struct player *next_player = NULL;
  while ( list )
  {
    next_player = list->next_player;
    free (list);
    list = next_player;
  }
}
