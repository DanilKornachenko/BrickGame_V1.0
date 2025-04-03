#include "tetris.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

// initialize componens

void init(GameInfo_t *game, tetromino *current, tetromino *nextable) {
  // field init
  game->field = (char **)malloc(sizeof(char *) * FIELD_Y);
  for (int i = 0; i < FIELD_Y; i++) {
    game->field[i] = (char *)malloc(sizeof(char) * FIELD_X);
  }
  // fill the field
  for (int i = 0; i < FIELD_Y; i++) {
    for (int j = 0; j < FIELD_X; j++) {
      if (i == 0 || i == FIELD_Y - 1) {
        game->field[i][j] = '#';
      } else if (j == 0 || j == FIELD_X - 1) {
        game->field[i][j] = '#';
      } else {
        game->field[i][j] = ' ';
      }
    }
  }
  // next init
  game->next = (char **)malloc(sizeof(char *) * 4);
  for (int i = 0; i < 4; i++) {
    game->next[i] = (char *)malloc(sizeof(char) * 4);
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      game->next[i][j] = ' ';
    }
  }

  // tetromino init
  *current = generateFigure((rand() % 7) + 1);
  *nextable = generateFigure((rand() % 7) + 1);

  changeNext(game->next, nextable);
  /*
  for (int i = 0; i < nextable->tet.rows && i < 4; i++) {
    for (int j = 0; j < nextable->tet.cols && j < 4; j++) {
      game->next[i][j] = nextable->tet.matrix[i][j];
    }
  }
  */
  game->score = 0;
  game->high_score = 0;
  game->level = 1;
  game->speed = 1;
  game->pause = 1;
}

void changeNext(char **next, tetromino *nextable) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      next[i][j] = ' ';
    }
  }

  for (int i = 0; i < nextable->tet.rows && i < 4; i++) {
    for (int j = 0; j < nextable->tet.cols && j < 4; j++) {
      next[i][j] = nextable->tet.matrix[i][j];
    }
  }
}

void clean(GameInfo_t *game, tetromino *current, tetromino *nextable) {
  // clean field
  for (int i = 0; i < FIELD_Y; i++) {
    free(game->field[i]);
  }
  free(game->field);
  // clean next
  for (int i = 0; i < 4; i++) {
    free(game->next[i]);
  }
  free(game->next);
  // clean current
  for (int i = 0; i < current->tet.rows; i++) {
    free(current->tet.matrix[i]);
  }
  free(current->tet.matrix);
  // clean nextable
  for (int i = 0; i < nextable->tet.rows; i++) {
    free(nextable->tet.matrix[i]);
  }
  free(nextable->tet.matrix);
}

// end initialize

// tetromino logic

tetromino generateFigure(Type f) {
  tetromino new_f;
  new_f.posX = 5;
  switch (f) {
    case T:
      fig_T(&new_f);
      break;
    case Q:
      fig_Q(&new_f);
      break;
    case I:
      fig_I(&new_f);
      break;
    case Z:
      fig_Z(&new_f);
      break;
    case S:
      fig_S(&new_f);
      break;
    case J:
      fig_J(&new_f);
      break;
    case L:
      fig_L(&new_f);
      break;
  }

  return new_f;
}

void fill_matrix(matrix_t *A) {
  A->matrix = (char **)malloc(sizeof(char *) * A->rows);
  for (int i = 0; i < A->rows; i++) {
    A->matrix[i] = (char *)malloc(sizeof(char) * A->cols);
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->cols; j++) {
      A->matrix[i][j] = '#';
    }
  }
}

void fig_T(tetromino *new_f) {
  new_f->fig = T;
  new_f->posY = 2;

  new_f->tet.cols = 3;
  new_f->tet.rows = 2;
  fill_matrix(&new_f->tet);
  new_f->tet.matrix[1][0] = ' ';
  new_f->tet.matrix[1][2] = ' ';
}

void fig_Q(tetromino *new_f) {
  new_f->fig = Q;
  new_f->posY = 2;

  new_f->tet.cols = 2;
  new_f->tet.rows = 2;
  fill_matrix(&new_f->tet);
}

void fig_I(tetromino *new_f) {
  new_f->fig = I;
  new_f->posY = 4;

  new_f->tet.cols = 1;
  new_f->tet.rows = 4;
  fill_matrix(&new_f->tet);
}

void fig_Z(tetromino *new_f) {
  new_f->fig = Z;
  new_f->posY = 2;

  new_f->tet.cols = 3;
  new_f->tet.rows = 2;
  fill_matrix(&new_f->tet);
  new_f->tet.matrix[0][0] = ' ';
  new_f->tet.matrix[1][2] = ' ';
}

void fig_S(tetromino *new_f) {
  new_f->fig = S;
  new_f->posY = 2;

  new_f->tet.cols = 3;
  new_f->tet.rows = 2;
  fill_matrix(&new_f->tet);
  new_f->tet.matrix[1][0] = ' ';
  new_f->tet.matrix[0][2] = ' ';
}

void fig_J(tetromino *new_f) {
  new_f->fig = J;
  new_f->posY = 3;

  new_f->tet.cols = 2;
  new_f->tet.rows = 3;
  fill_matrix(&new_f->tet);
  new_f->tet.matrix[1][0] = ' ';
  new_f->tet.matrix[2][0] = ' ';
}

void fig_L(tetromino *new_f) {
  new_f->fig = L;
  new_f->posY = 3;

  new_f->tet.cols = 2;
  new_f->tet.rows = 3;
  fill_matrix(&new_f->tet);
  new_f->tet.matrix[1][1] = ' ';
  new_f->tet.matrix[2][1] = ' ';
}

void setFigure(GameInfo_t *game, int mod, tetromino *current) {
  tetromino f = *current;

  for (int i = f.posY, iF = 0; iF < f.tet.rows; i--, iF++) {
    for (int j = f.posX, jF = 0; jF < f.tet.cols; j++, jF++) {
      if (f.tet.matrix[iF][jF] != ' ') {
        if (mod) {
          game->field[i][j] = 'X';
        } else {
          game->field[i][j] = '#';
        }
      }
    }
  }
}

void unsetFigure(GameInfo_t *game, tetromino *current) {
  tetromino f = *current;

  for (int i = f.posY, iF = 0; iF < f.tet.rows; i--, iF++) {
    for (int j = f.posX, jF = 0; jF < f.tet.cols; j++, jF++) {
      if (f.tet.matrix[iF][jF] == '#') {
        if (game->field[i][j] == '#') {
          game->field[i][j] = ' ';
        }
      }
    }
  }
}

int colision(GameInfo_t *game, tetromino *current) {
  tetromino f = *current;

  for (int iF = 0; iF < f.tet.rows; iF++) {
    for (int jF = 0; jF < f.tet.cols; jF++) {
      // Если часть тетромино не пустая
      if (f.tet.matrix[iF][jF] != ' ') {
        int fieldX = f.posX + jF;  // Расчет X на поле
        int fieldY =
            f.posY - iF;  // Расчет Y на поле (инвертируем, так как Y вниз)

        // Проверка на выход за границы поля
        if (fieldY < 0 || fieldY >= FIELD_Y || fieldX < 0 ||
            fieldX >= FIELD_X) {
          return 1;  // Коллизия с границей поля
        }

        // Проверка на столкновение с другими фигурами
        if (game->field[fieldY][fieldX] != ' ') {
          return 1;  // Коллизия с другой фигурой
        }
      }
    }
  }

  return 0;  // Нет коллизий
}

void freeFigure(tetromino *freeable) {
  for (int i = 0; i < freeable->tet.rows; i++) {
    free(freeable->tet.matrix[i]);
  }
  free(freeable->tet.matrix);
  freeable->tet.rows = 0;
  freeable->tet.cols = 0;

  freeable->posY = 0;
  freeable->posX = 0;
}

void nextFigure(GameInfo_t *game, tetromino *current, tetromino *nextable) {
  freeFigure(current);
  swapLeft(current, nextable);
  freeFigure(nextable);
  *nextable = generateFigure((rand() % 7) + 1);

  changeNext(game->next, nextable);

  if (colision(game, current)) game->level = 0;
}

void swapLeft(tetromino *current, tetromino *nextable) {
  *current = generateFigure(nextable->fig);
  current->posX = nextable->posX;
  current->posY = nextable->posY;
  current->fig = nextable->fig;
}

void movedown(GameInfo_t *game, tetromino *current, tetromino *nextable) {
  unsetFigure(game, current);
  current->posY++;
  if (colision(game, current)) {
    current->posY--;
    setFigure(game, 1, current);
    // checkField (game);
    nextFigure(game, current, nextable);
  } else
    setFigure(game, 0, current);
}

void dropdown(GameInfo_t *game, tetromino *current, tetromino *nextable) {
  unsetFigure(game, current);
  while (!colision(game, current)) {
    current->posY++;
  }
  current->posY--;
  setFigure(game, 1, current);
  nextFigure(game, current, nextable);
}

void moveleft(GameInfo_t *game, tetromino *current) {
  unsetFigure(game, current);
  current->posX--;
  if (colision(game, current)) {
    current->posX++;
    setFigure(game, 0, current);
  } else
    setFigure(game, 0, current);
}

void moveright(GameInfo_t *game, tetromino *current) {
  unsetFigure(game, current);
  current->posX++;
  if (colision(game, current)) {
    current->posX--;
    setFigure(game, 0, current);
  } else
    setFigure(game, 0, current);
}

void checkField(GameInfo_t *game) {
  int linesCleared = 0;

  for (int i = FIELD_Y - 2; i > 0; i--) {
    int count = 0;
    for (int j = 1; j < FIELD_X - 1; j++) {
      if (game->field[i][j] == 'X') count++;
    }
    if (count == FIELD_X - 2) {
      clearCol(i, game);
      linesCleared++;
      i++;
    }
  }

  switch (linesCleared) {
    case 1:
      game->score += 100;
      break;
    case 2:
      game->score += 300;
      break;
    case 3:
      game->score += 700;
      break;
    case 4:
      game->score += 1500;
      break;
  }
}

void clearCol(int row, GameInfo_t *game) {
  for (int i = row; i > 1; i--) {
    for (int j = 1; j < FIELD_X - 1; j++) {
      game->field[i][j] = game->field[i - 1][j];
    }
  }

  for (int j = 1; j < FIELD_X - 1; j++) {
    game->field[1][j] = ' ';
  }
}

void flip(GameInfo_t *game, tetromino *current) {
  unsetFigure(game, current);

  transpose(current);

  flipRight(current);
  if (colision(game, current)) {
    flipLeft(current);
    transpose(current);
  }

  setFigure(game, 0, current);
}

void flipRight(tetromino *current) {  // Переделать
  int rows = current->tet.rows;
  int cols = current->tet.cols;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols / 2; j++) {
      char temp = current->tet.matrix[i][j];
      current->tet.matrix[i][j] = current->tet.matrix[i][cols - 1 - j];
      current->tet.matrix[i][cols - 1 - j] = temp;
    }
  }
}

void flipLeft(tetromino *current) {
  int rows = current->tet.rows;
  int cols = current->tet.cols;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols / 2; j++) {
      char temp = current->tet.matrix[i][j];
      current->tet.matrix[i][j] = current->tet.matrix[i][cols - 1 - j];
      current->tet.matrix[i][cols - 1 - j] = temp;
    }
  }
}

void transpose(tetromino *current) {
  matrix_t newM;
  newM.rows = current->tet.cols;
  newM.cols = current->tet.rows;

  newM.matrix = (char **)malloc(sizeof(char *) * newM.rows);
  for (int i = 0; i < newM.rows; i++) {
    newM.matrix[i] = (char *)malloc(sizeof(char) * newM.cols);
  }

  for (int i = 0; i < newM.rows; i++) {
    for (int j = 0; j < newM.cols; j++) {
      newM.matrix[i][j] = current->tet.matrix[j][i];
    }
  }

  for (int i = 0; i < current->tet.rows; i++) {
    free(current->tet.matrix[i]);
  }
  free(current->tet.matrix);

  current->tet = newM;
}

// end tetromino

// User input logic

void userInput(UserAction_t *action) {
  int key = getch();
  if (key == ERR) *action = -1;
  switch (key) {
    case KEY_LEFT:
      *action = Left;
      break;
    case KEY_RIGHT:
      *action = Right;
      break;
    case KEY_UP:
      *action = Up;
      break;
    case KEY_DOWN:
      *action = Down;
      break;
    case 'q':
      *action = Terminate;
      break;
    case '\n':
      *action = Start;
      break;
    case 'p':
      *action = Pause;
      break;
    case '\t':
      *action = Pause;
      break;
    case 32:
      *action = Action;  // Пробел
      break;
  }
}

void updateTetrominoState(tetromino *current, tetromino *nextable,
                          GameInfo_t *game, UserAction_t *action) {
  if (game->level == 0) *action = Terminate;

  if (game->pause) {
    if (*action == Start) {
      game->pause = 0;
      setFigure(game, 0, current);
    }
  } else {
    switch (*action) {
      case Start:
        break;
      case Pause:
        game->pause = 1;
        break;
      case Left:
        moveleft(game, current);
        break;
      case Right:
        moveright(game, current);
        break;
      case Up:
        break;
      case Down:
        dropdown(game, current, nextable);
        break;
      case Action:
        flip(game, current);
        break;
      case Terminate:
        break;
      default:
        movedown(game, current, nextable);
        break;
    }
  }
}

void levelCheck(GameInfo_t *game) {
  int levelCh = 0;

  if (game->score < 600) {
    levelCh = 1;
  } else {
    int temp = game->score / 600;
    levelCh += temp + 1;
  }

  if (game->level != 0) {
    if (levelCh >= 10) {
      game->level = 10;
    } else {
      game->level = levelCh;
      game->speed = game->level;
    }
  }
}

void time_out(GameInfo_t game) {
  int tm = 0;

  switch (game.level) {
    case 1:
      tm = 900;
      break;
    case 2:
      tm = 800;
      break;
    case 3:
      tm = 700;
      break;
    case 4:
      tm = 600;
      break;
    case 5:
      tm = 500;
      break;
    case 6:
      tm = 400;
      break;
    case 7:
      tm = 300;
      break;
    case 8:
      tm = 200;
      break;
    case 9:
      tm = 100;
      break;
    case 10:
      tm = 50;
      break;
  }

  timeout(tm);
}

GameInfo_t updateCurrentState(GameInfo_t game) {
  checkField(&game);

  if (game.score > game.high_score) game.high_score = game.score;

  levelCheck(&game);

  time_out(game);

  return game;
}

// end User input logic

void savedata(GameInfo_t *game, int mod) {
  FILE *file;

  file = fopen("save/score.txt", "r+");

  if (file == NULL) {
    file = fopen("save/score.txt", "w+");
    if (file == NULL) {
      perror("Ошибка открытия файла");
      return;
    }
  }

  if (mod == 0) {  // Считать рекорд
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), file) != NULL) {
      game->high_score = atoi(buffer);
    } else {
      game->high_score = 0;
    }
  } else if (mod == 1) {  // Записать рекорд
    rewind(file);
    fprintf(file, "%d\n", game->high_score);
    fflush(file);
  }

  fclose(file);
}
