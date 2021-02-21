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
#include "questions.h"
#include "players.h"
#include "jeopardy.h"
#include <time.h>

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);

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

    // Prompt for players names
    char *name = calloc(256, sizeof(char));
    player pl1;
    pl1.score = 0;
    printf("What is the first name?\n");
    scanf("%s", name);
    strcpy(pl1.name, name);
    players[0] =pl1;
    

    player pl2;
    pl2.score = 0;
    printf("What is the second name?\n");
    scanf("%s", name);
    strcpy(pl2.name, name);
    players[1] =pl2;

    player pl3;
    pl3.score = 0;
    printf("What is the third name?\n");
    scanf("%s", name);
    strcpy(pl3.name, name);
    players[2] =pl3;
    
    player pl4;
    pl4.score = 0;
    printf("What is the fourth name?\n");
    scanf("%s", name);
    strcpy(pl4.name, name);
    players[3] =pl4;
    
    free(name);
    
    // initialize each of the players in the array
    
    int counter = 0;
    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        srand(time(0));
        display_categories();

        char *name = calloc(256, sizeof(char));
        name = players[rand()%4].name;
        char *category = calloc(256, sizeof(char));
        int value;
        //Keeps asking for category and value till one that has not been chosen is picked
        ASK:
        while (true) {
            printf("What category do you want, %s?\n", name);
            scanf(" %s", category);
            if(strstr(category, "programming") || strstr(category, "algorithms") ||strstr(category, "databases")){
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
        char *answer = calloc(256, sizeof(char));
        printf("What is your answer?\n");
        scanf("%s", answer);

        if (valid_answer(category, value, answer))
        {//nate fix this shit mark question as complete
            printf("correct");
            update_score(players, NUM_PLAYERS, name, value);
        }
        free(answer);
        //free(name);
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
    printf("Next answer the question with \"yes\" or \"no\".\n\nWhen all questions have been answered the final results will be displayed.\n\n");
}
