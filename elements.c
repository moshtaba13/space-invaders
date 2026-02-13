#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

#include "elements.h"
#include "map.h"

enemy enemies[MAX_ENEMIES];

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

void spawn_enemy() {

    double spawn, random, shooter, type;
    int max, enemy = 0, c, check = 0; 

    spawn = 0.02 + (0.0025 * pl.level);
    if (spawn > 0.4) 
        spawn = 0.4;

    random = (double)rand() / RAND_MAX;

    if (random < spawn) {
        
        max = (int)(3 * sqrt(pl.level));

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

void update_enemies() {
    double p = 0, random;

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

                if ((abs(dx) + abs(dy)) != 0) {
                    p = (double)abs(dx) / (abs(dx) + abs(dy));
                }
                
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
            }
        }
    }
}