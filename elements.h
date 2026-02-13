#ifndef ELEMENTS_H
#define ELEMENTS_H

#define MAX_ENEMIES 100

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

typedef struct {
    int x , y;
    int type;
    int health;
    int max_hp;
    int damage;
    int alive;
    int timer;
    int action;
}enemy;

void keyboard(player * );
void spawn_enemy(void);
void update_enemies(void);

extern player pl;
extern enemy enemies[MAX_ENEMIES];

#endif
