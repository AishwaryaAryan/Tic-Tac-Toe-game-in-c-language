#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];
void resetBoard(), printBoard(), move(char);
char checkWinner();
int freeSpaces();

int main() {
    char winner, response;
    do {
        resetBoard();
        while ((winner = checkWinner()) == '\0' && freeSpaces()) {
            printBoard();
            move('X'); 
            if ((winner = checkWinner()) != '\0' || !freeSpaces()) break;
            move('O'); 
        }
        printBoard();
        printf(winner ? (winner == 'X' ? "You win!\n" : "You lose!\n") : "It's a draw!\n");
        printf("Play again? (Y/N): ");
        scanf(" %c", &response);
    } while (response == 'Y' || response == 'y');
}

void resetBoard() { for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) board[i][j] = ' '; }

void printBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) printf(" %c %s", board[i][j], j < 2 ? "|" : "");
        if (i < 2) printf("\n---|---|---\n");
    }
    printf("\n");
}

int freeSpaces() {
    int spaces = 0;
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) if (board[i][j] == ' ') spaces++;
    return spaces;
}

void move(char symbol) {
    int x, y;
    if (symbol == 'X') {
        do {
            printf("Enter row and column (1-3): ");
            scanf("%d %d", &x, &y);
            x--; y--;
        } while (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ');
    } else {
        srand(time(0));
        do { x = rand() % 3; y = rand() % 3; } while (board[x][y] != ' ');
    }
    board[x][y] = symbol;
}

char checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') 
        return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') 
        return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') 
    return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
    return board[0][2];
    return '\0';
}
