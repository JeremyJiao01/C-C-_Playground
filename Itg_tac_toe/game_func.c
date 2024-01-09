//
//  game_func.c
//  Itg_tac_toe
//
//  Created by Jiao jeremy on 2024/1/7.
//

#include "game_func.h"


void init_board(char board[ROW][COL]){
    
    int i = 0;
    int j = 0;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            board[i][j] = ' ';
        }
    }
}



void display_board(char board[ROW][COL]){
    
    int i = 0;
    int j = 0;
    for (i = 0; i < ROW; i++) {
        for (j = 0; j< COL; j++) {
            printf(" %c ", board[i][j]);
            if (j < COL - 1) {
                printf("| ");
            }
        }
        printf("\n");
        if (i < ROW - 1) {
            int j = 0;
            for (j = 0; j < COL; j++) {
                printf("----");
            }
        }
        printf("\n");
    }
}



void player_step(char board[ROW][COL]){
    
    int row = 0;
    int col = 0;
    // Judge input correction
    while (1) {
        printf("Please Enter The Point Position \n");
        if (scanf("%d %d", &row, &col) == 2) {  
            // Check if exactly two integers were read
            // The return value of scanf is the number of valid input
            if (row > 0 && row <= ROW && col > 0 && col <= COL) {
                // Judge input position empty
                if (board[row - 1][col - 1] == ' ') {
                    break; // Input is valid, break the loop
                }
                else printf("The position has occupied, Try Again \n");
            } 
            else printf("Input is out of range \n");  // Input is out of range
        }
        else {
            printf("Wrong Input \n");  // Input is not two integers
            // Clear the input buffer
            while (getchar() != '\n');
        }
    }
    
    printf("Player Turn \n");
    board[row - 1][col - 1] = '*';
    display_board(board);
    
}



void computer_step(char board[ROW][COL]){
    
    int row = 0;
    int col = 0;
    
    srand((unsigned int)time(NULL));
    
    while (1) {
        row = rand() % ROW;
        col = rand() % COL;
        
        if (board[row][col] == ' ') {
            board[row][col] = '#';
            break;
        }
    }
    printf("Computer Turn \n");
    display_board(board);
}



char judge(char board[ROW][COL], char c) {
    // 检查行
    for (int i = 0; i < ROW; ++i) {
        bool row_win = true;
        for (int j = 0; j < COL; ++j) {
            if (board[i][j] != c) {
                row_win = false;
                break;
            }
        }
        if (row_win) return true;
    }

    // 检查列
    for (int j = 0; j < COL; ++j) {
        bool col_win = true;
        for (int i = 0; i < ROW; ++i) {
            if (board[i][j] != c) {
                col_win = false;
                break;
            }
        }
        if (col_win) return true;
    }

    // 检查对角线
    bool diag_win = true;
    for (int i = 0; i < ROW; ++i) {
        if (board[i][i] != c) {
            diag_win = false;
            break;
        }
    }
    if (diag_win) return true;

    // 检查反对角线
    diag_win = true;
    for (int i = 0; i < ROW; ++i) {
        if (board[i][ROW-1-i] != c) {
            diag_win = false;
            break;
        }
    }
    if (diag_win) return true;

    return false;
}

char tictactoe(char board[ROW][COL]) {
    if (judge(board, '*')) return '*';
    if (judge(board, '#')) return '#';

    // 检查是否还有空位
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (board[i][j] == ' ') return 'P'; // Pending
        }
    }

    // 平局
    return 'D'; // Draw
}
