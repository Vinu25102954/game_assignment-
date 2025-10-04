#include <stdio.h>
#include <stdlib.h>

// Create the game board
void createBoard(char board[10][10], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = ' ';
        }
    }
}

// Show the board
void showBoard(char board[10][10], int size) {
    printf("\nCurrent Board:\n");

    // Show column numbers
    printf("  ");
    for (int j = 0; j < size; j++) {
        printf(" %d ", j + 1);
    }
    printf("\n");

    // Show the board with borders
    for (int i = 0; i < size; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < size; j++) {
            printf("|%c", board[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}

// Check if someone won
int checkWin(char board[10][10], int size, char player) {
    int i, j;

    // Check rows
    for (i = 0; i < size; i++) {
        int win = 1;
        for (j = 0; j < size; j++) {
            if (board[i][j] != player) {
                win = 0;
                break;
            }
        }
        if (win == 1) return 1;
    }

    // Check columns
    for (j = 0; j < size; j++) {
        int win = 1;
        for (i = 0; i < size; i++) {
            if (board[i][j] != player) {
                win = 0;
                break;
            }
        }
        if (win == 1) return 1;
    }

    // Check diagonal 1 (top-left to bottom-right)
    int win = 1;
    for (i = 0; i < size; i++) {
        if (board[i][i] != player) {
            win = 0;
            break;
        }
    }
    if (win == 1) return 1;

    // Check diagonal 2 (top-right to bottom-left)
    win = 1;
    for (i = 0; i < size; i++) {
        if (board[i][size - 1 - i] != player) {
            win = 0;
            break;
        }
    }
    if (win == 1) return 1;

    return 0;
}

// Check if game is a draw
int checkDraw(char board[10][10], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == ' ') {
                return 0; // Not a draw, found an empty space
            }
        }
    }
    return 1; // Draw, no empty spaces
}

int main() {
    char board[10][10]; // Fixed-size array
    int size;
    char currentPlayer = 'X';
    int gameOver = 0;
    int moves = 0;

    printf("=== Tic Tac Toe Game ===\n");

    // Get board size
    printf("Enter board size (3-10): ");
    scanf("%d", &size);

    // Simple size check
    if (size < 3 || size > 10) {
        printf("Invalid size! Using default size 3.\n");
        size = 3;
    }

    // Create the board
    createBoard(board, size);

    // Open log file
    FILE *file = fopen("game_log.txt", "w");
    if (file == NULL) {
        printf("Note: Could not create log file.\n");
    } else {
        fprintf(file, "Tic Tac Toe Game - Board Size: %d\n\n", size);
    }

    printf("\nGame Started!\n");
    printf("Player 1: X, Player 2: O\n");
    printf("Enter row and column numbers (example: 1 2)\n\n");

    // Main game loop
    while (!gameOver) {
        showBoard(board, size);

        // Write to log file
        if (file != NULL) {
            fprintf(file, "Move %d - Player %c's turn:\n", moves, currentPlayer);
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    fprintf(file, "%c ", board[i][j]);
                }
                fprintf(file, "\n");
            }
            fprintf(file, "\n");
        }

        int row, col;
        printf("Player %c's turn: ", currentPlayer);
        scanf("%d %d", &row, &col);

        // Convert to array indices
        row--;
        col--;

        // Check if move is valid
        if (row < 0 || row >= size || col < 0 || col >= size) {
            printf("Invalid position! Use numbers 1 to %d.\n", size);
            continue;
        }

        if (board[row][col] != ' ') {
            printf("That spot is already taken!\n");
            continue;
        }

        // Make the move
        board[row][col] = currentPlayer;
        moves++;

        // Check for win
        if (checkWin(board, size, currentPlayer)) {
            showBoard(board, size);
            printf("*** Player %c WINS! ***\n", currentPlayer);
            if (file != NULL) {
                fprintf(file, "Player %c WINS!\n", currentPlayer);
            }
            gameOver = 1;
        }
        // Check for draw
        else if (checkDraw(board, size)) {
            showBoard(board, size);
            printf("*** It's a DRAW! ***\n");
            if (file != NULL) {
                fprintf(file, "Game ended in DRAW!\n");
            }
            gameOver = 1;
        }
        // Switch players
        else {
            if (currentPlayer == 'X') {
                currentPlayer = 'O';
            } else {
                currentPlayer = 'X';
            }
        }
    }

    // Close file
    if (file != NULL) {
        fclose(file);
        printf("Game saved to 'game_log.txt'\n");
    }

    printf("\nThanks for playing!\n");
    return 0;
}
