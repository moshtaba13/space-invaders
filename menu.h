#ifndef MENU_H
#define MENU_H

#define MAX 30

int sign_up(void);
int login(void);
void menu(void);
void menu_game(void);
void change_user_info(void);

extern char current_user[MAX];

#endif