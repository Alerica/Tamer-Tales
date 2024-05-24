/*
~~ Tamer Tales File Processing ~~
Contain all function for reading data from files

Update Log :
21 May 2024 by Alexander Ricky B. 
    - Create read function to read pokedex
    - Add function :
        void printData();
        void printPokemon(Pokemon p);
        void addData(Pokemon pokemons[]);
23 May 2024 by Alexander Ricky B. 
    - Improve read function, now it takes parameter
        printData(char file_name[], int total_data);
24 May 2024 by Alexander Ricky B.
    - Limit some of the function
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_NAME_LENGTH 50
#define MAX_TYPE_LENGTH 20

typedef struct {
    int number;
    char name[MAX_NAME_LENGTH];
    char type1[MAX_TYPE_LENGTH];
    char type2[MAX_TYPE_LENGTH];
    int hp;
    int attack;
    int defense;
    int sp_attack;
    int sp_defense;
    int speed;
} Pokemon;

void printData(char file_name[], int total_data);
void printPokemon(Pokemon p);
void addData(Pokemon pokemons[]);

void printData(char file_name[], int total_data) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        printf("Press any key to continue..");
        getch();
        return;
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); 

    Pokemon pokemons[total_data];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        Pokemon p;
        char *token;

        token = strtok(line, ",");
        p.number = atoi(token);

        token = strtok(NULL, ",");
        strncpy(p.name, token, MAX_NAME_LENGTH);

        token = strtok(NULL, ",");
        strncpy(p.type1, token, MAX_TYPE_LENGTH);

        token = strtok(NULL, ",");
        if (token != NULL && strcmp(token, "\n") != 0) {
            strncpy(p.type2, token, MAX_TYPE_LENGTH);
        } else {
            strcpy(p.type2, "");
        }

        token = strtok(NULL, ",");
        p.hp = atoi(token);

        token = strtok(NULL, ",");
        p.attack = atoi(token);

        token = strtok(NULL, ",");
        p.defense = atoi(token);

        token = strtok(NULL, ",");
        p.sp_attack = atoi(token);

        token = strtok(NULL, ",");
        p.sp_defense = atoi(token);

        token = strtok(NULL, ",");
        p.speed = atoi(token);

        pokemons[count++] = p;
    }

    fclose(file);
    
    printf("| Index | Name            | Type 1          | Type 2          | HP   | Atk  | Def  | SpA  | SpD  | Spe |\n");
    for (int i = 0; i < count; i++) {
        printPokemon(pokemons[i]);
    }

    printf("Press any key to continue..");
    getch();
}

void printPokemon(Pokemon p) {
    printf("| %-5d | %-15s | %-15s | %-15s | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d|\n",
        p.number, p.name, p.type1, p.type2[0] == '\0' ? "None" : p.type2, p.hp, p.attack, p.defense, p.sp_attack, p.sp_defense, p.speed);
}

void addData(Pokemon pokemons[]) {
    FILE *file = fopen("pokedex.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); 

    int count = 1;

    while (fgets(line, sizeof(line), file)) {
        Pokemon p;
        char *token;

        token = strtok(line, ",");
        p.number = atoi(token);

        token = strtok(NULL, ",");
        strncpy(p.name, token, MAX_NAME_LENGTH);

        token = strtok(NULL, ",");
        strncpy(p.type1, token, MAX_TYPE_LENGTH);

        token = strtok(NULL, ",");
        if (token != NULL && strcmp(token, "\n") != 0) {
            strncpy(p.type2, token, MAX_TYPE_LENGTH);
        } else {
            strcpy(p.type2, "");
        }

        token = strtok(NULL, ",");
        p.hp = atoi(token);

        token = strtok(NULL, ",");
        p.attack = atoi(token);

        token = strtok(NULL, ",");
        p.defense = atoi(token);

        token = strtok(NULL, ",");
        p.sp_attack = atoi(token);

        token = strtok(NULL, ",");
        p.sp_defense = atoi(token);

        token = strtok(NULL, ",");
        p.speed = atoi(token);

        pokemons[count++] = p;
    }

    fclose(file);
}
