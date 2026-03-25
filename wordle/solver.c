/*

File: solver.c

Author: Jerry Wang

Description: functions for wordle.c

*/

int DEBUG_S = 1;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int is_valid_word(char *input);
int load_word_list(char word_list[][6]);
void set_gray(char status_array[5][6]);
void evaluate_guess(char guess[6], char target[6], char status_array[5][6]);

int is_valid_word(char *input){
    FILE *fp = fopen("allowed-words.txt", "r");
    assert(fp != NULL);

    int flag = 0;

    //checking length validity
    int length = strlen(input);
    if (length != 5){
        flag = 0;
        fclose(fp);
        return 0;
    }

    char buffer[6];
    while(fscanf(fp, "%5s", buffer) == 1){
        if (strcmp(buffer, input) == 0){
            flag = 1;
            return flag;
        }
    }

    fclose(fp);
    return flag;
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

void set_gray(char status_array[5][6]){
    for (int i = 0; i < 5; i++) strcpy(status_array[i], "grey");
}

void evaluate_guess(char guess[6], char target[6], char status_array[5][6]){
    int used[5] = {0, 0, 0, 0, 0}; //0 = unused letter

    //checking greens
    for (int i = 0; i < 5; i++){
        if (guess[i] == target[i]){
            strcpy(status_array[i], "green");
            used[i] = 1;
        }
    }

    for (int i = 0; i < 5; i++){
        if (strcmp(status_array[i], "green") == 0) continue;

        for (int j = 0; j < 5; j++){
            if ((used[i] != 1) && guess[i] == target[j]){
                strcpy(status_array[i], "yellow");
                used[j] = 1;
                break;
            }

        }
    }
}

/*
function: 

description: 
*/

