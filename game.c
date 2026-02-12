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
            if (map[i][j] == '#')
                wprintf(L"█");

            else if (i == pl.y && j == pl.x)
                wprintf(L"\x1b[34m▲\x1b[0m");

            else
                wprintf(L" ");
        }
        if (i < HEIGHT - 1)
            wprintf(L"\n");
    }
}



