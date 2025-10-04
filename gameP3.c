#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to display the game board
void displayBoard(char board[3][3]) {
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

// Function to check if a player has won
int checkWin(char board[3][3], char symbol) {
    // Check rows, columns and diagonals
    for (int i = 0; i < 3; i++) {
        // Check rows
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
            return 1;
        // Check columns
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
            return 1;
    }
    // Check diagonals
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
        return 1;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
        return 1;

    return 0;
}

// Function to check if the board is full
int isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ')
                return 0;
        }
    }
    return 1;
}

// Function to save move to log file
void logMove(FILE *logFile, int player, int row, int col, char symbol) {
    fprintf(logFile, "Player %d (%c) moved to position (%d,%d)\n", player, symbol, row + 1, col + 1);
    fflush(logFile);
}

// Function for computer to make a random move
void computerMove(char board[3][3], int *row, int *col) {
    do {
        *row = rand() % 3;
        *col = rand() % 3;
    } while (board[*row][*col] != ' ');
}

int main() {
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char symbols[3] = {'X', 'O', 'Z'};
    int playerTypes[3]; // 0 = human, 1 = computer
    int currentPlayer = 0;
    int gameOver = 0;
    int row, col;

    // Seed random number generator
    srand(time(NULL));

    // Open log file
    FILE *logFile = fopen("game_log.txt", "w");
    if (logFile == NULL) {
        printf("Error creating log file!\n");
        return 1;
    }
    fprintf(logFile, "=== 3-Player Tic-Tac-Toe Game Log ===\n");

    printf("=== Welcome to 3-Player Tic-Tac-Toe! ===\n\n");

    // Player configuration
    printf("Player Configuration:\n");
    printf("Player 1 will use 'X'\n");
    printf("Player 2 will use 'O'\n");
    printf("Player 3 will use 'Z'\n\n");

    for (int i = 0; i < 3; i++) {
        int choice;
        printf("Should Player %d (%c) be:\n", i + 1, symbols[i]);
        printf("1. Human\n");
        printf("2. Computer\n");
        printf("Enter your choice (1 or 2): ");
        scanf("%d", &choice);
        playerTypes[i] = (choice == 1) ? 0 : 1;
    }

    printf("\nGame starting! Here's the empty board:\n");
    displayBoard(board);

    // Main game loop
    while (!gameOver) {
        printf("=== Player %d's Turn (%c) ===\n", currentPlayer + 1, symbols[currentPlayer]);

        if (playerTypes[currentPlayer] == 0) { // Human player
            int validMove = 0;
            while (!validMove) {
                printf("Enter your move (row and column, 1-3): ");
                scanf("%d %d", &row, &col);

                // Convert to 0-based indexing
                row--;
                col--;

                if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                    validMove = 1;
                } else {
                    printf("Invalid move! Please choose an empty spot (1-3).\n");
                }
            }
        } else { // Computer player
            printf("Computer is thinking...\n");
            computerMove(board, &row, &col);
            printf("Computer chooses position (%d,%d)\n", row + 1, col + 1);
        }

        // Make the move
        board[row][col] = symbols[currentPlayer];
        logMove(logFile, currentPlayer + 1, row, col, symbols[currentPlayer]);

        // Display updated board
        displayBoard(board);

        // Check for win
        if (checkWin(board, symbols[currentPlayer])) {
            printf("Player %d (%c) wins!\n", currentPlayer + 1, symbols[currentPlayer]);
            fprintf(logFile, "Player %d (%c) WINS THE GAME!\n", currentPlayer + 1, symbols[currentPlayer]);
            gameOver = 1;
        }
        // Check for draw
        else if (isBoardFull(board)) {
            printf("It's a draw! The board is full.\n");
            fprintf(logFile, "The game ended in a DRAW!\n");
            gameOver = 1;
        }

        // Move to next player
        currentPlayer = (currentPlayer + 1) % 3;
    }

    printf("\nThanks for playing! Game log saved to 'game_log.txt'\n");
    fclose(logFile);

    return 0;
}

