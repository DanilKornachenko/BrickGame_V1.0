#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../gui/cli/cli.h"
#include "tetris.h"

void gameloop(GameInfo_t game, UserAction_t input, tetromino *current,
              tetromino *nextable);

int main() {
  srand(time(NULL));
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);

  timeout(50);

  GameInfo_t game;
  tetromino current, nextable;
  UserAction_t input = Pause;
  init(&game, &current, &nextable);
  savedata(&game, 0);
  gameloop(game, input, &current, &nextable);
  clean(&game, &current, &nextable);
  endwin();
  return 0;
}

void gameloop(GameInfo_t game, UserAction_t input, tetromino *current,
              tetromino *nextable) {
  while (input != Terminate) {
    userInput(&input);
    if (input == Terminate) continue;
    updateTetrominoState(current, nextable, &game, &input);
    game = updateCurrentState(game);
    print(game.field, game.next, game.score, game.high_score, game.level,
          game.speed);
  }

  savedata(&game, 1);
}
