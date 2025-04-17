#include <stdio.h>
#include <stdlib.h>

// Constants for players
#define PLAYER_X 'X'
#define PLAYER_O 'O'
#define EMPTY ' '

// Function prototypes
void initializeBoard(char board[3][3]);
void printBoard(char board[3][3]);
int isMovesLeft(char board[3][3]);
int evaluateBoard(char board[3][3]);
int minimax(char board[3][3], int depth, int isMax);
void findBestMove(char board[3][3], int *bestRow, int *bestCol);
int checkWinner(char board[3][3]);
void playGame();

// Initialize the Tic-Tac-Toe board
void initializeBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = EMPTY;
        }
    }
}

// Print the Tic-Tac-Toe board
void printBoard(char board[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

// Check if there are moves left on the board
int isMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                return 1; // Moves are available
            }
        }
    }
    return 0; // No moves left
}

// Evaluate the board state
int evaluateBoard(char board[3][3]) {
    // Check rows for a win
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == PLAYER_X) return +10;
            else if (board[row][0] == PLAYER_O) return -10;
        }
    }

    // Check columns for a win
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == PLAYER_X) return +10;
            else if (board[0][col] == PLAYER_O) return -10;
        }
    }

    // Check diagonals for a win
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == PLAYER_X) return +10;
        else if (board[0][0] == PLAYER_O) return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == PLAYER_X) return +10;
        else if (board[0][2] == PLAYER_O) return -10;
    }

    // No winner
    return 0;
}

// Minimax algorithm to calculate the best move
int minimax(char board[3][3], int depth, int isMax) {
    int score = evaluateBoard(board);

    // If Maximizer (PLAYER_X) has won
    if (score == 10) return score - depth;

    // If Minimizer (PLAYER_O) has won
    if (score == -10) return score + depth;

    // If no moves left, it is a tie
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_X; // Make the move
                    best = (best > minimax(board, depth + 1, 0)) ? best : minimax(board, depth + 1, 0);
                    board[i][j] = EMPTY; // Undo the move
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_O; // Make the move
                    best = (best < minimax(board, depth + 1, 1)) ? best : minimax(board, depth + 1, 1);
                    board[i][j] = EMPTY; // Undo the move
                }
            }
        }
        return best;
    }
}

// Find the best possible move for the AI
void findBestMove(char board[3][3], int *bestRow, int *bestCol) {
    int bestVal = -1000;
    *bestRow = -1;
    *bestCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = PLAYER_X; // Try the move
                int moveVal = minimax(board, 0, 0);
                board[i][j] = EMPTY; // Undo the move

                if (moveVal > bestVal) {
                    *bestRow = i;
                    *bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
}

// Check for a winner or a draw
int checkWinner(char board[3][3]) {
    int score = evaluateBoard(board);
    if (score == 10) return 1;  // PLAYER_X wins
    if (score == -10) return -1; // PLAYER_O wins
    if (!isMovesLeft(board)) return 0; // Draw
    return 2; // Game ongoing
}

// Game loop
void playGame() {
    char board[3][3];
    initializeBoard(board);

    printf("Welcome to 3x3 Tic-Tac-Toe!\n");
    printBoard(board);

    int turn = 0; // 0 = PLAYER_X, 1 = PLAYER_O
    while (1) {
        int winner = checkWinner(board);
        if (winner == 1) {
            printf("PLAYER_X (AI) wins!\n");
            break;
        } else if (winner == -1) {
            printf("PLAYER_O wins!\n");
            break;
        } else if (winner == 0) {
            printf("It's a draw!\n");
            break;
        }

        if (turn == 0) {
            int bestRow, bestCol;
            findBestMove(board, &bestRow, &bestCol);
            board[bestRow][bestCol] = PLAYER_X;
            printf("PLAYER_X (AI) makes a move:\n");
        } else {
            int row, col;
            printf("PLAYER_O, enter your move (row and column): ");
            scanf("%d %d", &row, &col);
            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == EMPTY) {
                board[row][col] = PLAYER_O;
            } else {
                printf("Invalid move. Try again.\n");
                continue;
            }
        }

        printBoard(board);
        turn = 1 - turn;
    }
}

// Main function
int main() {
    playGame();
    return 0;
}
