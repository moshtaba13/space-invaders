#include <stdio.h>

#include "map.h"
#include "game.h"

void draw_map() 
{
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (map[i][j] == '#')
                printf("█");
            else
                printf(" ");
        }
        printf("\n");
    }
}

