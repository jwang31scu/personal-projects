/*

File: wordle.c

Author: Jerry Wang

Description: driver program to solve a wordle puzzle

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

//functions from solver.c --> compile as gcc wordle.c solver.c -o wordle

int isValidWord(char *input);

int main(){
    srand(time(NULL));
    
    char guess[6];
    char target[6];

    //choosing the target word
    char word_list[11000][6];
    int word_list_index = 0;
    FILE *fp = fopen("potential-answers.txt", "r");
    assert(fp != NULL);

    //adding the words in the file into an array
    while(fscanf(fp, "%5s", word_list[word_list_index]) == 1){
        word_list_index++;
    }
    
    //generating a random number from 0 to word_list_index to use for target

    int random_index = rand() % word_list_index;
    strcpy(target, word_list[random_index]);
    
    int win_flag = 0;

    //taking in the user's inputs via a while loop
    int guess_tracker = 1;
    while (guess_tracker < 7){
        printf("You are on guess #%d.\n", guess_tracker);
        printf("Enter a 5 letter guess: \n");

        scanf("%5s", guess);

        if (isValidWord(guess) != 1){
            printf("Invalid word. Try again.\n");
            continue;
        }




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