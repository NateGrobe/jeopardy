/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U
 *
 * Copyright (C) 2021, Nate Grobe, Cole Kahkonen, Kavan Chandra, Krystian Rusin
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);

void str_lower_case(char *str);

void display_instructions();

int main()
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    display_instructions();
    initialize_game();

    // Prompt for players names and append them to an array of players
    for(int i = 0; i < NUM_PLAYERS; i++) {
        char *name = calloc(256, sizeof(char));
        player p;
        p.score = 0;
        printf("Enter player %d's name: ", i+1);
        scanf("%s", name);
        strcpy(p.name, name);
        players[i] = p;
        free(name);
    }
    
    // initialize each of the players in the array
    
    int counter = 0;
    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {

        char *name = calloc(256, sizeof(char));
        char *category = calloc(256, sizeof(char));

        while (true) {
            printf("Enter the current player: ");
            scanf("%s", name);
            if(player_exists(players, NUM_PLAYERS, name)) {
                break;
            }
            printf("There is no player named %s", name);
        }

        display_categories();

        int value;
        //Keeps asking for category and value till one that has not been chosen is picked
        ASK:
        while (true) {
            printf("What category do you want, %s?\n", name);
            scanf(" %s", category);
            str_lower_case(category);
            if (strstr(category, "programming") || strstr(category, "algorithms") ||strstr(category, "databases")){
             break;
            }
        }
        while (true){
            printf("What value do you want, %s?\n", name);
            scanf(" %d", &value);
            if(value == 100|| value == 200 || value == 300 || value == 400){
                break;
            }
        }
    

        if(already_answered(category, value) == true)
        {
            printf("That question has been answered\n");
            goto ASK;
        }
        //shows question and checks for the answer
        display_question(category, value);

        char *answer = calloc(BUFFER_LEN, sizeof(char));
        char *cleaned_answer = calloc(BUFFER_LEN, sizeof(char));

        while (true) {
            char **tokens = calloc(BUFFER_LEN, sizeof(char*));
            scanf("\n%[^\n]c", answer);
            str_lower_case(answer);
            tokenize(answer, tokens);
            if ((strstr(tokens[0], "who") || strstr(tokens[0], "what")) && strstr(tokens[1], "is")) {
                if(strstr(tokens[2], "yes") || strstr(tokens[2], "no")) {
                    cleaned_answer = tokens[2];
                    break;
                } else {
                    printf("Please answer using yes or no!\n");
                }
            } else {
                printf("Please answer using \"who is\" or \"what is\"!\n");
            }
        }

        // print if the answer is correct
        if (valid_answer(category, value, cleaned_answer))
        {
            update_score(players, NUM_PLAYERS, name, value);
            for(int i = 0; i < NUM_PLAYERS; i++) {
                player p = players[i];
                if(strstr(p.name, name)) {
                    printf("correct! %s's score is now: %d \n", name, p.score);
                }
            }
        }else {
            for(int i = 0; i < NUM_PLAYERS; i++) {
                player p = players[i];
                if(strstr(p.name, name)) {
                    printf("incorrect, %s's score is still: %d \n", name, p.score);
                }
            }
        }

        free(answer);
        counter++;

        // Call functions from the questions and players source files
        // Execute the game until all questions are answered
        // Display the final results and exit
        if(counter >= 12){
            //show_results(players, NUM_PLAYERS);
            break;
        }

    }
    return EXIT_SUCCESS;
}

// write complete instructions here
void display_instructions() {
    printf("Instructions:\n");
    printf("Firstly, enter all 4 players names.\n\nThen enter the category and dollar amount of question.\n\n");
    printf("Next answer the question with \"who is yes\" or \"who is no\". \"What is\" is also accepted.");
    printf("\n\nWhen all questions have been answered the final results will be displayed.\n\n");
}

// converts a string to lower case
void str_lower_case(char *str) {
    for(int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

// splits input into tokens and appends them to an array
void tokenize(char *input, char **tokens) {
    char *token = strtok(input, " ");
    int c = 0;

    while(token != NULL) {
        tokens[c++] = token;
        token = strtok(NULL, " ");
    }
}