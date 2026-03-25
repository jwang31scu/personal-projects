/*

File: wordle.c

Author: Jerry Wang

Description: driver program to solve a wordle puzzle

*/

int DEBUG_W = 1;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

int is_valid_word(char *input);
int load_word_list(char word_list[][6]);
void set_gray(char status_array[5][6]);
void evaluate_guess(char guess[6], char target[6], char status_array[5][6]);

int main(){
    srand(time(NULL));
    
    printf("\n");

    char guess[6];
    char target[6];

    char word_array[11000][6];
    int word_array_size = load_word_list(word_array);

    int random_index = rand() % word_array_size;
    strcpy(target, word_array[random_index]);

    if(DEBUG_W == 1) printf("The selected answer from potential-answers.txt is: %5s.\n", target);
    


    //GAME START
    int win_flag = 0;
    int guess_tracker = 1;
    while (guess_tracker < 7){
        printf("\n");
        printf("You are on guess #%d.\n", guess_tracker);
        printf("Enter a 5 letter guess: \n");

        scanf("%5s", guess);

        if (is_valid_word(guess) != 1){
            printf("Invalid word. Try again.\n");
            continue;
        }

        //ACTUAL GAME LOGIC

        char status_array[5][6];
        set_gray(status_array);
        evaluate_guess(guess, target, status_array);
            
        for (int i = 0; i < 5; i++) printf("   %c   ", guess[i]);
        printf("\n");
        for (int i = 0; i < 5; i++) printf("%s ", status_array[i]);
        printf("\n");






        guess_tracker++;
    }

    if (win_flag == 0){
        printf("You lost. Word was: %5s.\n", target);
    }
    else{
        printf("You won. Number of guesses: %s.\n", guess);
    }

    return 0;
}