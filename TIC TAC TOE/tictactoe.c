#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>


char board[9];
const char player = 'X';
const char megatron = 'O';

void intructions() {
    printf("\nYou are going againts MEGATRON!\n");
    printf("You will need to enter a number to put your X\n");
    printf(" 1 | 2 | 3 \n");
    printf("---|---|---\n");
    printf(" 4 | 5 | 6 \n");
    printf("---|---|---\n");
    printf(" 7 | 8 | 9 \n\n");
}

void reset() {
    for (int i = 0; i < 9; i++) board[i] = ' ';
}

int avaible_places() {
    int count = 9;
    for (int i = 0; i < 9; i++) {
        if (board[i] != ' ') count--;
    } 
    return count;
}

void building_board() {
    printf(" %c | %c | %c \n", board[0], board[1], board[2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[3], board[4], board[5]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[6], board[7], board[8]);
}

void print_winner(char winner) {
    if (winner == 'X') {
        printf("PLAYER WON THE GAME\n");
    } else if (winner == 'O') {
        printf("MEGATRON WON THE GAME\n");
    } else {
        printf("TIE GAME\n");
    }
}

void player_move() {
    int input;
    do {
        printf("\nEnter a number: ");
        scanf("%d", &input);
        input--;
        if (board[input] != ' ') {
            printf("Invalid Space");
        } else {
            board[input] = player;
            break;
        }
    } while (board[input] != ' ');
    
}

void megatron_move() {
    srand(time(0));
    int x;

    if (avaible_places() > 0) {
        do {
            x = rand() % 9;
        } while (board[x] != ' ');
        board[x] = megatron;
    }  else {
        print_winner(' ');
    }
}

char checking_winner() {
    // checking each rows
    for (int i = 0; i < 9; i+=3) {
        if (board[i] == board[i+1] && board[i] == board[i+2] && board[i] != ' ') return board[i];
    }

    // checking diags
    if (board[0] == board[4] && board[0] == board[8] && board[0] != ' ') return board[0];
    if (board[2] == board[4] && board[2] == board[6] && board[2] != ' ') return board[2];


    // checking columns
    for (int i = 0; i < 3; i++) {
        if (board[i] == board[i+3] && board[i] == board[i+6] && board[i] != ' ') return board[i];
    }
    return ' ';
}



int main() {
  
    char winner = ' ';
    char again;
    do {
        winner = ' ';
        again = ' ';
        intructions();
        reset();


        while (winner == ' ' && 0 != avaible_places()) { 
            building_board();
            player_move();
            megatron_move();
            winner = checking_winner();
            if (winner != ' ' || avaible_places() == 0) {
                break;
            }
        }
        building_board();
        print_winner(winner);
        printf("Want to play again? (Y/N) : ");
        scanf(" %c", &again);
        again = toupper(again);
    } while (again == 'Y');

    
    return 0;
}