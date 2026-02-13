
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#include "menu.h"
#include "game.h"

char current_user[MAX];

int sign_up()
{
    char username[30], password[30];
    char u[30], p[30];
    int found = 0, ch;

    FILE *fp = fopen("users.txt", "r");

    wprintf(L"create username: ");
    scanf("%s", username);
    system("cls");


    if (fp)
    {
        while (fscanf(fp, "%s %s\n", u, p) == 2)
        {
            if (strcmp(u, username) == 0)
            {
                found = 1;
                break;
            }
        }
        fclose(fp);
    }

    if (found)
    {
        wprintf(L"this username alraedy has been used.\n\n");
        return 0;

    }

    else
    {
        wprintf(L"set password(at lest 8 chacter): ");
        for (int i = 0; ; )
        {
            ch = getch();
            if (ch == 13) {
                password[i] = '\0';
                break;
            }
            else if (ch == 32) {
                i--;
                continue;
            }
            else if (ch == 8) {
                i--;
                wprintf(L"\b \b");
            }
            else {
            password[i++] = ch;
            wprintf(L"*");
            }
        }

        
        system("cls");

        if (strlen(password) < 8) {
            wprintf(L"password is not valid.\n\n");
            return 0;
        }
        

        wprintf(L"confirm your password:");
        for (int i = 0; ; )
        {
            ch = getch();
            if (ch == 13) {
                p[i] = '\0';
                break;
            }
            else if (ch == 32) {
                i--;
                continue;
            }

            else if (ch == 8) {
                i--;
                wprintf(L"\b \b");
            }
            else {
            p[i++] = ch;
            wprintf(L"*");
            }
        }

        system("cls");

        if (strcmp(password, p) == 0) {
            
            fp = fopen("users.txt", "a");
            if (fp) {
                fprintf(fp, "%s %s\n", username, password);
                fclose(fp);
            }

            wprintf(L"Sign up successfully!\n\n");
            strcpy(current_user, username);
            return 1;
        }

        else {
            wprintf(L"password doesn't match.\n\n");
            return 0;
        }

    }
}

int login()
{
    char username[30], password[30];
    char u[30], p[30];
    int found = 0, ch;

    FILE *fp = fopen("users.txt", "r");

    wprintf(L"username: ");
    scanf("%s", username);
    system("cls");


    if (fp)
    {
        while (fscanf(fp, "%s %s\n", u, p) == 2)
        {
            if (strcmp(u, username) == 0)
            {
                found = 1;
                break;
            }
        }
        fclose(fp);
    }

    if (found != 1)
    {
        wprintf(L"this username is not exist.\n\n");
        return 0;

    }

    else
    {
        wprintf(L"password: ");
        for (int i = 0; ; )
        {
            ch = getch();
            if (ch == 13) {
                password[i] = '\0';
                break;
            }
            else if (ch == 32){
                i--;
                continue;
            }

            else if (ch == 8) {
                i--;
                wprintf(L"\b \b");
            }
            else {
            password[i++] = ch;
            wprintf(L"*");
            }
        }
        system("cls");
        
        if (strcmp(password, p) == 0) {
            wprintf(L"login successfully!\n\n");
            strcpy(current_user, username);
            return 1;
        }

        else {
            wprintf(L"password doesn't match.\n\n");
            return 0;
        }

    }
}


void change_user_info() {
    int option;
    
    system("cls");
    wprintf(L"\n   === EDIT USER INFO (%s) ===\n", current_user);
    wprintf(L"   1. Change Username\n");
    wprintf(L"   2. Change Password\n");
    wprintf(L"   3. Back\n");
    wprintf(L"   Select option: ");
    scanf("%d", &option);

    if (option == 3)
        return;

    char u[30], p[30];
    char new_data[30];
    int found = 0, exists = 0, ch;
    
    FILE *fp, *temp;

    if (option == 1) {
        wprintf(L"\nEnter new Username: ");
        scanf("%s", new_data);
        fp = fopen("users.txt", "r");
        while (fscanf(fp, "%s %s", u, p) == 2) {
            if (strcmp(u, new_data) == 0) {
                exists = 1;
                break;
            }
        }
        fclose(fp);

        if (exists) {
            wprintf(L"\n this username is already taken!\n");
            return;
        }

        fp = fopen("users.txt", "r");
        temp = fopen("temp.txt", "w");

        while (fscanf(fp, "%s %s", u, p) == 2) {
            if (strcmp(u, current_user) == 0) {
                fprintf(temp, "%s %s\n", new_data, p);
                found = 1;
            }
            else 
                fprintf(temp, "%s %s\n", u, p);
        }
        
        fclose(fp);
        fclose(temp);

        if (found) {
            remove("users.txt");
            rename("temp.txt", "users.txt");
            strcpy(current_user, new_data); 
           wprintf(L"\nusername changed to '%s'.\n", current_user);
        }
    }


    else if (option == 2) {
        wprintf(L"enter new Password: ");

        for (int i = 0; ; )
        {
            ch = getch();
            if (ch == 13) {
                new_data[i] = '\0';
                break;
            }
            else if (ch == 32){
                i--;
                continue;
            }

            else if (ch == 8) {
                i--;
                wprintf(L"\b \b");
            }
            else {
            new_data[i++] = ch;
            wprintf(L"*");
            }
        }
        
        fp = fopen("users.txt", "r");
        temp = fopen("temp.txt", "w");

        while (fscanf(fp, "%s %s", u, p) == 2) {
            if (strcmp(u, current_user) == 0) {
                fprintf(temp, "%s %s\n", u, new_data);
                found = 1;
            } 
            else {
                fprintf(temp, "%s %s\n", u, p);
            }
        }

        fclose(fp);
        fclose(temp);

        if (found) {
            remove("users.txt");
            rename("temp.txt", "users.txt");
            wprintf(L"\nPassword updated successfully.\n");
        }
    }

    wprintf(L"\n   Press any key to return...");
    getch();
}

void menu()
{
    int option;
    wprintf(L"======SPACE INVADERS======\n");
    wprintf(L"1.Sign up\n2.Login\n3.Exit\n");
    wprintf(L"==========================\n");
    wprintf(L"(Please enter from 1 to 3):");
    scanf("%d", &option);
    system("cls");

    switch (option)
    {
    case 1:
        if (sign_up() == 0) 
            menu();
        break;

    case 2:
        if (login() == 0) 
            menu();
        break;
    
    case 3:
        exit(0);
    
    default:
        menu();
    }
}

void menu_game()
{
    int option;

    wprintf(L"\n========MENU GAME========\n");
    wprintf(L"1.Start\n2.Leaderboard\n3.Store\n4.Edit user information\n5.Log out");
    wprintf(L"=========================");
    wprintf(L"(Please enter from 1 to 5):");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        break;
    case 2:
        show_leaderboard();
        break;
    case 3:
        store();
        break;
    case 4:
        change_user_info();
        break;
    case 5:
        menu();
        break;
    default:
        menu_game();
        break;
    }
}