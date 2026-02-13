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
    menu();
    menu_game();
    start();
    crat_map();
    while (1)
    {
        set_cursor_position(0, 0);
        if (!gameover) {
            system("cls");
            wprintf(L"\n\n GAME OVER");
            update_leaderboard(current_user, pl.level, pl.coins);
            Sleep(5000);
            reset();
            menu_game();
        }
        spawn_enemy();
        update_bullets();
        update_enemies();
        update_enemy_bullets();
        draw_map();
        wprintf(L"\n [hp: %d]  [coins: %d]  [level: %d]", pl.health, pl.coins, pl.level);
        keyboard(&pl);
        Sleep(50);
    }
    
        
}