//
//  main.c
//  Itg_tac_toe
//
//  Created by Jiao jeremy on 2024/1/7.
//

#include "game_func.h"



void menu(void){
    printf("---------------------------------\n");
    printf("---------- 1. PLAY --------------\n");
    printf("---------- 0. EXIT --------------\n");
    printf("---------------------------------\n");
}

void game(void){
    char board[ROW][COL];
    printf("Board Shape %d X %d \n", ROW, COL);
    init_board(board); // Init board
    display_board(board); // Display board
    while(1)
    {
        player_step(board); // Player step
        computer_step(board); // Computer step
        if(tictactoe(board) != 'P') break; // Judge
    }
    if (tictactoe(board) == '*')
    {
        printf("Player Win \n");
    }
    else if(tictactoe(board) == '#')
    {
        printf("Computer Win \n");
    }
    else
    {
        printf("Draw \n");
    }
    display_board(board);
}

int main(void) {
    int input = 3;
    // Game start screen
    do {
        menu();
        printf("Enter Number\n");
        scanf("%d", &input);
        switch (input) {
            case 1:
                game();
                break;
                
            case 0:
                break;
                
            default:
                printf("Wrong Number, Try Again \n");
                while (getchar() != '\n');
                break;
        }
    }while (input);
return 0;
}
