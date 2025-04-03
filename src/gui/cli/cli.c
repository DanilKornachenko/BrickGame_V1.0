#include "cli.h"

void print(char **field, char **next, int score, int high_score, int level,
           int speed) {
  clear();
  for (int i = 0; i < FIELD_Y; i++) {
    for (int j = 0; j < FIELD_X; j++) {
      printw("%c", field[i][j]);
    }
    printw("\n");
  }

  int start_x = FIELD_X + 3;
  int start_y = 0;

  for (int i = 0; i < 4; i++) {
    move(start_y + i, start_x);
    for (int j = 0; j < 4; j++) {
      printw("%c", next[i][j]);
    }
  }

  move(start_y + 5, start_x);
  printw("Score: ");

  move(start_y + 6, start_x);
  printw("%d", score);

  move(start_y + 7, start_x);
  printw("High score:");

  move(start_y + 8, start_x);
  printw("%d", high_score);

  move(start_y + 9, start_x);
  printw("Level: ");

  move(start_y + 10, start_x);
  printw("%d", level);

  move(start_y + 11, start_x);
  printw("Speed: ");

  move(start_y + 12, start_x);
  printw("%d", speed);

  refresh();
}
