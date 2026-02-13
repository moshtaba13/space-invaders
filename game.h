#ifndef GAME_H
#define GAME_H

#define MAX_LEADERBOARD 10


typedef struct {
    char username[30];
    int level;
    int coins; 
} Leaderboard;


Leaderboard leaderboard[MAX_LEADERBOARD + 1];

void draw_map(void);
void start(void);
void hide_cursor(void);
void setup_console(void);
void set_cursor_position(int , int );
void store(void);
void reset(void);
void show_leaderboard(void);
void update_leaderboard(char* ,int ,int ); 

#endif