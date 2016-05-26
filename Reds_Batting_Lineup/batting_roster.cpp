/* batting_roster.c
 * 
*/

struct player {
  char *Name;
  int GP;
  int AB;
  int R;
  int H;
  int Doubles;
  int Triples;
  int HR;
  int RBI;
  int TB;
  int BB;
  int SO;
  int SB;
  double BA;
  double OBP;
  double SLG;
  double OPS;
  double OWAR;
  struct player *nxt_plyr;
};
 
int input_batting_statistics (const char *, int, struct player *)
{
  return 0;
}

void print_roster (const struct player *)
{
  return;
}

