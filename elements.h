#ifndef ELEMENTS_H
#define ELEMENTS_H

#define MAX_ENEMIES 100
#define MAX_BULLETS 3
#define MAX_ENEMY_BULLETS 20

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
    int active;
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
void update_bullets(void);
void shoot(void);
void update_enemy_bullets(void);

extern player pl;
extern enemy enemies[MAX_ENEMIES];
extern bullet bullets[MAX_BULLETS];
extern bullet enemy_bullets[MAX_ENEMY_BULLETS];
extern int gameover;
extern int spawned;
extern int killed;

#endif
