//
//  game_func.h
//  Itg_tac_toe
//
//  Created by Jiao jeremy on 2024/1/7.
//

#ifndef game_func_h
#define game_func_h

#define ROW 4
#define COL 4



#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#endif /* game_func_h */

void init_board(char board[ROW][COL]);

void display_board(char board[ROW][COL]);

void player_step(char board[ROW][COL]);

// Dont need
// int scan_wrong_input(int row, int col);

void computer_step(char board[ROW][COL]);

char judge(char board[ROW][COL], char c);
char tictactoe(char board[ROW][COL]);
