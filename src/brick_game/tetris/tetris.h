#include <ncurses.h>
#include <stdbool.h>

#define FIELD_Y 20
#define FIELD_X 10

#define defaultPos 4

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef enum { T = 1, Q, I, Z, S, J, L } Type;

typedef struct {
  char **matrix;
  int rows;
  int cols;
} matrix_t;

typedef struct {
  matrix_t tet;
  Type fig;
  int posX;
  int posY;
} tetromino;

typedef struct {
  char **field;
  char **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

// Ввод от пользователя
void userInput(UserAction_t *action);
// Обновление данных
GameInfo_t updateCurrentState(GameInfo_t game);

void updateTetrominoState(tetromino *current, tetromino *nextable,
                          GameInfo_t *game, UserAction_t *action);

// Инициализация
void init(GameInfo_t *game, tetromino *current, tetromino *nextable);

void fill_matrix(matrix_t *A);

void fig_T(tetromino *new_f);

void fig_Q(tetromino *new_f);

void fig_I(tetromino *new_f);

void fig_Z(tetromino *new_f);

void fig_S(tetromino *new_f);

void fig_J(tetromino *new_f);

void fig_L(tetromino *new_f);

// movement

tetromino generateFigure(Type f);

void setFigure(GameInfo_t *game, int mod, tetromino *current);

void unsetFigure(GameInfo_t *game, tetromino *current);

void freeFigure(tetromino *freeable);

void nextFigure(GameInfo_t *game, tetromino *current, tetromino *nextable);

void swapLeft(tetromino *current, tetromino *nextable);

int colision(GameInfo_t *game, tetromino *current);

void movedown(GameInfo_t *game, tetromino *current, tetromino *nextable);

void moveleft(GameInfo_t *game, tetromino *current);

void moveright(GameInfo_t *game, tetromino *current);

void dropdown(GameInfo_t *game, tetromino *current, tetromino *nextable);

void flip(GameInfo_t *game, tetromino *current);

void flipRight(tetromino *current);

void flipLeft(tetromino *current);

void transpose(tetromino *current);  // think

void checkField(GameInfo_t *game);  // Не работает

void clearCol(int row, GameInfo_t *game);

void clean(GameInfo_t *game, tetromino *current, tetromino *nextable);

// Other

void changeNext(char **next, tetromino *nextable);

void levelCheck(GameInfo_t *game);

void time_out(GameInfo_t game);

void savedata(GameInfo_t *game, int mod);
