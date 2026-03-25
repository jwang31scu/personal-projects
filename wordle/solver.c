/*

File: solver.c

Author: Jerry Wang

Description: functions for wordle.c

*/

int DEBUG_S = 0;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int load_allowed_word_list(char allowed_word_list[][6]);
int is_valid_word(char *input, char allowed[][6], int size);
int load_word_list(char word_list[][6]);
void evaluate_guess(char guess[6], char target[6], char status_array[5][7]);
int check_duplicate(char guess[6], char previous_guesses[][6], int count);
int check_win(char status_array[5][7]);

int load_allowed_word_list(char allowed_word_list[][6]){
    FILE *fp = fopen("allowed-words.txt", "r");
    assert(fp != NULL);

    int index = 0;

    while(fscanf(fp, "%5s", allowed_word_list[index]) == 1){
        index++;
    }

    fclose(fp);

    if(DEBUG_S == 1){
        printf("First word from allowed-words.txt: %5s.\n", allowed_word_list[0]); // FIXED label
        printf("Last word from allowed-words.txt: %5s.\n", allowed_word_list[index - 1]);
    }

    return index;
}

int is_valid_word(char *input, char allowed[][6], int size){
    if (strlen(input) != 5) return 0;

    for (int i = 0; i < size; i++){
        if (strcmp(input, allowed[i]) == 0){
            return 1;
        }
    }

    return 0;
}

int load_word_list(char word_list[][6]){
    FILE *fp = fopen("potential-answers.txt", "r");
    assert(fp != NULL);

    int index = 0;

    while(fscanf(fp, "%5s", word_list[index]) == 1){
        index++;
    }

    fclose(fp);

    if(DEBUG_S == 1){
        printf("First word from potential-answers.txt: %5s.\n", word_list[0]);
        printf("Last word from potential-answers.txt: %5s.\n", word_list[index - 1]);
    }

    return index;
}

void evaluate_guess(char guess[6], char target[6], char status_array[5][7]){
    int used[5] = {0, 0, 0, 0, 0};

    for (int i = 0; i < 5; i++){
        strcpy(status_array[i], "grey");
    }

    // greens
    for (int i = 0; i < 5; i++){
        if (guess[i] == target[i]){
            strcpy(status_array[i], "green");
            used[i] = 1;
        }
    }

    // yellows
    for (int i = 0; i < 5; i++){
        if (strcmp(status_array[i], "green") == 0) continue;

        for (int j = 0; j < 5; j++){
            if ((used[j] != 1) && guess[i] == target[j]){
                strcpy(status_array[i], "yellow");
                used[j] = 1;
                break;
            }
        }
    }

    if (DEBUG_S == 1) printf("DEBUG target: %s, guess: %s\n", target, guess);

    for (int i = 0; i < 5; i++){
        printf("[%s]", status_array[i]);
    }
    printf("\n");
}

int check_duplicate(char guess[6], char previous_guesses[][6], int count){
    for (int i = 0; i < count; i++){
        if (strcmp(guess, previous_guesses[i]) == 0) return 0;
    }
    return 1;
}

int check_win(char status_array[5][7]){
    for (int i = 0; i < 5; i++){
        if (strcmp(status_array[i], "green") != 0) return 0;
    }
    return 1;
}