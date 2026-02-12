#ifndef ELEMENTS_H
#define ELEMENTS_H

typedef struct {
    int x;
    int y;
    int health;
    int max_hp;
    int coins;
    int level;
    int damage;
    int max_bullets;
}player;

typedef struct {
    int x;
    int y;
    int alive;
}bullet;


void keyboard(player * );

extern player pl;

#endif
