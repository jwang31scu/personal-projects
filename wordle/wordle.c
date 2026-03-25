/*

File: wordle.c

Author: Jerry Wang

Description: driver program to solve a wordle puzzle

*/

int DEBUG_W = 0; //1 = debugging mode

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int load_allowed_word_list(char allowed_word_list[][6]);
int is_valid_word(char *input, char allowed[][6], int size);
int load_word_list(char word_list[][6]);
void evaluate_guess(char guess[6], char target[6], char status_array[5][7]);
int check_duplicate(char guess[6], char previous_guesses[][6], int count);
int check_win(char status_array[5][7]);

int main(){
    srand(time(NULL));
    
    printf("\n");

    char guess[6];
    char target[6];

    char allowed_words_array[16000][6];
    int allowed_size = load_allowed_word_list(allowed_words_array); // FIXED name

    char word_array[11000][6];
    int word_array_size = load_word_list(word_array);

    int random_index = rand() % word_array_size;
    strcpy(target, word_array[random_index]);

    if(DEBUG_W == 1) printf("The selected answer from potential-answers.txt is: %5s.\n", target);
    
    //GAME START
    int win_flag = 0;
    int guess_tracker = 1;
    char previous_guesses[6][6] = {0}; // safer initialization

    while (guess_tracker < 7){
        printf("\n");
        printf("You are on guess #%d.\n", guess_tracker);
        printf("Enter a 5 letter guess: \n");

        scanf("%5s", guess);

        if (is_valid_word(guess, allowed_words_array, allowed_size) != 1){
            printf("Invalid word. Try again.\n");
            continue;
        }

        if (check_duplicate(guess, previous_guesses, guess_tracker - 1) == 0){
            printf("Already guessed. Try again.\n");
            continue;
        }

        strcpy(previous_guesses[guess_tracker - 1], guess);

        //ACTUAL GAME LOGIC
        char status_array[5][7];
        evaluate_guess(guess, target, status_array);
            
        if (guess_tracker != 1){
            printf("Previous guesses: \n");
            for (int i = 0; i < guess_tracker - 1; i++) printf("%5s\n", previous_guesses[i]);
        }

        for (int i = 0; i < 5; i++) printf("    %c    ", guess[i]);
        printf("\n");

        for (int i = 0; i < 5; i++) printf("%-9s", status_array[i]);
        printf("\n");

        if (check_win(status_array) == 1){
            win_flag = 1;
            break;
        }

        guess_tracker++;
    }

    if (win_flag == 0){
        printf("You lost. Word was: %5s.\n", target);
        printf("\n");
    }
    else{
        printf("You won. Number of guesses: %d.\n", guess_tracker); 
        printf("\n");
    }

    return 0;
}