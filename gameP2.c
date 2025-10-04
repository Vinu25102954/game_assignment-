#include <stdio.h>
#include <stdlib.h> // for memory functions and random numbers
#include <time.h> // for time functions to make random numbers different each time

// Create the game board
void createBoard(char board[10][10], int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            board[i][j] = ' ';
        }
    }
}

// Show the board
void showBoard(char board[10][10], int size) {
    printf("\nCurrent Board:\n");
    
    // Show column numbers
    printf("  ");
    for(int j = 0; j < size; j++) {
        printf(" %d ", j + 1);
    }
    printf("\n");
    
    // Show the board with borders
    for(int i = 0; i < size; i++) {
        printf("%d ", i + 1);
        for(int j = 0; j < size; j++) {
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
    for(i = 0; i < size; i++) {
        int win = 1;
        for(j = 0; j < size; j++) {
            if(board[i][j] != player) {
                win = 0;
                break;
            }
        }
        if(win == 1) return 1;
    }
    
    // Check columns
    for(j = 0; j < size; j++) {
        int win = 1;
        for(i = 0; i < size; i++) {
            if(board[i][j] != player) {
                win = 0;
                break;
            }
        }
        if(win == 1) return 1;
    }
    
    // Check diagonal 1 (top-left to bottom-right)
    int win = 1;
    for(i = 0; i < size; i++) {
        if(board[i][i] != player) {
            win = 0;
            break;
        }
    }
    if(win == 1) return 1;
    
    // Check diagonal 2 (top-right to bottom-left)
    win = 1;
    for(i = 0; i < size; i++) {
        if(board[i][size - 1 - i] != player) {
            win = 0;
            break;
        }
    }
    if(win == 1) return 1;
    
    return 0;
}

// Check if game is a draw
int checkDraw(char board[10][10], int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(board[i][j] == ' ') {
                return 0; // Not a draw, empty space found
            }
        }
    }
    return 1; // Draw, no empty spaces
}

// Computer makes a random move
void computerMove(char board[10][10], int size) {
    int row, col;
    
    // Keep trying until we find an empty spot
    do {
        row = rand() % size; // Random number from 0 to size - 1
        col = rand() % size;
    } while(board[row][col] != ' ');
    
    // Make the move
    board[row][col] = 'O';
    printf("Computer placed O at position %d %d\n", row + 1, col + 1);
}

int main() {
    char board[10][10];
    int size;
    int gameOver = 0;
    int moves = 0;
    
    // Initialize random number generator
    srand(time(0));
    
    printf("=== Tic Tac Toe - Player vs Computer ===\n");
    
    // Get board size
    printf("Enter board size (3-10): ");
    scanf("%d", &size);
    
    // Simple size check
    if(size < 3 || size > 10) {
        printf("Invalid size! Using default size 3.\n");
        size = 3;
    }
    
    // Create the board
    createBoard(board, size);
    
    // Open log file
    FILE *file = fopen("game_log.txt", "w");
    if(file == NULL) {
        printf("Note: Could not create log file.\n");
    } else {
        fprintf(file, "Tic Tac Toe - Player vs Computer\n");
        fprintf(file, "Board Size: %d\n\n", size);
    }
    
    printf("\nGame Started!\n");
    printf("Player: X, Computer: O\n");
    printf("Enter row and column numbers (example: 1 2)\n\n");
    
    // Main game loop
    while(!gameOver) {
        showBoard(board, size);
        
        // Write to log file
        if(file != NULL) {
            fprintf(file, "Move %d:\n", moves);
            for(int i = 0; i < size; i++) {
                for(int j = 0; j < size; j++) {
                    fprintf(file, "%c ", board[i][j]);
                }
                fprintf(file, "\n");
            }
            fprintf(file, "\n");
        }
        
        // Player's turn (X)
        int row, col;
        printf("Your turn (X): ");
        scanf("%d %d", &row, &col);
        
        // Convert to array indices
        row--;
        col--;
        
        // Check if move is valid
        if(row < 0 || row >= size || col < 0 || col >= size) {
            printf("Invalid position! Use numbers 1 to %d.\n", size);
            continue;
        }
        
        if(board[row][col] != ' ') {
            printf("That spot is already taken!\n");
            continue;
        }
        
        // Player makes a move
        board[row][col] = 'X';
        moves++;
        
        // Check if player won
        if(checkWin(board, size, 'X')) {
            showBoard(board, size);
            printf("*** YAY YOU WIN! ***\n");
            if(file != NULL) {
                fprintf(file, "Player (X) WINS!\n");
            }
            gameOver = 1;
        }
        // Check for draw
        else if(checkDraw(board, size)) {
            showBoard(board, size);
            printf("*** IT'S A DRAW! ***\n");
            if(file != NULL) {
                fprintf(file, "Game ended in a DRAW!\n");
            }
            gameOver = 1;
        }
        else {
            // Computer's turn (O)
            printf("\nComputer's turn...\n");
            computerMove(board, size);
            moves++;
            
            // Check if computer won
            if(checkWin(board, size, 'O')) {
                showBoard(board, size);
                printf("*** OOPS COMPUTER WINS! ***\n");
                if(file != NULL) {
                    fprintf(file, "Computer (O) WINS!\n");
                }
                gameOver = 1;
            }
            // Check for draw
            else if(checkDraw(board, size)) {
                showBoard(board, size);
                printf("*** IT'S A DRAW! ***\n");
                if(file != NULL) {
                    fprintf(file, "Game ended in a DRAW!\n");
                }
                gameOver = 1;
            }
        }
    }
    
    // Close file
    if(file != NULL) {
        fclose(file);
        printf("Game saved to 'game_log.txt'\n");
    }
    
    printf("\nThanks for playing!\n");
    return 0;
}

