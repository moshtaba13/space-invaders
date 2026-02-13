#include <stdio.h>
#include <windows.h>

#include "map.h"
#include "game.h"
#include "elements.h"

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

player pl;

void hide_cursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE; 
    SetConsoleCursorInfo(consoleHandle, &info);
}


void setup_console() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void start()
{
    pl.x = WIDTH / 2;
    pl.y = HEIGHT - 5;
    pl.damage = 1;
    pl.health = 5;
    pl.max_hp = 5;
    pl.coins = 0;
    pl.level = 1;
    pl.max_bullets = 3;
}

void set_cursor_position(int x, int y) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, pos);
}

void draw_map() 
{
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {

            if (i == pl.y && j == pl.x) {
                wprintf(L"\x1b[34m▲\x1b[0m");
                continue;
            }

            int flag = 0;
            for (int k = 0; k < MAX_ENEMIES; k++) {
                if (enemies[k].alive && enemies[k].x == j && enemies[k].y == i) {
                    if (enemies[k].type == 1) 
                        wprintf(L"\x1b[31m■\x1b[0m");
                    else 
                        wprintf(L"\x1b[33m▼\x1b[0m"); 
                    flag = 1;
                    break;
                }
            }

            if (flag)
                continue;

            int flag1 = 0;
            for (int k = 0; k < MAX_ENEMY_BULLETS; k++) {
                if (enemy_bullets[k].active && enemy_bullets[k].x == j && enemy_bullets[k].y == i) {
                    wprintf(L"\x1b[31m|\x1b[0m"); 
                    flag1 = 1;
                    break;
                }
            }
            if (flag1)
                continue;

            int flag2 = 0;
            for (int k = 0; k < MAX_BULLETS; k++) {
                if (bullets[k].active && bullets[k].x == j && bullets[k].y == i) {
                    wprintf(L"\x1b[32m|\x1b[0m");
                    flag2 = 1;
                    break;
                }
            }

            if (flag2)
                continue;

            if (map[i][j] == '#')
                wprintf(L"█");

            else
                wprintf(L" ");
        }
        if (i < HEIGHT - 1)
            wprintf(L"\n");
    }
}


