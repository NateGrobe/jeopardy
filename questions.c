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
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    question a1;
    strcpy(a1.category, "algorithms");
    strcpy(a1.question, "Can a binary heap be build in O(n)?");
    strcpy(a1.answer, "yes");
    a1.value = 100;
    a1.answered = false;
    questions[0] = a1;

    question a2;
    strcpy(a2.category, "algorithms");
    strcpy(a2.question, "Is the time complexity of heap sort O(n^2)?");
    strcpy(a2.answer, "no");
    a2.value = 200;
    a2.answered = false;
    questions[3] = a2;

    question a3;
    strcpy(a3.category, "algorithms");
    strcpy(a3.question, "Is A* a greedy algorithm?");
    strcpy(a3.answer, "yes");
    a3.value = 300;
    a3.answered = false;
    questions[6] = a3;

    question a4;
    strcpy(a4.category, "algorithms");
    strcpy(a4.question, "Does the regularity condition hold for T(n) = 2T(n/2) + n^n");
    strcpy(a4.answer, "yes");
    a4.value = 400;
    a4.answered = false;
    questions[9] = a4;

    question p1;
    strcpy(p1.category, "programming");
    strcpy(p1.question, "Does a boolean use 2 bytes to store its value in C?");
    strcpy(p1.answer, "no");
    p1.value = 100;
    p1.answered = false;
    questions[1] = p1;

    question p2;
    strcpy(p2.category, "programming");
    strcpy(p2.question, "Is C an object oriented programming language?");
    strcpy(p2.answer, "no");
    p2.value = 200;
    p2.answered = false;
    questions[4] = p2;

    question p3;
    strcpy(p3.category, "programming");
    strcpy(p3.question, "Does the free() function deallocate memory?");
    strcpy(p3.answer, "yes");
    p3.value = 300;
    p3.answered = false;
    questions[7] = p3;

    question p4;
    strcpy(p4.category, "programming");
    strcpy(p4.question, "Is C a memory safe language?");
    strcpy(p4.answer, "no");
    p4.value = 400;
    p4.answered = false;
    questions[10] = p4;

    question d1;
    strcpy(d1.category, "databases");
    strcpy(d1.question, "Does the * operator refer to all columns in a table?");
    strcpy(d1.answer, "yes");
    d1.value = 100;
    d1.answered = false;
    questions[2] = d1;

    question d2;
    strcpy(d2.category, "databases");
    strcpy(d2.question, "Is MongoDB a no SQL database?");
    strcpy(d2.answer, "yes");
    d2.value = 200;
    d2.answered = false;
    questions[5] = d2;

    question d3;
    strcpy(d3.category, "databases");
    strcpy(d3.question, "Does SQL stand for Simple Query Language?");
    strcpy(d3.answer, "no");
    d3.value = 300;
    d3.answered = false;
    questions[8] = d3;

    question d4;
    strcpy(d4.category, "databases");
    strcpy(d4.question, "Does MongoDB return data in JSON?");
    strcpy(d4.answer, "yes");
    d4.value = 400;
    d4.answered = false;
    questions[11] = d4;
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    printf("Algorithms   Programming   Databases\n");
    for(int i = 0; i < NUM_QUESTIONS; i += 3) {
        printf("   %d           %d          %d\n", questions[i].value, questions[i+1].value, questions[i+2].value);
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    for(int i = 0; i < NUM_QUESTIONS; i++) {
        question q = questions[i];
        if(strstr(category, q.category) && q.value == value) {
            printf("%d: %s\n> ", q.value, q.question);
        }
    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    for(int i = 0; i < NUM_QUESTIONS; i++) {
        question q = questions[i];
        if(strstr(category, q.category) && q.value == value) {
            if(strstr(q.answer, answer)) {
                q.answered = true;
                return true;
            }
        }
    }
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    for(int i = 0; i < NUM_QUESTIONS; i++) {
        question q = questions[i];
        if(strstr(category, q.category) && q.value == value) {
            return q.answered; 
        }
    }
    // return false;
}
