#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// Special 3-player mode functions
void displayBoard3x3(char board[3][3]) {
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int checkWin3x3(char board[3][3], char symbol) {
    // Check rows
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
            return 1;
    }
    
    // Check columns
    for(int i = 0; i < 3; i++) {
        if(board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
            return 1;
    }
    
    // Check diagonals
    if(board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
        return 1;
    if(board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
        return 1;

    return 0;
}

int isBoardFull3x3(char board[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == ' ')
                return 0;
        }
    }
    return 1;
}

void computerMove3x3(char board[3][3], int *row, int *col) {
    do {
        *row = rand() % 3;
        *col = rand() % 3;
    } while(board[*row][*col] != ' ');
}

// Main menu
int showMenu() {
    int choice;
    printf("\n=== TIC TAC TOE GAME ===\n");
    printf("1. 2 Players (Human vs Human)\n");
    printf("2. Player vs Computer\n");
    printf("3. 3 Players (Special 3x3 mode)\n");
    printf("4. Exit\n");
    printf("Choose game mode (1-4): ");
    scanf("%d", &choice);
    return choice;
}

int main() {
    srand(time(0)); // Initialize random number generator
    
    while(1) {
        int choice = showMenu();
        
        if(choice == 1) {
            // 2 Player mode
            char board[10][10];
            int size;
            char currentPlayer = 'X';
            int gameOver = 0;
            int moves = 0;

            printf("\n=== 2 Player Tic Tac Toe ===\n");
            printf("Enter board size (3-10): ");
            scanf("%d", &size);

            if(size < 3 || size > 10) {
                printf("Invalid size! Using default size 3.\n");
                size = 3;
            }

            createBoard(board, size);
            
            FILE *file = fopen("game_log.txt", "w");
            if(file != NULL) {
                fprintf(file, "2 Player Tic Tac Toe - Board Size: %d\n\n", size);
            }

            printf("\nGame Started! Player 1: X, Player 2: O\n");

            while(!gameOver) {
                showBoard(board, size);

                if(file != NULL) {
                    fprintf(file, "Move %d - Player %c's turn:\n", moves, currentPlayer);
                    for(int i = 0; i < size; i++) {
                        for(int j = 0; j < size; j++) {
                            fprintf(file, "%c ", board[i][j]);
                        }
                        fprintf(file, "\n");
                    }
                    fprintf(file, "\n");
                }

                int row, col;
                printf("Player %c's turn: ", currentPlayer);
                scanf("%d %d", &row, &col);

                row--;
                col--;

                if(row < 0 || row >= size || col < 0 || col >= size) {
                    printf("Invalid position! Use numbers 1 to %d.\n", size);
                    continue;
                }

                if(board[row][col] != ' ') {
                    printf("That spot is already taken!\n");
                    continue;
                }

                board[row][col] = currentPlayer;
                moves++;

                if(checkWin(board, size, currentPlayer)) {
                    showBoard(board, size);
                    printf("*** Player %c WINS! ***\n", currentPlayer);
                    if(file != NULL) {
                        fprintf(file, "Player %c WINS!\n", currentPlayer);
                    }
                    gameOver = 1;
                }
                else if(checkDraw(board, size)) {
                    showBoard(board, size);
                    printf("*** It's a DRAW! ***\n");
                    if(file != NULL) {
                        fprintf(file, "Game ended in DRAW!\n");
                    }
                    gameOver = 1;
                }
                else {
                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                }
            }

            if(file != NULL) {
                fclose(file);
                printf("Game saved to 'game_log.txt'\n");
            }
        }
        else if(choice == 2) {
            // Player vs Computer mode
            char board[10][10];
            int size;
            int gameOver = 0;
            int moves = 0;

            printf("\n=== Player vs Computer ===\n");
            printf("Enter board size (3-10): ");
            scanf("%d", &size);

            if(size < 3 || size > 10) {
                printf("Invalid size! Using default size 3.\n");
                size = 3;
            }

            createBoard(board, size);
            
            FILE *file = fopen("game_log.txt", "w");
            if(file != NULL) {
                fprintf(file, "Player vs Computer - Board Size: %d\n\n", size);
            }

            printf("\nGame Started! Player: X, Computer: O\n");

            while(!gameOver) {
                showBoard(board, size);

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

                // Player's turn
                int row, col;
                printf("Your turn (X): ");
                scanf("%d %d", &row, &col);

                row--;
                col--;

                if(row < 0 || row >= size || col < 0 || col >= size) {
                    printf("Invalid position! Use numbers 1 to %d.\n", size);
                    continue;
                }

                if(board[row][col] != ' ') {
                    printf("That spot is already taken!\n");
                    continue;
                }

                board[row][col] = 'X';
                moves++;

                if(checkWin(board, size, 'X')) {
                    showBoard(board, size);
                    printf("*** YAY YOU WIN! ***\n");
                    if(file != NULL) {
                        fprintf(file, "Player (X) WINS!\n");
                    }
                    gameOver = 1;
                }
                else if(checkDraw(board, size)) {
                    showBoard(board, size);
                    printf("*** IT'S A DRAW! ***\n");
                    if(file != NULL) {
                        fprintf(file, "Game ended in a DRAW!\n");
                    }
                    gameOver = 1;
                }
                else {
                    // Computer's turn
                    printf("\nComputer's turn...\n");
                    computerMove(board, size);
                    moves++;

                    if(checkWin(board, size, 'O')) {
                        showBoard(board, size);
                        printf("*** OOPS COMPUTER WINS! ***\n");
                        if(file != NULL) {
                            fprintf(file, "Computer (O) WINS!\n");
                        }
                        gameOver = 1;
                    }
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

            if(file != NULL) {
                fclose(file);
                printf("Game saved to 'game_log.txt'\n");
            }
        }
        else if(choice == 3) {
            // 3 Player mode (fixed 3x3 board)
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

            FILE *logFile = fopen("game_log.txt", "w");
            if(logFile != NULL) {
                fprintf(logFile, "=== 3-Player Tic-Tac-Toe Game Log ===\n");
            }

            printf("\n=== 3-Player Tic-Tac-Toe ===\n");
            printf("Player 1: X, Player 2: O, Player 3: Z\n\n");

            // Choose player types
            for(int i = 0; i < 3; i++) {
                int type;
                printf("Player %d (%c):\n", i + 1, symbols[i]);
                printf("1. Human\n");
                printf("2. Computer\n");
                printf("Choose (1 or 2): ");
                scanf("%d", &type);
                playerTypes[i] = (type == 1) ? 0 : 1;
            }

            printf("\nGame starting!\n");
            displayBoard3x3(board);

            while(!gameOver) {
                printf("=== Player %d's Turn (%c) ===\n", currentPlayer + 1, symbols[currentPlayer]);

                if(playerTypes[currentPlayer] == 0) { // Human
                    int validMove = 0;
                    while(!validMove) {
                        printf("Enter your move (row and column, 1-3): ");
                        scanf("%d %d", &row, &col);
                        row--;
                        col--;

                        if(row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                            validMove = 1;
                        } else {
                            printf("Invalid move! Please choose an empty spot (1-3).\n");
                        }
                    }
                } else { // Computer
                    printf("Computer is thinking...\n");
                    computerMove3x3(board, &row, &col);
                    printf("Computer chooses position (%d,%d)\n", row + 1, col + 1);
                }

                board[row][col] = symbols[currentPlayer];
                
                if(logFile != NULL) {
                    fprintf(logFile, "Player %d (%c) moved to (%d,%d)\n", 
                            currentPlayer + 1, symbols[currentPlayer], row + 1, col + 1);
                }

                displayBoard3x3(board);

                if(checkWin3x3(board, symbols[currentPlayer])) {
                    printf("Player %d (%c) wins!\n", currentPlayer + 1, symbols[currentPlayer]);
                    if(logFile != NULL) {
                        fprintf(logFile, "Player %d (%c) WINS!\n", currentPlayer + 1, symbols[currentPlayer]);
                    }
                    gameOver = 1;
                }
                else if(isBoardFull3x3(board)) {
                    printf("It's a draw! The board is full.\n");
                    if(logFile != NULL) {
                        fprintf(logFile, "Game ended in a DRAW!\n");
                    }
                    gameOver = 1;
                }

                currentPlayer = (currentPlayer + 1) % 3;
            }

            if(logFile != NULL) {
                fclose(logFile);
                printf("Game saved to 'game_log.txt'\n");
            }
        }
        else if(choice == 4) {
            printf("Thanks for playing! Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice! Please choose 1-4.\n");
        }

        printf("\nPress Enter to continue...");
        getchar(); // Clear input buffer
        getchar(); // Wait for Enter key
    }

    return 0;
}
