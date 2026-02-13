#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#include <time.h>

#include "menu.h"
#include "map.h"
#include "game.h"
#include "elements.h"

#ifndef _U16TEXT
#define _U16TEXT 0x00020000
#endif


int main() {
    srand(time(NULL));
    setup_console();
    hide_cursor(); 
    _setmode(_fileno(stdout), _U16TEXT);

    system("cls");
    //menu();
    start();
    crat_map();
    while (1)
    {
        set_cursor_position(0, 0);
        spawn_enemy();
        update_enemies();
        update_bullets();
        draw_map();
        keyboard(&pl);
        Sleep(50);
    }
    
}