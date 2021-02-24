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
#include "players.h"

// Returns true if the player name matches one of the existing players
bool player_exists(player *players, int num_players, char *name)
{
    for(int i = 0; i < num_players; i++) {
        player p = players[i];
        if(strstr(p.name, name)) {
            return true;
        }
    }
    return false;
}

// Go through the list of players and update the score for the 
// player given their name
<<<<<<< HEAD
int update_score(player *players, int num_players, char *name, int score)
=======
void update_score(player *players, int num_players, char *name, int score)//TODO
>>>>>>> 2e45c9a94995f3f612c849bbef6a11b8c0047db5
{
    for(int i = 0; i < num_players; i++) {
        player p = players[i];
        if(strstr(p.name, name)) {
            p.score += score;
            players[i] = p;
            // return p.score;
        }
    }
}
