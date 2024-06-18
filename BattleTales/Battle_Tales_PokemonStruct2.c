#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "Battle_Tales_UI.h"

#define MAX_LINE_LENGTH 1000
#define MAX_NAME_LENGTH 50
#define MAX_TYPE_LENGTH 20

typedef struct {
    int index;
    char name[MAX_NAME_LENGTH];
    char type[MAX_TYPE_LENGTH];
    char category[MAX_TYPE_LENGTH];
    int power;
    int accuracy;
    int pp;
    int curr_pp;
} moves;

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

typedef struct{
    Pokemon pokemon;
    moves moves[4];
    int max_hp;
    int curr_hp;
    int catch_rate;
    int exp;
    int level_up_exp;
    int level;
    int affinity;
    int IV;
} PokemonBattle;

typedef struct{
    char name[MAX_NAME_LENGTH];
    int quantity;
} Bag;

void searchPokemon(int wildIndex, PokemonBattle *wild);
int searchMove(moves move[], PokemonBattle *wild);
void wildPokemon(PokemonBattle *wild);
void printbattle(PokemonBattle *wild, PokemonBattle inv[], int index);
int getInventory(PokemonBattle inv[]);
void getSkillData(PokemonBattle inv[], int max_data);
int getBagData(Bag bag[]);
void maxHP(PokemonBattle *wild);
int menuBattleNavigation(int nav, int max_data, PokemonBattle inv[], PokemonBattle *wild, int *index, Bag bag[]);
int menuBattle(PokemonBattle *wild, PokemonBattle inv[], int max_data, Bag bag[], int max_bag, int index);
void menuBattleDisplay(int current, PokemonBattle *wild, PokemonBattle inv[], int index);
int menuPokemonSwitch(PokemonBattle *wild, PokemonBattle inv[], int *index);
int menuPokemonSwitchNavigation(int nav, PokemonBattle inv[], int max_data, int *index);
void menuPokemonDisplay(PokemonBattle inv[], int current, int *index, PokemonBattle *wild);

int menuFightNavigation(int nav, PokemonBattle inv[], PokemonBattle *wild, int index);
int menuFight(PokemonBattle *wild, PokemonBattle inv[], int index);
void menuFightDisplay(int current, PokemonBattle *wild, PokemonBattle inv[], int index);

void hpUpdate(PokemonBattle *attacker, PokemonBattle *defender, int damage);
int damageCalc(PokemonBattle *attacker, PokemonBattle *defender, moves skill);
float isEffective(PokemonBattle *attacker, PokemonBattle *defender, moves skill);

int menuInventory(PokemonBattle inv[], int size, PokemonBattle *wild, int *index, Bag bag[]);
int menuInventoryNavigation(int nav, PokemonBattle inv[], int max_data, PokemonBattle *wild, int *index, Bag bag[]);
void menuInventoryDisplay(int current, PokemonBattle inv[], int size, PokemonBattle *wild, int *index, Bag bag[]);
int itemEffect(PokemonBattle *inv, Bag bag, PokemonBattle *wild, int i);
int catchSystem(PokemonBattle *wild, PokemonBattle inv[], int *index, Bag bag[]);
int catchSystemNavigation(int nav, PokemonBattle *wild, PokemonBattle inv[], int *index, Bag bag[]);
void catchSystemDisplay(int count, PokemonBattle *wild, PokemonBattle inv[], int *index, Bag bag[]);
int updateInventory(PokemonBattle inv[], PokemonBattle *wild, int *index, Bag bag[]);

int main(){
    int max_data;
    int max_bag;
    int index;
    PokemonBattle wild;
    PokemonBattle inv[7];
    Bag bag[10];
    for(int i = 0; i < 7; i++){
        inv[i].pokemon.name[0] = '\0'; // Set the first character to null terminator
    }
    for(int i = 0; i < 10; i++){
        bag[i].name[0] = '\0'; // Set the first character to null terminator
    }
    index = 0;
    max_data = getInventory(inv);
    getSkillData(inv, max_data);
    max_bag = getBagData(bag);
    wildPokemon(&wild);
    int a = -1;
    int b;
    while(a != 4) {
        a = menuBattle(&wild, inv, max_data, bag, max_bag, index);
        b = menuBattleNavigation(a, max_data, inv, &wild, &index, bag);
        if(b == 399){
            break;
        }
    }
    return 399;
}


void maxHP(PokemonBattle *wild){
    wild->max_hp = (2 * (wild->pokemon.hp + wild->IV) * wild->level)/ 100 + wild->level + 10;
    wild->curr_hp = wild->max_hp;
}

void searchPokemon(int wildIndex, PokemonBattle *wild){
    FILE *file = fopen("./assets/database/pokedex_all.txt", "r");
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
        if (token != NULL && strcmp(token, "\n") != 0 && strcmp(token, "") != 0) {
            strncpy(p.type2, token, MAX_TYPE_LENGTH);
        } else {
            strcpy(p.type2, "none");
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

        count++;
        if(count == wildIndex) {
            wild->pokemon = p;
            break;
        }
    }
    fclose(file);
}


int searchMove(moves move[], PokemonBattle *wild){
    int counter = 0;
    char gen[100];
    FILE *file = fopen("./assets/database/movelist.txt", "r");
    if (file == NULL) {
        printf("File not found\n");
        return 0;
    }
    char line[MAX_LINE_LENGTH];
    moves m;
    while (fgets(line, sizeof(line), file) != NULL) {
        char *token;

        token = strtok(line, ",");
        m.index = atoi(token);

        token = strtok(NULL, ",");
        strncpy(m.name, token, MAX_NAME_LENGTH);

        token = strtok(NULL, ",");
        strncpy(m.type, token, MAX_TYPE_LENGTH);

        token = strtok(NULL, ",");
        strncpy(m.category, token, MAX_TYPE_LENGTH);

        token = strtok(NULL, ",");
        m.pp = atoi(token);

        token = strtok(NULL, ",");
        m.power = atoi(token);

        token = strtok(NULL, ",");
        m.accuracy = atoi(token);

        token = strtok(NULL, ",");
        strncpy(gen, token, MAX_TYPE_LENGTH);
        if(counter == 99){
            break;
        }
        if(strcmp(m.type, wild->pokemon.type1) == 0 || strcmp(m.type, wild->pokemon.type2) == 0) {
            move[counter] = m;
            counter++;
        }
    }
    fclose(file);
    return counter;
}

void wildPokemon(PokemonBattle *wild){
    moves move[99];
    int wildIndex;
    int rate = rand() % 100+1;
    int index = 0;
    char indexString[100];
    char header[MAX_LINE_LENGTH];
    int totalMove;
    if (rate > 0) {
        printf("You encountered a wild Pokemon!\n");
        srand(time(NULL));
        wildIndex = rand() % 900 + 1;
        searchPokemon(wildIndex, wild);
        totalMove = searchMove(move, wild);
        for(int i = 0; i<4; i++){
            index = rand() % totalMove;
            wild->moves[i] = move[index];
        }
        wild->exp = 0;
        wild->level_up_exp = 100;
        wild->level = rand() % 100 + 1;
        wild->affinity = 0;
        wild->IV = rand() % 32;
        maxHP(wild);
    }
}


void printbattle(PokemonBattle *wild, PokemonBattle inv[], int index){
    // PokemonBattle wild;
    printf("Wild Pokemon\n");
    printf("Name: %s\n", wild->pokemon.name);
    printf("Type: %s\n", wild->pokemon.type1);
    printf("Level: %d\n", wild->level);
    printf("HP: %d / %d\n", wild->curr_hp, wild->max_hp);
    // printf("Moves:\n");
    // for(int i = 0; i < 4; i++) {
    //     printf("%d. %s\n", i + 1, wild->moves[i].name);
    // }
    printf("\n\n\n\n");
    printf("Your Pokemon\n");
    printf("Name: %s\n", inv[index].pokemon.name);
    printf("Level: %d\n", inv[index].level);
    printf("HP: %d / %d\n", inv[index].curr_hp, inv[index].max_hp);
}



int getInventory(PokemonBattle inv[]){
    FILE *file = fopen("./assets/save_data/slot_1/inventory/pokemons.txt", "r");
    if (file == NULL) {
        printf("File not found\n");
        return 0;
    }
    char *token;
    char line[MAX_LINE_LENGTH];
    int i = 0;
    fgets(line, sizeof(line), file);
    int max_data;
    max_data = atoi(fgets(line, sizeof(line), file));
    while(fgets(line, sizeof(line), file) != NULL){
        // while (fgets(line, sizeof(line), file) != NULL) {
        token = strtok(line, ",");
        inv[i].pokemon.number = atoi(token);

        token = strtok(NULL, ",");
        strncpy(inv[i].pokemon.name, token, MAX_NAME_LENGTH);

        token = strtok(NULL, ",");
        strncpy(inv[i].pokemon.type1, token, MAX_TYPE_LENGTH);

        token = strtok(NULL, ",");
        strncpy(inv[i].pokemon.type2, token, MAX_TYPE_LENGTH);

        token = strtok(NULL, ",");
        inv[i].level = atoi(token);

        token = strtok(NULL, ",");
        inv[i].exp = atoi(token);

        token = strtok(NULL, ",");
        inv[i].IV = atoi(token);

        token = strtok(NULL, ",");
        inv[i].max_hp = atoi(token);
        inv[i].curr_hp = inv[i].max_hp;

        token = strtok(NULL, ",");
        inv[i].pokemon.attack = atoi(token);

        token = strtok(NULL, ",");
        inv[i].pokemon.defense = atoi(token);

        token = strtok(NULL, ",");
        inv[i].pokemon.sp_attack = atoi(token);

        token = strtok(NULL, ",");
        inv[i].pokemon.sp_defense = atoi(token);

        token = strtok(NULL, ",");
        inv[i].pokemon.speed = atoi(token);

        token = strtok(NULL, ",");
        inv[i].affinity = atoi(token);
        i++;
        if(i == max_data){
            break;
        }
        // }
    }
    fclose(file);

    FILE *file2 = fopen("./assets/save_data/slot_1/inventory/movelist.txt", "r");
    if (file2 == NULL) {
        printf("File not found\n");
        return 0;
    }
    for(int i = 0; i<max_data; i++){
        for(int j = 0; j<4; j++){
            fgets(line, sizeof(line), file2);
            line[strlen(line) - 1] = '\0'; // remove '\n' at the end of line
            strcpy(inv[i].moves[j].name, line);
        }
    }
    fclose(file2);
    return max_data;
}

void getSkillData(PokemonBattle inv[], int max_data){
    FILE *file = fopen("./assets/database/movelist.txt", "r");
    if (file == NULL) {
        printf("File not found\n");
        return;
    }
    char line[MAX_LINE_LENGTH];
    while(fgets(line, sizeof(line), file) != NULL){
        char *token;
        moves m;
        token = strtok(line, ",");
        m.index = atoi(token);

        token = strtok(NULL, ",");
        strncpy(m.name, token, MAX_NAME_LENGTH);

        token = strtok(NULL, ",");
        strncpy(m.type, token, MAX_TYPE_LENGTH);

        token = strtok(NULL, ",");
        strncpy(m.category, token, MAX_TYPE_LENGTH);

        token = strtok(NULL, ",");
        m.pp = atoi(token);

        token = strtok(NULL, ",");
        m.power = atoi(token);

        token = strtok(NULL, ",");
        m.accuracy = atoi(token);

        m.curr_pp = m.pp;

        for(int i = 0; i<max_data; i++){
            for(int j = 0; j<4; j++){
                if(strcmp(m.name, inv[i].moves[j].name) == 0){
                    inv[i].moves[j] = m;
                }
            }
        }
    }
}

int getBagData(Bag bag[]){
    FILE *file = fopen("./assets/save_data/slot_1/inventory/items.txt", "r");
    if (file == NULL) {
        printf("File not found\n");
        return 0;
    }
    char line[MAX_LINE_LENGTH];
    
    int i = 0;
    // fgets(line, sizeof(line), file);
    int max_data;
    fgets(line, sizeof(line), file);
    line[strlen(line) - 1] = '\0'; // remove '\n' at the end of line
    max_data = atoi(line);
    printf("%d\n", max_data);
    while(fgets(line, sizeof(line), file) != NULL){
        Bag b;
        line[strlen(line) - 1] = '\0'; // remove '\n' at the end of line
        strcpy(b.name, line);
        // token = fgets(line, sizeof(line), file);
        b.quantity = atoi(fgets(line, sizeof(line), file));
        bag[i] = b;
        i++;
        if(i == max_data){
            break;
        }
    }
    fclose(file);
    return max_data;
}






// MENU BATTLE
int menuBattleNavigation(int nav, int max_data, PokemonBattle inv[], PokemonBattle *wild, int *index, Bag bag[]) {
    //char name[50];

    switch (nav) {
        case 1: ;
            // FIGHT (SKILL POKEMON)
            int menu1 = -1;
            int status;
            while (menu1 !=  5)
            {
                if(status == 5){
                    return 399;
                    break;
                }
                if(status == 4){
                    return 0;
                    break;
                }
                menu1 = menuFight(wild, inv, *index);
                status = menuFightNavigation(menu1, inv, wild, *index);
            }
            
            break;
        case 2: ;
            // BAG
            int menu2 = -1;
            while (menu2 !=  10)
            {
                menu2 = menuInventory(inv, max_data, wild, index, bag);
                menuInventoryNavigation(menu2, inv, max_data, wild, index, bag);

            }
            break;
        case 3:
            // POKEMON
            int menu3 = -1;
            while (menu3 !=  7)
            {
                menu3 = menuPokemonSwitch(wild, inv, index);
                menuPokemonSwitchNavigation(menu3, inv, max_data, index);
                return 0;                
            }
            break;
        case 4:
            // RUN
            return 399;
            break;
    }
}


int menuBattle(PokemonBattle *wild, PokemonBattle inv[], int max_data, Bag bag[], int max_bag, int index) {
    char input = ' ';
    int count = 400;
    while (true) {
        switch (input) {
            case 'S':
            case 's':
                count++;
                break;
            case 'W':
            case 'w':
                count--;
                break;
            case '\r': // press 'enter'
                return count % 4 + 1;
            default:
                int a = input;
                switch (a) {
                case 72: //up
                    count--;
                    break;
                case 80: //down
                    count++;
                    break;
                }
                break;
        }
        menuBattleDisplay(count, wild, inv, index);
        input = _getch();  // Read a single character without pressing Enter
    }
}

//display main menu
void menuBattleDisplay(int current, PokemonBattle *wild, PokemonBattle inv[], int index) {
    int atMenu = current % 4 + 1;
    switch(atMenu) {
        case 1:
            system("cls");
            printf("================================================================\n");
            printf("\n");
            printbattle(wild, inv, index);
            printf("\n");
            printf("================================================================\n");
            printf("  "); colorTextunderline("green", "FIGHT\n");
            printf("   BAG\n");
            printf("   POKEMON\n");
            printf("   RUN\n");
            break;
        case 2:
            system("cls");
            printf("================================================================\n");
            printf("\n");
            printbattle(wild, inv, index);
            printf("\n");
            printf("================================================================\n");
            printf("   FIGHT\n");
            printf("  "); colorTextunderline("green", "BAG\n");
            printf("   POKEMON\n");
            printf("   RUN\n");
            break;
        case 3:
            system("cls");
            printf("================================================================\n");
            printf("\n");
            printbattle(wild, inv, index);
            printf("\n");
            printf("================================================================\n");
            printf("   FIGHT\n");
            printf("   BAG\n");
            printf("  "); colorTextunderline("green", "POKEMON\n");
            printf("   RUN\n");
            break;
        case 4:
            system("cls");
            printf("================================================================\n");
            printf("\n");
            printbattle(wild, inv, index);
            printf("\n");
            printf("================================================================\n");
            printf("   FIGHT\n");
            printf("   BAG\n");
            printf("   POKEMON\n");
            printf("  "); colorTextunderline("green", "RUN\n");
            break;
    }
}


// MENU POKEMON SWITCH
int menuPokemonSwitch(PokemonBattle *wild, PokemonBattle inv[], int *index){
    char input = ' ';
    int count = 600;
    while (true) {
        switch (input) {
            case 'S':
            case 's':
                count++;
                break;
            case 'W':
            case 'w':
                count--;
                break;
            case '\r': // press 'enter'
                return count % 6 + 1;
            case 'B':
            case 'b':
                return 7;
            default:
                int a = input;
                switch (a) {
                case 72: //up
                    count--;
                    break;
                case 80: //down
                    count++;
                    break;
                }
                break;
        }
        menuPokemonDisplay(inv, count, index, wild);
        input = _getch();  // Read a single charasssscter without pressing Enter
    }
}

int menuPokemonSwitchNavigation(int nav, PokemonBattle inv[], int max_data, int *index) {
    //char name[50];
    switch (nav) {
        case 1: ;
            // POKEMON 1
            if(inv[0].pokemon.name[0] == '\0'){
                return 0;
            }
            *index = 0;
            break;
        case 2: ;
            // POKEMON 2
            if(inv[1].pokemon.name[0] == '\0'){
                return 0;
            }
            *index = 1;
            break;
        case 3: ;
            // POKEMON 3
            if(inv[2].pokemon.name[0] == '\0'){
                return 0;
            }
            *index = 2;
            break;
        case 4: ;
            // POKEMON 4
            if(inv[3].pokemon.name[0] == '\0'){
                return 0;
            }
            *index = 3;
            break;
        case 5: ;
            // POKEMON 5
            if(inv[4].pokemon.name[0] == '\0'){
                return 0;
            }
            *index = 4;
            break;
        case 6: ;
            // POKEMON 6
            if(inv[5].pokemon.name[0] == '\0'){
                return 0;
            }
            *index = 5;
            break;
    }
    return 0;
}

void menuPokemonDisplay(PokemonBattle inv[], int current, int *index, PokemonBattle *wild){
    int atMenu = current % 6 + 1;
    int i = *index;
    switch(atMenu) {
        case 1:
            system("cls");
            printf("================================================================\n");
            printf("\n");
            printbattle(wild, inv, i);
            printf("\n");
            printf("================================================================\n");
            if(inv[0].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   \033[4;32m%s\033[0m\n", inv[0].pokemon.name);
            }
            if(inv[1].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[1].pokemon.name);
            }
            if(inv[2].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[2].pokemon.name);
            }
            if(inv[3].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[3].pokemon.name);
            }
            if(inv[4].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[4].pokemon.name);
            }
            if(inv[5].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[5].pokemon.name);
            }
            break;
        case 2:
            system("cls");
            printf("================================================================\n");
            printf("\n");
            printbattle(wild, inv, i);
            printf("\n");
            printf("================================================================\n");
            if(inv[0].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[0].pokemon.name);
            }
            if(inv[1].pokemon.name[0] == '\0'){
                printf("   \033[4;32mEmpty\033[0m\n");
            } else {
                printf("   \033[4;32m%s\033[0m\n", inv[1].pokemon.name);
            }
            if(inv[2].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[2].pokemon.name);
            }
            if(inv[3].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[3].pokemon.name);
            }
            if(inv[4].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[4].pokemon.name);
            }
            if(inv[5].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[5].pokemon.name);
            }
            break;
        case 3:
            system("cls");
            printf("================================================================\n");
            printf("\n");
            printbattle(wild, inv, i);
            printf("\n");
            printf("================================================================\n");
            if(inv[0].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[0].pokemon.name);
            }
            if(inv[1].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[1].pokemon.name);
            }
            if(inv[2].pokemon.name[0] == '\0'){
                printf("   \033[4;32mEmpty\033[0m\n");
            } else {
                printf("   \033[4;32m%s\033[0m\n", inv[2].pokemon.name);
            }
            if(inv[3].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[3].pokemon.name);
            }
            if(inv[4].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[4].pokemon.name);
            }
            if(inv[5].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[5].pokemon.name);
            }
            break;
        case 4:
            system("cls");
            printf("================================================================\n");
            printf("\n");
            printbattle(wild, inv, i);
            printf("\n");
            printf("================================================================\n");
            if(inv[0].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[0].pokemon.name);
            }
            if(inv[1].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[1].pokemon.name);
            }
            if(inv[2].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[2].pokemon.name);
            }
            if(inv[3].pokemon.name[0] == '\0'){
                printf("   \033[4;32mEmpty\033[0m\n");
            } else {
                printf("   \033[4;32m%s\033[0m\n", inv[3].pokemon.name);
            }
            if(inv[4].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[4].pokemon.name);
            }
            if(inv[5].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[5].pokemon.name);
            }
            break;
        case 5:
            system("cls");
            printf("================================================================\n");
            printf("\n");
            printbattle(wild, inv, i);
            printf("\n");
            printf("================================================================\n");
            if(inv[0].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[0].pokemon.name);
            }
            if(inv[1].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[1].pokemon.name);
            }
            if(inv[2].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[2].pokemon.name);
            }
            if(inv[3].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[3].pokemon.name);
            }
            if(inv[4].pokemon.name[0] == '\0'){
                printf("   \033[4;32mEmpty\033[0m\n");
            } else {
                printf("   \033[4;32m%s\033[0m\n", inv[4].pokemon.name);
            }
            if(inv[5].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[5].pokemon.name);
            }
            break;
        case 6:
            system("cls");
            printf("================================================================\n");
            printf("\n");
            printbattle(wild, inv, i);
            printf("\n");
            printf("================================================================\n");
            if(inv[0].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[0].pokemon.name);
            }
            if(inv[1].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[1].pokemon.name);
            }
            if(inv[2].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[2].pokemon.name);
            }
            if(inv[3].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[3].pokemon.name);
            }
            if(inv[4].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[4].pokemon.name);
            }
            if(inv[5].pokemon.name[0] == '\0'){
                printf("   \033[4;32mEmpty\033[0m\n");
            } else {
                printf("   \033[4;32m%s\033[0m\n", inv[5].pokemon.name);
            }
            break;
    }

}




// MENU FIGHT
int menuFightNavigation(int nav, PokemonBattle inv[], PokemonBattle *wild, int index) {
    //char name[50];
    int damage;
    int enemyDamage;
    moves skill;
    moves enemyMove;
    int enemyindex;
    switch (nav) {
        case 1: ;
            // FIGHT (SKILL POKEMON)
            if(inv[index].moves[0].curr_pp == 0){
                printf("No PP left!\n");
                getch();
                return 0;
            }
            skill = inv[index].moves[0];
            damage = damageCalc(inv, wild, skill);
            hpUpdate(inv, wild, damage);
            if(wild->curr_hp <= 0){
                system("cls");
                printf("Enemy HP becomes 0\n");
                printf("You win!\n");
                getch();
                return 5;
            }
            enemyindex = rand() % 4;
            enemyMove = wild->moves[enemyindex];
            enemyDamage = damageCalc(wild, &inv[index], enemyMove);
            hpUpdate(wild, &inv[index], enemyDamage);
            printf("You dealt %d damage to the enemy\n", damage);
            printf("Enemy dealt %d damage to you\n", enemyDamage);
            break;
        case 2: ;
            if(inv[index].moves[0].curr_pp == 0){
                printf("No PP left!\n");
                getch();
                return 0;
            }
            skill = inv[index].moves[1];
            damage = damageCalc(inv, wild, skill);
            hpUpdate(inv, wild, damage);
            if(wild->curr_hp <= 0){
                system("cls");
                printf("Enemy HP becomes 0\n");
                printf("You win!\n");
                getch();
                return 5;
            }
            enemyindex = rand() % 4;
            enemyMove = wild->moves[enemyindex];
            enemyDamage = damageCalc(wild, &inv[index], enemyMove);
            hpUpdate(wild, &inv[index], enemyDamage);
            printf("You dealt %d damage to the enemy\n", damage);
            printf("Enemy dealt %d damage to you\n", enemyDamage);
            getch();
            break;
        case 3:
            if(inv[index].moves[0].curr_pp == 0){
                printf("No PP left!\n");
                getch();
                return 0;
            }
            skill = inv[index].moves[2];
            damage = damageCalc(inv, wild, skill);
            hpUpdate(inv, wild, damage);
            if(wild->curr_hp <= 0){
                system("cls");
                printf("Enemy HP becomes 0\n");
                printf("You win!\n");
                getch();
                return 5;
            }
            enemyindex = rand() % 4;
            enemyMove = wild->moves[enemyindex];
            enemyDamage = damageCalc(wild, &inv[index], enemyMove);
            hpUpdate(wild, &inv[index], enemyDamage);
            printf("You dealt %d damage to the enemy\n", damage);
            printf("Enemy dealt %d damage to you\n", enemyDamage);
            break;
        case 4:
            if(inv[index].moves[0].curr_pp == 0){
                printf("No PP left!\n");
                return 0;
            }
            skill = inv[index].moves[3];
            damage = damageCalc(inv, wild, skill);
            hpUpdate(inv, wild, damage);
            if(wild->curr_hp <= 0){
                system("cls");
                printf("Enemy HP becomes 0\n");
                printf("You win!\n");
                return 5;
            }
            enemyindex = rand() % 4;
            enemyMove = wild->moves[enemyindex];
            enemyDamage = damageCalc(wild, &inv[index], enemyMove);
            hpUpdate(wild, &inv[index], enemyDamage);
            printf("You dealt %d damage to the enemy\n", damage);
            printf("Enemy dealt %d damage to you\n", enemyDamage);
            getch();
            break;
    }
    
}

int menuFight(PokemonBattle *wild, PokemonBattle inv[], int index) {
    char input = ' ';
    int count = 800;
    if(inv[index].curr_hp == 0){
        printf("No HP left!\n");
        getch();
        return 5;
    }
    while (true) {
        switch (input) {
            case 'S':
            case 's':
                count++;
                break;
            case 'W':
            case 'w':
                count--;
                break;
            case '\r': // press 'enter'
                return count % 4 + 1;
            case 'B':
            case 'b':
                return 5;
            default:
                int a = input;
                switch (a) {
                case 72: //up
                    count--;
                    break;
                case 80: //down
                    count++;
                    break;
                }
                break;
        }
        menuFightDisplay(count, wild, inv, index);
        input = _getch();  // Read a single character without pressing Enter
    }
}

void menuFightDisplay(int current, PokemonBattle *wild, PokemonBattle inv[], int index) {
    int atMenu = current % 4 + 1;
    switch(atMenu) {
        case 1:
            system("cls");
            printf("================================================================\n");
            printf("\n");
            printbattle(wild, inv, index);
            printf("\n");
            printf("================================================================\n");
            printf("  "); colorTextunderline("green", inv[index].moves[0].name); printf("\n");
            printf("   %s\n", inv[index].moves[1].name);
            printf("   %s\n", inv[index].moves[2].name);
            printf("   %s\n", inv[index].moves[3].name);
            break;
        case 2:
            system("cls");
            printf("================================================================\n");
            printf("\n");
            printbattle(wild, inv, index);
            printf("\n");
            printf("================================================================\n");
            printf("   %s\n", inv[index].moves[0].name);
            printf("  "); colorTextunderline("green", inv[index].moves[1].name); printf("\n");
            printf("   %s\n", inv[index].moves[2].name);
            printf("   %s\n", inv[index].moves[3].name);
            break;
        case 3:
            system("cls");
            printf("================================================================\n");
            printf("\n");
            printbattle(wild, inv, index);
            printf("\n");
            printf("================================================================\n");
            printf("   %s\n", inv[index].moves[0].name);
            printf("   %s\n", inv[index].moves[1].name);
            printf("  "); colorTextunderline("green", inv[index].moves[2].name); printf("\n");
            printf("   %s\n", inv[index].moves[3].name);
            break;
        case 4:
            system("cls");
            printf("================================================================\n");
            printf("\n");
            printbattle(wild, inv, index);
            printf("\n");
            printf("================================================================\n");
            printf("   %s\n", inv[index].moves[0].name);
            printf("   %s\n", inv[index].moves[1].name);
            printf("   %s\n", inv[index].moves[2].name);
            printf("  "); colorTextunderline("green", inv[index].moves[3].name);
            break;
    }
}

void hpUpdate(PokemonBattle *attacker, PokemonBattle *defender, int damage){
    defender->curr_hp -= damage;
    if(defender->curr_hp <= 0){
        defender->curr_hp = 0;
    }
    return;
}

int damageCalc(PokemonBattle *attacker, PokemonBattle *defender, moves skill){
    int final_damage;
    double damage;
    int level = attacker->level;
    int attack = attacker->pokemon.attack;
    int defense = defender->pokemon.defense;
    int power = skill.power;
    int random = rand() % 16 + 85; // 85-101
    // jika efektif maka type = 2, jika tidak efektif maka type = 0.5
    // jika tidak ada efek maka type = 1
    float type = isEffective(attacker, defender, skill);
    
    int critical = rand() % 16;
    int modifier = 150;
    int max_modifier = 100;
    if(critical == 0){
        modifier = 210;
    }
    damage = (((((2 * ((double)level / 100 + 1) *(double) modifier / (double)max_modifier * ((double)attack / (double)defense))  / 5) + 2) * (double)power / 250) + 2) * ((double)random / 255) * (double)type; 
    double adjust_damage = damage * 3.65;
    // printf("Damage: %lf\n", adjust_damagee);
    // getch();
    final_damage = (int)adjust_damage;
    if(final_damage < 1) final_damage = 1;
    if(final_damage > 999) final_damage = 999;
    return final_damage;
}

float isEffective(PokemonBattle *attacker, PokemonBattle *defender, moves skill){
    float effectiveness = 1;
    // if(strcmp(skill.type, defender->pokemon.type1) == 0 || strcmp(attacker->moves[index].type, defender->pokemon.type2) == 0){
        
    //Fire Type Move Effectiveness
    if(strcmp(skill.type, "fire") == 0){
        if(strcmpi(defender->pokemon.type1, "grass") == 0 || strcmpi(defender->pokemon.type2, "grass") == 0 ||
            strcmpi(defender->pokemon.type1, "bug") == 0 || strcmpi(defender->pokemon.type2, "bug") == 0 ||
            strcmpi(defender->pokemon.type1, "ice") == 0 || strcmpi(defender->pokemon.type2, "ice") == 0 ||
            strcmpi(defender->pokemon.type1, "steel") == 0 || strcmpi(defender->pokemon.type2, "steel") == 0){
            effectiveness = 2;
        } else if(strcmpi(defender->pokemon.type1, "water") == 0 || strcmpi(defender->pokemon.type2, "water") == 0 ||
            strcmpi(defender->pokemon.type1, "rock") == 0 || strcmpi(defender->pokemon.type2, "rock") == 0 ||
            strcmpi(defender->pokemon.type1, "ground") == 0 || strcmpi(defender->pokemon.type2, "ground") == 0){
            effectiveness = 0.5;
        }
    } 
    
    //Water Type Move Effectiveness
    else if(strcmp(skill.type, "water") == 0){
        if(strcmpi(defender->pokemon.type1, "fire") == 0 || strcmpi(defender->pokemon.type2, "fire") == 0 ||
            strcmpi(defender->pokemon.type1, "rock") == 0 || strcmpi(defender->pokemon.type2, "rock") == 0 ||
            strcmpi(defender->pokemon.type1, "ground") == 0 || strcmpi(defender->pokemon.type2, "ground") == 0){
            effectiveness = 2;
        } else if(strcmp(defender->pokemon.type1, "grass") == 0 || strcmp(defender->pokemon.type2, "grass") == 0 ||
            strcmp(defender->pokemon.type1, "electric") == 0 || strcmp(defender->pokemon.type2, "electric") == 0){
            effectiveness = 0.5;
        }
    }
    
    //Grass Type Move Effectiveness
    else if(strcmpi(skill.type, "grass") == 0){
        if(strcmpi(defender->pokemon.type1, "water") == 0 || strcmpi(defender->pokemon.type2, "water") == 0 || 
            strcmpi(defender->pokemon.type1, "rock") == 0 || strcmpi(defender->pokemon.type2, "rock") == 0 ||
            strcmpi(defender->pokemon.type1, "ground") == 0 || strcmpi(defender->pokemon.type2, "ground") == 0){
            effectiveness = 2;
        } else if(strcmpi(defender->pokemon.type1, "fire") == 0 || strcmpi(defender->pokemon.type2, "fire") == 0 ||
            strcmpi(defender->pokemon.type1, "ice") == 0 || strcmpi(defender->pokemon.type2, "ice") == 0 ||
            strcmpi(defender->pokemon.type1, "poison") == 0 || strcmpi(defender->pokemon.type2, "poison") == 0 ||
            strcmpi(defender->pokemon.type1, "flying") == 0 || strcmpi(defender->pokemon.type2, "flying") == 0 ||
            strcmpi(defender->pokemon.type1, "bug") == 0 || strcmpi(defender->pokemon.type2, "bug") == 0){
            effectiveness = 0.5;
        }
    }
    
    //Rock Type Effectiveness
    else if(strcmpi(skill.type, "rock") == 0){
        if(strcmpi(defender->pokemon.type1, "fire") == 0 || strcmpi(defender->pokemon.type2, "fire") == 0 ||
            strcmpi(defender->pokemon.type1, "ice") == 0 || strcmpi(defender->pokemon.type2, "ice") == 0 ||
            strcmpi(defender->pokemon.type1, "flying") == 0 || strcmpi(defender->pokemon.type2, "flying") == 0 ||
            strcmpi(defender->pokemon.type1, "bug") == 0 || strcmpi(defender->pokemon.type2, "bug") == 0){
            effectiveness = 2;
        } else if(strcmpi(defender->pokemon.type1, "fighting") == 0 || strcmpi(defender->pokemon.type2, "fighting") == 0 ||
            strcmpi(defender->pokemon.type1, "ground") == 0 || strcmpi(defender->pokemon.type2, "ground") == 0 ||
            strcmpi(defender->pokemon.type1, "steel") == 0 || strcmpi(defender->pokemon.type2, "steel") == 0 ||
            strcmpi(defender->pokemon.type1, "water") == 0 || strcmpi(defender->pokemon.type2, "water") == 0 ||
            strcmpi(defender->pokemon.type1, "grass") == 0 || strcmpi(defender->pokemon.type2, "grass") == 0){
            effectiveness = 0.5;
        }
    }

    //Ice Type Effectiveness
    else if(strcmpi(skill.type, "ice") == 0){
        if(strcmpi(defender->pokemon.type1, "grass") == 0 || strcmpi(defender->pokemon.type2, "grass") == 0 ||
            strcmpi(defender->pokemon.type1, "ground") == 0 || strcmpi(defender->pokemon.type2, "ground") == 0 ||
            strcmpi(defender->pokemon.type1, "flying") == 0 || strcmpi(defender->pokemon.type2, "flying") == 0 ||
            strcmpi(defender->pokemon.type1, "dragon") == 0 || strcmpi(defender->pokemon.type2, "dragon") == 0){
            effectiveness = 2;
        } else if(strcmpi(defender->pokemon.type1, "fire") == 0 || strcmpi(defender->pokemon.type2, "fire") == 0 ||
            strcmpi(defender->pokemon.type1, "fighting") == 0 || strcmpi(defender->pokemon.type2, "fighting") == 0 ||
            strcmpi(defender->pokemon.type1, "rock") == 0 || strcmpi(defender->pokemon.type2, "rock") == 0 ||
            strcmpi(defender->pokemon.type1, "steel") == 0 || strcmpi(defender->pokemon.type2, "steel") == 0){
            effectiveness = 0.5;
        }
    }

    //Dragon Effectiveness
    else if(strcmpi(skill.type, "dragon") == 0){
        if(strcmpi(defender->pokemon.type1, "ice") == 0 || strcmpi(defender->pokemon.type2, "ice") == 0 ||
            strcmpi(defender->pokemon.type1, "fairy") == 0 || strcmpi(defender->pokemon.type2, "fairy") == 0){
            effectiveness = 0.5;
        }
    }

    //Dark Type Effectiveness
    else if(strcmpi(skill.type, "dark") == 0){
        if(strcmpi(defender->pokemon.type1, "psychic") == 0 || strcmpi(defender->pokemon.type2, "psychic") == 0 ||
            strcmpi(defender->pokemon.type1, "ghost") == 0 || strcmpi(defender->pokemon.type2, "ghost") == 0){
            effectiveness = 2;
        } else if(strcmpi(defender->pokemon.type1, "fighting") == 0 || strcmpi(defender->pokemon.type2, "fighting") == 0 ||
            strcmpi(defender->pokemon.type1, "bug") == 0 || strcmpi(defender->pokemon.type2, "bug") == 0 ||
            strcmpi(defender->pokemon.type1, "fairy") == 0 || strcmpi(defender->pokemon.type2, "fairy") == 0){
            effectiveness = 0.5;
        }
    }

    //Psychic Type Effectiveness
    else if(strcmpi(skill.type, "psychic") == 0){
        if(strcmpi(defender->pokemon.type1, "fighting") == 0 || strcmpi(defender->pokemon.type2, "fighting") == 0 ||
            strcmpi(defender->pokemon.type1, "poison") == 0 || strcmpi(defender->pokemon.type2, "poison") == 0){
            effectiveness = 2;
        } else if(strcmpi(defender->pokemon.type1, "bug") == 0 || strcmpi(defender->pokemon.type2, "bug") == 0 ||
            strcmpi(defender->pokemon.type1, "ghost") == 0 || strcmpi(defender->pokemon.type2, "ghost") == 0 ||
            strcmpi(defender->pokemon.type1, "dark") == 0 || strcmpi(defender->pokemon.type2, "dark") == 0){
            effectiveness = 0.5;
        }
    }

    //Bug Type Effectiveness
    else if(strcmpi(skill.type, "bug") == 0){
        if(strcmpi(defender->pokemon.type1, "grass") == 0 || strcmpi(defender->pokemon.type2, "grass") == 0 ||
            strcmpi(defender->pokemon.type1, "psychic") == 0 || strcmpi(defender->pokemon.type2, "psychic") == 0 ||
            strcmpi(defender->pokemon.type1, "dark") == 0 || strcmpi(defender->pokemon.type2, "dark") == 0){
            effectiveness = 2;
        } else if(strcmpi(defender->pokemon.type1, "fire") == 0 || strcmpi(defender->pokemon.type2, "fire") == 0 ||
            strcmpi(defender->pokemon.type1, "flying") == 0 || strcmpi(defender->pokemon.type2, "flying") == 0 ||
            strcmpi(defender->pokemon.type1, "rock") == 0 || strcmpi(defender->pokemon.type2, "rock") == 0){
            effectiveness = 0.5;
        }
    }

    //Flying Type Effectiveness
    else if(strcmpi(skill.type, "flying") == 0){
        if(strcmpi(defender->pokemon.type1, "fighting") == 0 || strcmpi(defender->pokemon.type2, "fighting") == 0 ||
            strcmpi(defender->pokemon.type1, "bug") == 0 || strcmpi(defender->pokemon.type2, "bug") == 0 ||
            strcmpi(defender->pokemon.type1, "grass") == 0 || strcmpi(defender->pokemon.type2, "grass") == 0){
            effectiveness = 2;
        } else if(strcmpi(defender->pokemon.type1, "electric") == 0 || strcmpi(defender->pokemon.type2, "electric") == 0 ||
            strcmpi(defender->pokemon.type1, "rock") == 0 || strcmpi(defender->pokemon.type2, "rock") == 0 ||
            strcmpi(defender->pokemon.type1, "ice") == 0 || strcmpi(defender->pokemon.type2, "ice") == 0){
            effectiveness = 0.5;
        }
    }

    //Steel Type Effectiveness
    else if(strcmpi(skill.type, "steel") == 0){
        if(strcmpi(defender->pokemon.type1, "ice") == 0 || strcmpi(defender->pokemon.type2, "ice") == 0 ||
            strcmpi(defender->pokemon.type1, "rock") == 0 || strcmpi(defender->pokemon.type2, "rock") == 0 ||
            strcmpi(defender->pokemon.type1, "fairy") == 0 || strcmpi(defender->pokemon.type2, "fairy") == 0){
            effectiveness = 2;
        } else if(strcmpi(defender->pokemon.type1, "fire") == 0 || strcmpi(defender->pokemon.type2, "fire") == 0 ||
            strcmpi(defender->pokemon.type1, "fighting") == 0 || strcmpi(defender->pokemon.type2, "fighting") == 0 ||
            strcmpi(defender->pokemon.type1, "ground") == 0 || strcmpi(defender->pokemon.type2, "ground") == 0){
            effectiveness = 0.5;
        }
    }

    //Fight Type Effectiveness
    else if(strcmpi(skill.type, "fighting") == 0){
        if(strcmpi(defender->pokemon.type1, "normal") == 0 || strcmpi(defender->pokemon.type2, "normal") == 0 ||
            strcmpi(defender->pokemon.type1, "rock") == 0 || strcmpi(defender->pokemon.type2, "rock") == 0 ||
            strcmpi(defender->pokemon.type1, "steel") == 0 || strcmpi(defender->pokemon.type2, "steel") == 0 ||
            strcmpi(defender->pokemon.type1, "ice") == 0 || strcmpi(defender->pokemon.type2, "ice") == 0 ||
            strcmpi(defender->pokemon.type1, "dark") == 0 || strcmpi(defender->pokemon.type2, "dark") == 0){
            effectiveness = 2;
        } else if(strcmpi(defender->pokemon.type1, "flying") == 0 || strcmpi(defender->pokemon.type2, "flying") == 0 ||
            strcmpi(defender->pokemon.type1, "fairy") == 0 || strcmpi(defender->pokemon.type2, "fairy") == 0 ||
            strcmpi(defender->pokemon.type1, "psychic") == 0 || strcmpi(defender->pokemon.type2, "psychic") == 0){
            effectiveness = 0.5;
        }
    }

    //Ground Type Effectiveness
    else if(strcmpi(skill.type, "ground") == 0){
        if(strcmpi(defender->pokemon.type1, "fire") == 0 || strcmpi(defender->pokemon.type2, "fire") == 0 ||
            strcmpi(defender->pokemon.type1, "electric") == 0 || strcmpi(defender->pokemon.type2, "electric") == 0 ||
            strcmpi(defender->pokemon.type1, "rock") == 0 || strcmpi(defender->pokemon.type2, "rock") == 0 ||
            strcmpi(defender->pokemon.type1, "steel") == 0 || strcmpi(defender->pokemon.type2, "steel") == 0 ||
            strcmpi(defender->pokemon.type1, "poison") == 0 || strcmpi(defender->pokemon.type2, "poison") == 0){
            effectiveness = 2;
        } else if(strcmpi(defender->pokemon.type1, "grass") == 0 || strcmpi(defender->pokemon.type2, "grass") == 0 ||
            strcmpi(defender->pokemon.type1, "water") == 0 || strcmpi(defender->pokemon.type2, "water") == 0 ||
            strcmpi(defender->pokemon.type1, "ice") == 0 || strcmpi(defender->pokemon.type2, "ice") == 0){
            effectiveness = 0.5;
        }
    }

    //Ghost Type Effectiveness
    else if(strcmpi(skill.type, "ghost") == 0){
        if(strcmpi(defender->pokemon.type1, "psychic") == 0 || strcmpi(defender->pokemon.type2, "psychic") == 0 ||
            strcmpi(defender->pokemon.type1, "ghost") == 0 || strcmpi(defender->pokemon.type2, "ghost") == 0){
            effectiveness = 2;
        } else if(strcmpi(defender->pokemon.type1, "dark") == 0 || strcmpi(defender->pokemon.type2, "dark") == 0 ||
            strcmpi(defender->pokemon.type1, "normal") == 0 || strcmpi(defender->pokemon.type2, "normal") == 0){
            effectiveness = 0.5;
        }
    }

    //Poison Type Effectiveness
    else if(strcmpi(skill.type, "poison") == 0){
        if(strcmpi(defender->pokemon.type1, "grass") == 0 || strcmpi(defender->pokemon.type2, "grass") == 0 ||
            strcmpi(defender->pokemon.type1, "fairy") == 0 || strcmpi(defender->pokemon.type2, "fairy") == 0){
            effectiveness = 2;
        } else if(strcmpi(defender->pokemon.type1, "Psychic") == 0 || strcmpi(defender->pokemon.type2, "Psychic") == 0 ||
            strcmpi(defender->pokemon.type1, "ground") == 0 || strcmpi(defender->pokemon.type2, "ground") == 0){
            effectiveness = 0.5;
        }
    }

    //fairy type effectiveness
    else if(strcmpi(skill.type, "fairy") == 0){
        if(strcmpi(defender->pokemon.type1, "fighting") == 0 || strcmpi(defender->pokemon.type2, "fighting") == 0 ||
            strcmpi(defender->pokemon.type1, "dragon") == 0 || strcmpi(defender->pokemon.type2, "dragon") == 0 ||
            strcmpi(defender->pokemon.type1, "dark") == 0 || strcmpi(defender->pokemon.type2, "dark") == 0){
            effectiveness = 2;
        } else if(strcmpi(defender->pokemon.type1, "poison") == 0 || strcmpi(defender->pokemon.type2, "poison") == 0 ||
            strcmpi(defender->pokemon.type1, "steel") == 0 || strcmpi(defender->pokemon.type2, "steel") == 0){
            effectiveness = 0.5;
        }
    }

    //Electrica Type Effectiveness
    else if(strcmpi(skill.type, "electric") == 0){
        if(strcmpi(defender->pokemon.type1, "water") == 0 || strcmpi(defender->pokemon.type2, "water") == 0 ||
            strcmpi(defender->pokemon.type1, "flying") == 0 || strcmpi(defender->pokemon.type2, "flying") == 0){
            effectiveness = 2;
        } else if(strcmpi(defender->pokemon.type1, "electric") == 0 || strcmpi(defender->pokemon.type2, "electric") == 0 ||
            strcmpi(defender->pokemon.type1, "ground") == 0 || strcmpi(defender->pokemon.type2, "ground") == 0){
            effectiveness = 0.5;
        }
    }

    //Normal Type Effectiveness
    else if(strcmpi(skill.type, "normal") == 0){
        if(strcmpi(defender->pokemon.type1, "fight") == 0 || strcmpi(defender->pokemon.type2, "fight") == 0){
            effectiveness = 0.5;
        }
    }
    return effectiveness;
}




//MENU BAG
int menuInventory(PokemonBattle inv[], int size, PokemonBattle *wild, int *index, Bag bag[]) {
    char input = ' ';
    int count = 1000;
    while (true) {
        switch (input) {
            case 'S':
            case 's':
                count++;
                break;
            case 'W':
            case 'w':
                count--;
                break;
            case '\r': // press 'enter'
                return count % size;
            case 'B':
            case 'b':
                return 10;
            default:
                int a = input;
                switch (a) {
                case 72: //up
                    count--;
                    break;
                case 80: //down
                    count++;
                    break;
                }
                break;
        }
        menuInventoryDisplay(count, inv, size, wild, index, bag);
        input = _getch();  // Read a single character without pressing Enter
    }
}

int menuInventoryNavigation(int nav, PokemonBattle inv[], int max_data, PokemonBattle *wild, int *index, Bag bag[]) {
    int status;
    status = itemEffect(&inv[*index], bag[nav], wild, *index);
    int menuCatch = -1;
    if(status == 999){
        menuCatch = catchSystem(wild, inv, index, bag);
        catchSystemNavigation(menuCatch, wild, inv, index, bag);
    }
    bag[nav].quantity--;
}

void menuInventoryDisplay(int current, PokemonBattle inv[], int size, PokemonBattle *wild, int *index, Bag bag[]) {
    int atMenu = current % size;
    int i = *index;
    system("cls");
    printf("================================================================\n");
    printf("\n");
    printbattle(wild, inv, *index);
    printf("\n");
    printf("================================================================\n");
    for(int i = 0; i < size; i++){
        if(i == atMenu){
            printf("  "); colorTextunderline("green", bag[i].name); printf("\n");
        } else {
            printf("   %s\n", bag[i].name);
        }
    }
}

int itemEffect(PokemonBattle *inv, Bag bag, PokemonBattle *wild, int i){
    if(strcmp(bag.name, "health_potion") == 0){
        inv->curr_hp += 20;
        if(inv->curr_hp >= inv->max_hp){
            inv->curr_hp = inv->max_hp;
            printf("Your pokemon is already full HP!\n");
            getch();
            return 0;
        }
    } else if(strcmpi(bag.name, "pokeball") == 0){
        int catch_rate = 255 * 3 / 3; // 255
        int random = rand() % 255; // 0-255
        if(random < catch_rate){
            printf("You caught the enemy!\n");
            getch();
            return 999;
        } else {
            printf("The enemy broke free!\n");
            getch();
            return 0;
        }
    } else if(strcmpi(bag.name, "greatball") == 0){
        int catch_rate = 255 * 3 / 2; // 382
        int random = rand() % 255; // 
        if(random < catch_rate){
            printf("You caught the enemy!\n");
            getch();
            return 999;
        } else {
            printf("The enemy broke free!\n");
            getch();
            return 0;
        }
    } else if(strcmpi(bag.name, "masterball") == 0){
        int catch_rate = 255 * 3 / 1; // 765
        int random = 0; // 0 (100% dapat)
        if(random < catch_rate){
            printf("You caught the enemy!\n");
            getch();
            return 999;
        } else {
            printf("The enemy broke free!\n");
            getch();
            return 0;
        }
    }
    return 0;
}

int catchSystem(PokemonBattle *wild, PokemonBattle inv[], int *index, Bag bag[]){
    char input = ' ';
    int count = 600;
    while (true) {
        switch (input) {
            case 'S':
            case 's':
                count++;
                break;
            case 'W':
            case 'w':
                count--;
                break;
            case '\r': // press 'enter'
                return count % 6 + 1;
            default:
                int a = input;
                switch (a) {
                case 72: //up
                    count--;
                    break;
                case 80: //down
                    count++;
                    break;
                }
                break;
        }
        catchSystemDisplay(count, wild, inv, index, bag);
        input = _getch();  // Read a single charasssscter without pressing Enter
    }
}

int catchSystemNavigation(int nav, PokemonBattle *wild, PokemonBattle inv[], int *index, Bag bag[]) {
    inv[nav] = *wild;
    updateInventory(inv, wild, index, bag);
    
}


void catchSystemDisplay(int count, PokemonBattle *wild, PokemonBattle inv[], int *index, Bag bag[]) {
    int atMenu = count % 6 + 1;
    system("cls");
    for(int i = 0; i < 6; i++){
        if(i == atMenu){
            if(inv[i].pokemon.name[0] == '\0'){
                printf("  "); colorTextunderline("green", "Empty"); printf("\n");
            } else {
                printf("  "); colorTextunderline("green", inv[i].pokemon.name); printf("\n");
            }
        } else {
            if(inv[i].pokemon.name[0] == '\0'){
                printf("   Empty\n");
            } else {
                printf("   %s\n", inv[i].pokemon.name);
            }
        }
    }
}

int updateInventory(PokemonBattle inv[], PokemonBattle *wild, int *index, Bag bag[]){
    int max_data = 0;
    while(inv[max_data].pokemon.name[0] != '\0'){
        max_data++;
        if(max_data == 6){
            break;
        }
    }
    FILE *file = fopen("./assets/save_data/slot_1/inventory/pokemons.txt", "w");
    if(file == NULL){
        printf("Error opening file\n");
        return 0;
    }
    fprintf(file, "Number,Name,Type 1,Type 2,Level,Exp,IV,HP,Attack,Defense,Sp. Attack,Sp. Defense,Speed,Affinity\n");
    fprintf(file, "%d\n", max_data);
    for(int i = 0; i < max_data; i++){
        // fprintf(file, "%00d,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s\n", inv[i].pokemon.number, inv[i].pokemon.name, inv[i].pokemon.type1, inv[i].pokemon.type2, inv[i].level, inv[i].exp, inv[i].IV, inv[i].max_hp, inv[i].pokemon.attack, inv[i].pokemon.defense, inv[i].pokemon.sp_attack, inv[i].pokemon.sp_defense, inv[i].pokemon.speed, inv[i].affinity);
        fprintf(file, "%03d", inv[i].pokemon.number);
        fprintf(file, ",%s", inv[i].pokemon.name);
        fprintf(file, ",%s", inv[i].pokemon.type1);
        fprintf(file, ",%s", inv[i].pokemon.type2);
        fprintf(file, ",%d", inv[i].level);
        fprintf(file, ",%d", inv[i].exp);
        fprintf(file, ",%d", inv[i].IV);
        fprintf(file, ",%d", inv[i].max_hp);
        fprintf(file, ",%d", inv[i].pokemon.attack);
        fprintf(file, ",%d", inv[i].pokemon.defense);
        fprintf(file, ",%d", inv[i].pokemon.sp_attack);
        fprintf(file, ",%d", inv[i].pokemon.sp_defense);
        fprintf(file, ",%d", inv[i].pokemon.speed);
        fprintf(file, ",%d\n", inv[i].affinity);
    }
    fclose(file);
}


// Reward System
int expUp(PokemonBattle *wild, PokemonBattle inv[], int index){
    
}