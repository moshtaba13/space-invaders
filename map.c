
#include <stdio.h>

#include "map.h"

char map[HEIGHT][WIDTH];

void crat_map()
{
    for (int i = 0; i < HEIGHT; i++) 
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT-1 || j == 0 || j == WIDTH-1)
                map[i][j] = '#';
            else
                map[i][j] = ' ';
            
        }
}

