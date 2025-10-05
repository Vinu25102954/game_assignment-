#ifndef TICTACTOE_H
#define TICTACTOE_H

// Include standard libraries
#include <stdio.h>

//  Function Prototypes 

// Board creation and display
void createBoard(char board[10][10], int size);
void showBoard(char board[10][10], int size);

// Game logic (2-player & vs computer)
int checkWin(char board[10][10], int size, char player);
int checkDraw(char board[10][10], int size);
void computerMove(char board[10][10], int size);

// 3-player mode functions
void displayBoard3x3(char board[3][3]);
int checkWin3x3(char board[3][3], char symbol);
int isBoardFull3x3(char board[3][3]);
void computerMove3x3(char board[3][3], int *row, int *col);

// Menu
int showMenu();

#endif
