#include <stdio.h>
#include <conio.h>

#include "elements.h"
#include "map.h"

void keyboard(player *one) {
    if (kbhit()) {

        int nexe_x = one->x;
        int nexe_y = one->y;

        switch (getch())
        {
        case 'w':
            nexe_y--;
            break;

        case 's':
            nexe_y++;
            break;
        
        case 'd':
            nexe_x++;
            break;
        
        case 'a':
            nexe_x--;
            break;
        case ' ':
            break;
        
        default:
            break;
        }

        if (map[nexe_y][nexe_x] != '#') {
            one->x = nexe_x ;
            one->y = nexe_y;
        }
    }
}


