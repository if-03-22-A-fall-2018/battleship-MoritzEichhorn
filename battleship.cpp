/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>

#include "battleship.h"

static CellContent my[FIELDSIZE][FIELDSIZE];
static CellContent op[FIELDSIZE][FIELDSIZE];
static CellContent my_guesses[FIELDSIZE][FIELDSIZE];

void load_game() {
  FILE *my_fd = fopen("battleship.my", "r");
	FILE *op_fd = fopen("battleship.op", "r");

  for(int i = 0; i < FIELDSIZE; i++)
  {
    for(int j = 0; j < FIELDSIZE; j++)
    {
      fread(&my[i][j], sizeof(CellContent), 1, my_fd);
      fread(&op[i][j], sizeof(CellContent), 1, op_fd);
      my_guesses[i][j] = Unknown;
    }
  }
  fclose(my_fd);
  fclose(op_fd);
}


CellContent get_shot(int row, int col) {
  if(row < FIELDSIZE && row >= 0 && col < FIELDSIZE && col >= 0)
  {
    return my[row][col];
  }
  return OutOfRange;
}

bool shoot(int row, int col) {
  if(row < FIELDSIZE && row >= 0 && col < FIELDSIZE && col >= 0)
  {
    my_guesses[row][col] = op[row][col];
    if(op[row][col] == Boat)
    {
      for (int i = row-1; i <= row + 1; i++) {
        for (int j = col -1; j <= col + 1;j++)
        {
          if(i < FIELDSIZE && i >= 0 && j < FIELDSIZE && j >= 0 && (i != row || j != col))
          {
            my_guesses[i][j] = Water;
          }
        }
      }
    }
    return true;
  }
  return false;
}

CellContent get_my_guess(int row, int col) {
  if(row < FIELDSIZE && row >= 0 && col < FIELDSIZE && col >= 0)
  {
    return my_guesses[row][col];
  }
  return OutOfRange;
}
