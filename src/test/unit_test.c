#include <check.h>

#include "../brick_game/tetris/tetris.h"

START_TEST(init_t) {
  GameInfo_t game;
  tetromino current, nextable;
  init(&game, &current, &nextable);

  for (int i = 0; i < FIELD_Y; i++) {
    for (int j = 0; j < FIELD_X; j++) {
      if (i == 0 || i == FIELD_Y - 1 || j == 0 || j == FIELD_X - 1) {
        ck_assert_int_eq(game.field[i][j], '#');
      } else {
        ck_assert_int_eq(game.field[i][j], ' ');
      }
    }
  }

  ck_assert_int_eq(game.score, 0);
  ck_assert_int_eq(game.level, 1);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(genfig_t) {
  tetromino nextable = generateFigure(T);

  ck_assert_int_eq(nextable.tet.matrix[1][0], ' ');
  ck_assert_int_eq(nextable.tet.matrix[1][1], '#');
  ck_assert_int_eq(nextable.tet.matrix[1][2], ' ');
}
END_TEST

START_TEST(colision_t) {
  GameInfo_t game;
  tetromino current = generateFigure(Q);
  tetromino nextable = generateFigure(Q);

  init(&game, &current, &nextable);

  current.posY = 0;
  ck_assert_int_eq(colision(&game, &current), 1);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(colision1_t) {
  GameInfo_t game;
  tetromino current = generateFigure(Q);
  tetromino nextable = generateFigure(Q);

  init(&game, &current, &nextable);

  ck_assert_int_eq(colision(&game, &current), 0);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(colision2_t) {
  GameInfo_t game;
  tetromino current = generateFigure(Q);
  tetromino nextable = generateFigure(Q);

  init(&game, &current, &nextable);

  current.posX = 0;
  ck_assert_int_eq(colision(&game, &current), 1);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(checkfield_t) {
  GameInfo_t game;
  tetromino current = generateFigure(Q);
  tetromino nextable = generateFigure(Q);

  init(&game, &current, &nextable);

  for (int j = 1; j < FIELD_X - 1; j++) {
    game.field[1][j] = 'X';
  }

  checkField(&game);

  for (int j = 1; j < FIELD_X - 1; j++) {
    ck_assert_int_eq(game.field[1][j], ' ');
  }

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(checkfield1_t) {
  GameInfo_t game;
  tetromino current = generateFigure(Q);
  tetromino nextable = generateFigure(Q);

  init(&game, &current, &nextable);
  for (int i = 1; i <= 2; i++) {
    for (int j = 1; j < FIELD_X - 1; j++) {
      game.field[i][j] = 'X';
    }
  }

  checkField(&game);

  for (int i = 1; i <= 2; i++) {
    for (int j = 1; j < FIELD_X - 1; j++) {
      ck_assert_int_eq(game.field[1][j], ' ');
    }
  }

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(checkfield2_t) {
  GameInfo_t game;
  tetromino current = generateFigure(Q);
  tetromino nextable = generateFigure(Q);

  init(&game, &current, &nextable);
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j < FIELD_X - 1; j++) {
      game.field[i][j] = 'X';
    }
  }

  checkField(&game);

  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j < FIELD_X - 1; j++) {
      ck_assert_int_eq(game.field[1][j], ' ');
    }
  }

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(checkfield3_t) {
  GameInfo_t game;
  tetromino current = generateFigure(Q);
  tetromino nextable = generateFigure(Q);

  init(&game, &current, &nextable);
  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j < FIELD_X - 1; j++) {
      game.field[i][j] = 'X';
    }
  }

  checkField(&game);

  for (int i = 1; i <= 4; i++) {
    for (int j = 1; j < FIELD_X - 1; j++) {
      ck_assert_int_eq(game.field[1][j], ' ');
    }
  }

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(tetrominoState_t) {
  GameInfo_t game;
  tetromino current;
  tetromino nextable;
  UserAction_t action;

  init(&game, &current, &nextable);

  game.level = 0;

  updateTetrominoState(&current, &nextable, &game, &action);

  ck_assert_int_eq(action, Terminate);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(tetrominoState1_t) {
  GameInfo_t game;
  tetromino current;
  tetromino nextable;
  UserAction_t action = Start;

  init(&game, &current, &nextable);

  game.pause = 1;

  updateTetrominoState(&current, &nextable, &game, &action);

  ck_assert_int_eq(game.pause, 0);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(tetrominoState2_t) {
  GameInfo_t game;
  tetromino current;
  tetromino nextable;
  UserAction_t action = Start;

  init(&game, &current, &nextable);

  game.pause = 0;

  updateTetrominoState(&current, &nextable, &game, &action);

  ck_assert_int_eq(game.pause, 0);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(tetrominoState3_t) {
  GameInfo_t game;
  tetromino current;
  tetromino nextable;
  UserAction_t action = Pause;

  init(&game, &current, &nextable);

  game.pause = 0;

  updateTetrominoState(&current, &nextable, &game, &action);

  ck_assert_int_eq(game.pause, 1);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(tetrominoState4_t) {
  GameInfo_t game;
  tetromino current;
  tetromino nextable;
  UserAction_t action = Left;

  init(&game, &current, &nextable);

  game.pause = 0;

  setFigure(&game, 0, &current);

  updateTetrominoState(&current, &nextable, &game, &action);

  ck_assert_int_eq(current.posX, 4);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(tetrominoState5_t) {
  GameInfo_t game;
  tetromino current;
  tetromino nextable;
  UserAction_t action = Right;

  init(&game, &current, &nextable);

  game.pause = 0;

  setFigure(&game, 0, &current);

  updateTetrominoState(&current, &nextable, &game, &action);

  ck_assert_int_eq(current.posX, 6);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(tetrominoState6_t) {
  GameInfo_t game;
  tetromino current;
  tetromino nextable;
  UserAction_t action = Up;

  init(&game, &current, &nextable);

  game.pause = 0;

  setFigure(&game, 0, &current);

  updateTetrominoState(&current, &nextable, &game, &action);

  ck_assert_int_eq(current.posX, 5);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(tetrominoState7_t) {
  GameInfo_t game;
  tetromino current;
  tetromino nextable;
  UserAction_t action = Down;

  init(&game, &current, &nextable);

  game.pause = 0;

  setFigure(&game, 0, &current);

  updateTetrominoState(&current, &nextable, &game, &action);

  ck_assert_int_eq(current.posY, 2);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(tetrominoState8_t) {
  GameInfo_t game;
  tetromino current;
  tetromino nextable;
  UserAction_t action = Action;

  init(&game, &current, &nextable);

  game.pause = 0;

  current = generateFigure(Q);

  setFigure(&game, 0, &current);

  updateTetrominoState(&current, &nextable, &game, &action);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(tetrominoState9_t) {
  GameInfo_t game;
  tetromino current;
  tetromino nextable;
  UserAction_t action = Terminate;

  init(&game, &current, &nextable);

  game.pause = 0;

  setFigure(&game, 0, &current);

  updateTetrominoState(&current, &nextable, &game, &action);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(tetrominoState10_t) {
  GameInfo_t game;
  tetromino current;
  tetromino nextable;
  UserAction_t action = -1;

  init(&game, &current, &nextable);

  game.pause = 0;

  setFigure(&game, 0, &current);

  updateTetrominoState(&current, &nextable, &game, &action);

  ck_assert_int_eq(current.posY, 3);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(levelcheck_t) {
  GameInfo_t game;
  game.level = 0;
  game.score = 100;

  levelCheck(&game);

  ck_assert_int_eq(game.level, 0);
}

START_TEST(levelcheck1_t) {
  GameInfo_t game;
  game.level = 1;
  game.score = 100;

  levelCheck(&game);

  ck_assert_int_eq(game.level, 1);
}

START_TEST(levelcheck2_t) {
  GameInfo_t game;
  tetromino current, nextable;
  init(&game, &current, &nextable);
  game.level = 1;
  game.score = 600;

  levelCheck(&game);

  ck_assert_int_eq(game.level, 2);

  clean(&game, &current, &nextable);
}

START_TEST(levelcheck3_t) {
  GameInfo_t game;
  tetromino current, nextable;
  init(&game, &current, &nextable);
  game.level = 1;
  game.score = 1600;

  levelCheck(&game);

  ck_assert_int_eq(game.level, 3);
  clean(&game, &current, &nextable);
}

START_TEST(levelcheck4_t) {
  GameInfo_t game;
  tetromino current, nextable;
  init(&game, &current, &nextable);
  game.level = 1;
  game.score = 666666;

  levelCheck(&game);

  ck_assert_int_eq(game.level, 10);
  clean(&game, &current, &nextable);
}

START_TEST(updateCurrentState_t) {
  GameInfo_t game;
  tetromino current, nextable;

  init(&game, &current, &nextable);

  game = updateCurrentState(game);
}
END_TEST

START_TEST(updateCurrentState1_t) {
  GameInfo_t game;
  tetromino current, nextable;

  init(&game, &current, &nextable);

  game.level = 2;
  game.score = 600;

  game = updateCurrentState(game);
}
END_TEST

START_TEST(updateCurrentState2_t) {
  GameInfo_t game;
  tetromino current, nextable;

  init(&game, &current, &nextable);

  game.level = 3;
  game.score = 600 * 2;

  game = updateCurrentState(game);
}
END_TEST

START_TEST(updateCurrentState3_t) {
  GameInfo_t game;
  tetromino current, nextable;

  init(&game, &current, &nextable);

  game.level = 4;
  game.score = 600 * 3;

  game = updateCurrentState(game);
}
END_TEST

START_TEST(updateCurrentState4_t) {
  GameInfo_t game;
  tetromino current, nextable;

  init(&game, &current, &nextable);

  game.level = 5;
  game.score = 600 * 4;

  game = updateCurrentState(game);
}
END_TEST

START_TEST(updateCurrentState5_t) {
  GameInfo_t game;
  tetromino current, nextable;

  init(&game, &current, &nextable);

  game.level = 6;
  game.score = 600 * 5;

  game = updateCurrentState(game);
}
END_TEST

START_TEST(updateCurrentState6_t) {
  GameInfo_t game;
  tetromino current, nextable;

  init(&game, &current, &nextable);

  game.level = 7;
  game.score = 600 * 6;

  game = updateCurrentState(game);
}
END_TEST

START_TEST(updateCurrentState7_t) {
  GameInfo_t game;
  tetromino current, nextable;

  init(&game, &current, &nextable);

  game.level = 8;
  game.score = 600 * 7;

  game = updateCurrentState(game);
}
END_TEST

START_TEST(updateCurrentState8_t) {
  GameInfo_t game;
  tetromino current, nextable;

  init(&game, &current, &nextable);

  game.level = 9;
  game.score = 600 * 8;

  game = updateCurrentState(game);
}
END_TEST

START_TEST(updateCurrentState9_t) {
  GameInfo_t game;
  tetromino current, nextable;

  init(&game, &current, &nextable);

  game.level = 10;
  game.score = 600 * 9;

  game = updateCurrentState(game);
}
END_TEST

START_TEST(savedata1_t) {
  GameInfo_t game;
  tetromino current, nextable;

  init(&game, &current, &nextable);

  savedata(&game, 0);
}

START_TEST(savedata2_t) {
  GameInfo_t game;
  tetromino current, nextable;

  init(&game, &current, &nextable);

  savedata(&game, 1);
}

START_TEST(userInput1_t) {
  UserAction_t action;

  userInput(&action);
}
END_TEST

START_TEST(flip_t) {
  GameInfo_t game;
  tetromino current;
  tetromino nextable = generateFigure(Q);

  init(&game, &current, &nextable);

  current = generateFigure(I);

  current.posX = 9;
  flip(&game, &current);

  ck_assert_int_eq(current.tet.rows, 4);
  ck_assert_int_eq(current.tet.cols, 1);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(genfig1) {
  tetromino test;

  test = generateFigure(T);

  ck_assert_int_eq(test.fig, T);
}
END_TEST

START_TEST(genfig2) {
  tetromino test;

  test = generateFigure(Q);

  ck_assert_int_eq(test.fig, Q);
}
END_TEST

START_TEST(genfig3) {
  tetromino test;

  test = generateFigure(I);

  ck_assert_int_eq(test.fig, I);
}
END_TEST

START_TEST(genfig4) {
  tetromino test;

  test = generateFigure(Z);

  ck_assert_int_eq(test.fig, Z);
}
END_TEST

START_TEST(genfig5) {
  tetromino test;

  test = generateFigure(S);

  ck_assert_int_eq(test.fig, S);
}
END_TEST

START_TEST(genfig6) {
  tetromino test;

  test = generateFigure(J);

  ck_assert_int_eq(test.fig, J);
}
END_TEST

START_TEST(genfig7) {
  tetromino test;

  test = generateFigure(L);

  ck_assert_int_eq(test.fig, L);
}
END_TEST

START_TEST(set1) {
  GameInfo_t game;
  tetromino t1, t2;
  init(&game, &t1, &t2);

  t1 = generateFigure(T);

  setFigure(&game, 0, &t1);

  ck_assert_int_eq((int)game.field[2][5], (int)'#');

  unsetFigure(&game, &t1);

  int colis = colision(&game, &t1);

  ck_assert_int_eq(colis, 0);

  ck_assert_int_eq((int)game.field[2][5], (int)' ');

  setFigure(&game, 1, &t1);

  setFigure(&game, 1, &t2);

  colis = colision(&game, &t2);

  ck_assert_int_eq(colis, 1);

  ck_assert_int_eq((int)game.field[2][5], (int)'X');

  nextFigure(&game, &t1, &t2);

  clean(&game, &t1, &t2);
}
END_TEST

START_TEST(freeFigure1) {
  tetromino t1 = generateFigure(T);

  freeFigure(&t1);
}
END_TEST

START_TEST(movement) {
  GameInfo_t game;
  tetromino t1, t2;

  init(&game, &t1, &t2);

  setFigure(&game, 0, &t1);

  movedown(&game, &t1, &t2);

  moveleft(&game, &t1);

  moveright(&game, &t1);

  flipRight(&t1);

  flipLeft(&t1);

  dropdown(&game, &t1, &t2);
}
END_TEST

START_TEST(movement_t) {
  GameInfo_t game;
  tetromino current;
  tetromino nextable;

  init(&game, &current, &nextable);

  current = generateFigure(Q);
  nextable = generateFigure(T);

  current.posY = 18;
  movedown(&game, &current, &nextable);

  ck_assert_int_eq(current.fig, T);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(movement1_t) {
  GameInfo_t game;
  tetromino current;
  tetromino nextable;

  init(&game, &current, &nextable);

  current = generateFigure(Q);
  nextable = generateFigure(T);

  current.posX = 1;
  moveleft(&game, &current);

  ck_assert_int_eq(current.posX, 1);

  clean(&game, &current, &nextable);
}
END_TEST

START_TEST(movement2_t) {
  GameInfo_t game;
  tetromino current;
  tetromino nextable;

  init(&game, &current, &nextable);

  current = generateFigure(Q);
  nextable = generateFigure(T);

  current.posX = 9;
  moveright(&game, &current);

  ck_assert_int_eq(current.posX, 9);

  clean(&game, &current, &nextable);
}
END_TEST

Suite *tetris(void) {
  Suite *s = suite_create("Tetris");

  TCase *tc_init_t = tcase_create("initialization tasting");
  tcase_add_test(tc_init_t, init_t);

  TCase *tc_changeNext_t = tcase_create("Generate figure");
  tcase_add_test(tc_changeNext_t, genfig_t);

  TCase *tc_colision = tcase_create("Colision figure");
  tcase_add_test(tc_colision, colision_t);
  tcase_add_test(tc_colision, colision1_t);
  tcase_add_test(tc_colision, colision2_t);

  TCase *tc_checkfield = tcase_create("Check field");
  tcase_add_test(tc_checkfield, checkfield_t);
  tcase_add_test(tc_checkfield, checkfield1_t);
  tcase_add_test(tc_checkfield, checkfield2_t);
  tcase_add_test(tc_checkfield, checkfield3_t);

  TCase *tc_tetrominoState = tcase_create("Tetromino State");
  tcase_add_test(tc_tetrominoState, tetrominoState_t);
  tcase_add_test(tc_tetrominoState, tetrominoState1_t);
  tcase_add_test(tc_tetrominoState, tetrominoState2_t);
  tcase_add_test(tc_tetrominoState, tetrominoState3_t);
  tcase_add_test(tc_tetrominoState, tetrominoState4_t);
  tcase_add_test(tc_tetrominoState, tetrominoState5_t);
  tcase_add_test(tc_tetrominoState, tetrominoState6_t);
  tcase_add_test(tc_tetrominoState, tetrominoState7_t);
  tcase_add_test(tc_tetrominoState, tetrominoState8_t);
  tcase_add_test(tc_tetrominoState, tetrominoState9_t);
  tcase_add_test(tc_tetrominoState, tetrominoState10_t);

  TCase *tc_levelcheck = tcase_create("Level Check");
  tcase_add_test(tc_levelcheck, levelcheck_t);
  tcase_add_test(tc_levelcheck, levelcheck1_t);
  tcase_add_test(tc_levelcheck, levelcheck2_t);
  tcase_add_test(tc_levelcheck, levelcheck3_t);
  tcase_add_test(tc_levelcheck, levelcheck4_t);

  TCase *tc_updateCurrentState = tcase_create("Update Current State");
  tcase_add_test(tc_updateCurrentState, updateCurrentState_t);
  tcase_add_test(tc_updateCurrentState, updateCurrentState1_t);
  tcase_add_test(tc_updateCurrentState, updateCurrentState2_t);
  tcase_add_test(tc_updateCurrentState, updateCurrentState3_t);
  tcase_add_test(tc_updateCurrentState, updateCurrentState4_t);
  tcase_add_test(tc_updateCurrentState, updateCurrentState5_t);
  tcase_add_test(tc_updateCurrentState, updateCurrentState6_t);
  tcase_add_test(tc_updateCurrentState, updateCurrentState7_t);
  tcase_add_test(tc_updateCurrentState, updateCurrentState8_t);
  tcase_add_test(tc_updateCurrentState, updateCurrentState9_t);

  TCase *tc_savedata = tcase_create("savedata");
  tcase_add_test(tc_savedata, savedata1_t);
  tcase_add_test(tc_savedata, savedata2_t);

  TCase *tc_userInput = tcase_create("UserInput");
  tcase_add_test(tc_userInput, userInput1_t);

  TCase *tc_flip = tcase_create("Flip figure");
  tcase_add_test(tc_flip, flip_t);

  TCase *tc_genfig1 = tcase_create("gen_figure_T");
  tcase_add_test(tc_genfig1, genfig1);
  tcase_add_test(tc_genfig1, genfig2);
  tcase_add_test(tc_genfig1, genfig3);
  tcase_add_test(tc_genfig1, genfig4);
  tcase_add_test(tc_genfig1, genfig5);
  tcase_add_test(tc_genfig1, genfig6);
  tcase_add_test(tc_genfig1, genfig7);

  TCase *tc_set1 = tcase_create("setfigure1");
  tcase_add_test(tc_set1, set1);

  TCase *tc_ff = tcase_create("free figure");
  tcase_add_test(tc_ff, freeFigure1);

  TCase *tc_move = tcase_create("movement");
  tcase_add_test(tc_move, movement);
  tcase_add_test(tc_move, movement_t);
  tcase_add_test(tc_move, movement1_t);
  tcase_add_test(tc_move, movement2_t);

  suite_add_tcase(s, tc_init_t);
  suite_add_tcase(s, tc_changeNext_t);
  suite_add_tcase(s, tc_colision);
  suite_add_tcase(s, tc_checkfield);
  suite_add_tcase(s, tc_tetrominoState);
  suite_add_tcase(s, tc_levelcheck);
  suite_add_tcase(s, tc_updateCurrentState);
  suite_add_tcase(s, tc_savedata);
  suite_add_tcase(s, tc_userInput);
  suite_add_tcase(s, tc_flip);
  suite_add_tcase(s, tc_genfig1);
  suite_add_tcase(s, tc_set1);
  suite_add_tcase(s, tc_ff);
  suite_add_tcase(s, tc_move);

  return s;
}

int main(void) {
  Suite *s = tetris();
  SRunner *runner;

  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);

  srunner_free(runner);

  return 0;
}
