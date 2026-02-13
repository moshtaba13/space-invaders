#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

#include "elements.h"
#include "map.h"
#include "game.h"

enemy enemies[MAX_ENEMIES];
bullet bullets[MAX_BULLETS];
bullet enemy_bullets[MAX_ENEMY_BULLETS];

int bullet_index = 0; 
int spawned = 0, killed = 0, max_enemy = 0, gameover = 0;

void keyboard(player *one) {
    if (kbhit()) {

        int next_x = one->x;
        int next_y = one->y;

        switch (getch())
        {
        case 'w':
            next_y--;
            break;

        case 's':
            next_y++;
            break;
        
        case 'd':
            next_x++;
            break;
        
        case 'a':
            next_x--;
            break;
        case ' ':
            shoot();
            break;
        
        default:
            break;
        }

        if (map[next_y][next_x] != '#') {
            one->x = next_x ;
            one->y = next_y;
        }
    }
}

void spawn_enemy() {

    double spawn, random, shooter, type;
    int max, enemy = 0, c, check = 0; 

    if (spawned >= max_enemy) 
        return;

    spawn = 0.02 + (0.0025 * pl.level);
    if (spawn > 0.4) 
        spawn = 0.4;

    random = (double)rand() / RAND_MAX;

    if (random < spawn) {
        
        max = (int)(3 * sqrt(pl.level));
        max_enemy = max;

        for(int i = 0; i <  MAX_ENEMIES ;i++)
            if(enemies[i].alive)
                enemy++;

        if (enemy >= max) 
            return;

        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemies[i].alive != 1) {
                c = (rand() % (WIDTH - 2)) + 1;
            
                for(int j = 0; j < MAX_ENEMIES; j++) 
                    if(enemies[j].alive && enemies[j].x == c && enemies[j].y == 1) 
                        check = 1;
                
                if (check) 
                    return;

                spawned++;

                enemies[i].alive = 1;
                enemies[i].x = c;
                enemies[i].y = 1;
                enemies[i].timer = 0;

                shooter = 0.01 * pl.level;
                if (shooter > 0.5) 
                    shooter = 0.5;

                type = (double)rand() / RAND_MAX;

                if (type < shooter) {
                    enemies[i].type = 2;
                    enemies[i].max_hp = 2 + (pl.level / 20);
                    enemies[i].damage = 1 + (pl.level / 10);
                    enemies[i].action = 10; 
                } 
                else {
                    enemies[i].type = 1;
                    enemies[i].max_hp = 2 + (pl.level / 10);
                    enemies[i].damage = 1 + (pl.level / 20);
                    enemies[i].action = 8;
                }
                enemies[i].health = enemies[i].max_hp;
                break;
            }
        }
    }
}

void shoot() {
    bullets[bullet_index].x = pl.x;
    bullets[bullet_index].y = pl.y - 1;
    bullets[bullet_index].active = 1;   

    bullet_index++;
    if (bullet_index >= MAX_BULLETS) {
        bullet_index = 0;
    }
}

void update_enemies() {
    double p = 0, random;
    double fire_chance = 0.05;

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].alive != 1) 
            continue;

        enemies[i].timer++;

        if (enemies[i].timer >= enemies[i].action) {
            enemies[i].timer = 0;
            int dx = pl.x - enemies[i].x; 
            int dy = pl.y - enemies[i].y;
            int next_x = enemies[i].x;
            int next_y = enemies[i].y;
        
            if (enemies[i].type == 1) {

                if (abs(dx) <= 1 && abs(dy) <= 1) {
                    pl.health -= enemies[i].damage;
                    if (pl.health <= 0) 
                        gameover = 1;
                }

                else {
                    if ((abs(dx) + abs(dy)) != 0) 
                        p = (double)abs(dx) / (abs(dx) + abs(dy));
                
                    random = (double)rand() / RAND_MAX;

                    if (random < p) {
                        if (dx > 0)
                            next_x++;     
                        else if (dx < 0) 
                            next_x--;
                    } 
                
                    else {
                        if (dy > 0)
                            next_y++;      
                        else if (dy < 0)
                            next_y--; 
                    }
                }

                if (map[next_y][next_x] != '#') {
                    enemies[i].x = next_x;
                    enemies[i].y = next_y;
                }
            }
            
            else if (enemies[i].type == 2) {
                
                if (abs(dy) > (2.0 * HEIGHT / 3.0))
                    next_y++;
                
                else if (abs(dy) < (HEIGHT / 4.0)) 
                    next_y--;
                
                else {
                    if (dx > 0)
                        next_x++;    
                    else if (dx < 0)   
                        next_x--; 
                }

                if (map[next_y][next_x] != '#' ) {
                    enemies[i].x = next_x;
                    enemies[i].y = next_y;
                }
 
                if (enemies[i].x == pl.x)
                    fire_chance = 0.30;

                if ((double)rand() / RAND_MAX < fire_chance) {
                    for (int b = 0; b < MAX_ENEMY_BULLETS; b++) {
                        if (enemy_bullets[b].active != 1) {
                            enemy_bullets[b].active = 1;
                            enemy_bullets[b].x = enemies[i].x;
                            enemy_bullets[b].y = enemies[i].y + 1;
                            break; 
                        }
                    }
                }
            }
        }
    }
}

void update_bullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].y--; 

            if (map[bullets[i].y][bullets[i].x] == '#') {
                bullets[i].active = 0;
                continue;
            }

            for (int j = 0; j < MAX_ENEMIES; j++) {
                if (enemies[j].alive && enemies[j].x == bullets[i].x && enemies[j].y == bullets[i].y) {
                    enemies[j].health -= pl.damage; 
                    bullets[i].active = 0;

                    if (enemies[j].health <= 0) {
                        enemies[j].alive = 0;
                        killed++;
                        if (enemies[i].type == 1) 
                            pl.coins += 3;
                        else 
                            pl.coins += 5;
                        
                        if (killed >= max_enemy) {
                        system("cls");
                        wprintf(L"\n\n\n\t\t LEVEL %d COMPLETED! \n", pl.level);
                        wprintf(L"\t\t Get Ready for Level %d... \n", pl.level + 1);
                        Sleep(5000);

                        pl.level++;
                        reset();   
                        return;  
                        }   
                    }
                    break;
                }
            }
        }
    }
}


void update_enemy_bullets() {
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
        if (enemy_bullets[i].active) {
            enemy_bullets[i].y++; 

            if (map[enemy_bullets[i].y][enemy_bullets[i].x] == '#') {
                enemy_bullets[i].active = 0; 
                continue;
            }

            if (enemy_bullets[i].x == pl.x && enemy_bullets[i].y == pl.y) {
                pl.health--;
                enemy_bullets[i].active = 0;

                if (pl.health <= 0) {
                    gameover = 1;
                }

            }
        }
    }
}