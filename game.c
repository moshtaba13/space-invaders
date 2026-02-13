#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>

#include "map.h"
#include "game.h"
#include "elements.h"

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

player pl;
int leaderboard_count = 0; 

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

void reset() {
    pl.x = WIDTH / 2;
    pl.y = HEIGHT - 5;
    spawned = 0;
    killed = 0;

    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].alive = 0;
    }
    for (int i = 0; i < MAX_BULLETS; i++)
        bullets[i].active = 0;

    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
        enemy_bullets[i].active = 0;
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


void store() {
    while (1) {
        system("cls");
        
        wprintf(L"\n\n ===========store===========\n");
        wprintf(L"   Coins: %d $\n\n", pl.coins);
        wprintf(L"   1. Health [+1]     Price: 25 $\n");
        wprintf(L"   2. Damage [+1]     Price: 35 $\n");
        wprintf(L"   3. Max Bullets [+1]   Price: 80 $\n");
        wprintf(L"   4. Exit\n\n");
        
        wprintf(L"(Please enter from 1 to 4):");
        
        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            if (pl.coins >= 25) {
                pl.coins -= 25;
                pl.health++;
                wprintf(L"\n   its done!! \n(Health: %d)\n", pl.health);
            } 
            else 
                wprintf(L"\n your coins is not enough!!\n");
            
        }
        else if (choice == 2) {
            if (pl.coins >= 40) {
                pl.coins -= 40;
                pl.damage++;
                wprintf(L"\n   its done! \n(Damage: %d)\n", pl.damage);
            } 
            else 
                wprintf(L"\n  your coins is not enough! \n");
            
        }
        else if (choice == 3) {
            if (pl.coins >= 80) {
                pl.coins -= 80;
                pl.max_bullets++;
                wprintf(L"\n  its done! (Max Bullets: %d)\n", pl.max_bullets);
            } 
            else 
                wprintf(L"\n  your coins is not enough!\n");
            
        }
        else if (choice == 4) {
            return;
        }
        
        Sleep(5000); 
    }

    printf("\n   Press any key to return...");
    getch();
}

void update_leaderboard(char *user, int level, int coins) {

    strcpy(leaderboard[leaderboard_count].username, user);
    leaderboard[leaderboard_count].level = level;
    leaderboard[leaderboard_count].coins = coins;
    
    leaderboard_count++;

    for (int i = 0; i < leaderboard_count - 1; i++) {
        for (int j = 0; j < leaderboard_count - i - 1; j++) {
            if (leaderboard[j].coins < leaderboard[j + 1].coins) {

                Leaderboard temp = leaderboard[j];
                leaderboard[j] = leaderboard[j + 1];
                leaderboard[j + 1] = temp;
            }
        }
    }

    if (leaderboard_count > MAX_LEADERBOARD) {
        leaderboard_count = MAX_LEADERBOARD;
    }
}

void show_leaderboard() {
    system("cls");
    wprintf(L"\n   ==========================================\n");
    wprintf(L"       LEADERBOARD (TOP PLAYERS)    \n");
    wprintf(L"   ==========================================\n\n");

        wprintf(L"   Rank  Username            Level    Coins\n");
        wprintf(L"   ----  ------------------  -----    -----\n");

        for (int i = 0; i < leaderboard_count; i++) {
            if (i == 0)
                wprintf(L"\x1b[33m");      
            else if (i == 1)
                wprintf(L"\x1b[37m");
            else if (i == 2)
                wprintf(L"\x1b[31m"); 
            else 
                wprintf(L"\x1b[0m");              

            wprintf(L"   #%d %s %d %d\n", i + 1, leaderboard[i].username, leaderboard[i].level, leaderboard[i].coins);
            wprintf(L"\x1b[0m");
        }
    

    wprintf(L"\n   ==========================================\n");
    wprintf(L"   Press any key to return...");
    getch();
}