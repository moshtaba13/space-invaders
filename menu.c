
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#include "menu.h"

int sign_up()
{
    char username[30], password[30];
    char u[30], p[30];
    int found = 0, ch;

    FILE *fp = fopen("users.txt", "r");

    printf("create username: ");
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
        printf("this username alraedy has been used.\n\n");
        return 0;

    }

    else
    {
        printf("set password(at lest 8 chacter): ");
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
                printf("\b \b");
            }
            else {
            password[i++] = ch;
            printf("*");
            }
        }

        
        system("cls");

        if (strlen(password) < 8) {
            printf("password is not valid.\n\n");
            return 0;
        }
        

        printf("confirm your password:");
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
                printf("\b \b");
            }
            else {
            p[i++] = ch;
            printf("*");
            }
        }

        system("cls");

        if (strcmp(password, p) == 0) {
            
            fp = fopen("users.txt", "a");
            if (fp) {
                fprintf(fp, "%s %s\n", username, password);
                fclose(fp);
            }

            printf("Sign up successfully!\n\n");
            return 1;
        }

        else {
            printf("password doesn't match.\n\n");
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

    printf("username: ");
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
        printf("this username is not exist.\n\n");
        return 0;

    }

    else
    {
        printf("password: ");
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
                printf("\b \b");
            }
            else {
            password[i++] = ch;
            printf("*");
            }
        }
        system("cls");
        
        if (strcmp(password, p) == 0) {
            printf("login successfully!\n\n");
            return 1;
        }

        else {
            printf("password doesn't match.\n\n");
            return 0;
        }

    }
}

void menu()
{
    int option;
    printf("======SPACE INVADERS======\n");
    printf("1.Sign up\n2.Login\n3.Exit\n");
    printf("==========================\n");
    printf("(Please enter from 1 to 3):");
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