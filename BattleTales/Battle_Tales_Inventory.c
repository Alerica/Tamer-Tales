#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

// #include "Battle_Tales_Display.h"
#include "Battle_Tales_UI.h"
// #include "Battle_Tales_FileProcessing.h"
// #include "Battle_Tales_Performance.h"
// #include "Battle_Tales_PokemonStruct.h"

#define MAX_LINE_LENGTH 1000
#define MAX_NAME_LENGTH 50
#define MAX_TYPE_LENGTH 20

typedef struct {
    int number;
    char name[MAX_NAME_LENGTH];
    char type1[MAX_TYPE_LENGTH];
    char type2[MAX_TYPE_LENGTH];
    int level;
    int exp;
    int IV;
    int hp;
    int attack;
    int defense;
    int sp_attack;
    int sp_defense;
    int speed;
    int affinity;
} Pokemon;

typedef struct {
    int number;
    char name[MAX_NAME_LENGTH];
    char type[MAX_TYPE_LENGTH];
    char category[MAX_TYPE_LENGTH];
    int pp;
    int power;
    int accuracy;
    char gen[MAX_TYPE_LENGTH];
} Move;

void mapMenu();
int inventoryMenu();
void inventoryMenuDisplay(int current);
void inventoryMenuNav(int nav);
void printPokemonInventory(Pokemon p);
void printAllDataInventory(char file_name[]);
void printItemInventory(char *text ,int count);
void printAllItemInventory(char file_name[]);

void printAllItemInventory(char file_name[]) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        printf("Press any key to continue..");
        getch();
        return;
    }

    char line[MAX_LINE_LENGTH];
    system("cls");
    printf("=========================================\n");
    colorText("yellow", "Item Name               Count  \n");
    printf("=========================================\n");
    fgets(line, sizeof(line), file); 
    int max_data = atoi(line);
    for(int i = 0; i < max_data; i++){
        fgets(line, sizeof(line), file);
        char item_name[MAX_LINE_LENGTH];
        strcpy(item_name, line);
        item_name[strlen(item_name) - 1] = '\0';
        fgets(line, sizeof(line), file);
        int item_count = atoi(line);
        printf("%-23s %-5d\n", item_name, item_count);
    }
}

void printItemInventory(char *text, int count) {
    printf("%-20s %-5d\n", text, count);
}

void mapMenu() {
    int x = -2;
    while(x != 3) {
        x = inventoryMenu();
        inventoryMenuNav(x);
    }
}

int inventoryMenu() {
    char input = ' ';
    int count = 600;
    inventoryMenuDisplay(count);
    while (true) {
        input = _getch();  // Read a single character without pressing Enter
        switch (input) {
            case 'S':
            case 's':
                count++;
                break;
            case 'W':
            case 'w':
                count--;
                break;
            case 'B':
            case 'b':
                return 3;
                break;
            case '\r': // press 'enter'
                return count % 3 + 1;
            default:
                int a = input;
                switch (a) {
                case 72: //up
                    count--;
                    break;
                case 75: //left
                    break;
                case 77: //right
                    break;
                case 80: //down
                    count++;
                    break;
                }
                break;
        } 
        inventoryMenuDisplay(count);
    }
}

void inventoryMenuDisplay(int current) {
    int atMenu = current % 3 + 1;
    switch(atMenu){
        case 1:
            system("cls");
            printf("================================================================\n");
            printf("                            Tamer Tales                         \n");
            printf("================================================================\n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                        Select Menu :                           \n");
            printf("                        > View Items                            \n");
            printf("                          View Pokemons                         \n");
            printf("                          Back                                  \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("================================================================\n");
            break;
        case 2:
            system("cls");
            printf("================================================================\n");
            printf("                            Tamer Tales                         \n");
            printf("================================================================\n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                        Select Menu :                           \n");
            printf("                          View Items                            \n");
            printf("                        > View Pokemons                         \n");
            printf("                          Back                                  \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("================================================================\n");
            break;
        case 3:
            system("cls");
            printf("================================================================\n");
            printf("                            Tamer Tales                         \n");
            printf("================================================================\n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                        Select Menu :                           \n");
            printf("                          View Items                            \n");
            printf("                          View Pokemons                         \n");
            printf("                        > Back                                  \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("================================================================\n");
            break;
    }
}
void inventoryMenuNav(int nav){
    switch (nav) {
    case 1:
        printAllItemInventory("./assets/save_data/slot_1/inventory/items.txt");
        getch();
        break;
    case 2:
        printAllDataInventory("./assets/save_data/slot_1/inventory/pokemons.txt");
        getch();
        break;
    default:
        break;
    }
}

void printPokemonInventory(Pokemon p) {
    //jika number = 0, maka tidak perlu di print (tidak print 0 dan None)
    if(p.number == 0) {
        return;
    }
    printf("| %-6d | %-15s | %-12s | %-12s | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d | %-5d | %-4d|\n",
        p.number, p.name, p.type1, p.type2[0] == '\0' ? "None" : p.type2, p.level, p.exp, p.IV, p.hp, p.attack, p.defense, p.sp_attack, p.sp_defense, p.speed, p.affinity);
}

void printAllDataInventory(char file_name[]){
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        printf("Press any key to continue..");
        getch();
        return;
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); 
    fgets(line, sizeof(line), file); 
    int max_data = atoi(line);
    Pokemon pokemons[30];
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
        p.level = atoi(token);

        token = strtok(NULL, ",");
        p.exp = atoi(token);

        token = strtok(NULL, ",");
        p.IV = atoi(token);

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

        token = strtok(NULL, ",");
        p.affinity = atoi(token);

        pokemons[count++] = p;
    }

    fclose(file);

    system("cls");
    printf("================================================================================================================================\n");
    colorText("yellow", "| Number | Name            | Type 1       | Type 2       | Lv   | Exp  | IV   | HP   | Atk  | Def  | Sp.A | Sp.D | Speed | Aff |\n");
    // printf("=================================================================================================================================\n");
    
    FILE *file2 = fopen("./assets/save_data/slot_1/inventory/movelist.txt", "r");
    if (file2 == NULL) {
        fprintf(stderr, "Could not open file\n");
        printf("Press any key to continue..");
        getch();
        return;
    }

    char text[MAX_LINE_LENGTH];
    // fgets(text, sizeof(text), text); 
    
    for (int i = 0; i < max_data; i++) {
        printPokemonInventory(pokemons[i]);
        printf("=================================================================================================================================\n");
        printf("Movelist : \n");
        fgets(text, sizeof(text), file2); 
        printf("\t\t%s", text);
        fgets(text, sizeof(text), file2); 
        printf("\t\t%s", text);
        fgets(text, sizeof(text), file2); 
        printf("\t\t%s", text);
        fgets(text, sizeof(text), file2); 
        printf("\t\t%s", text);
        printf("=================================================================================================================================\n");
        
        getch();
    }
    fclose(file2);
    printf("=================================================================================================================================\n");
}
