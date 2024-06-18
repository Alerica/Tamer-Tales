#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <time.h>

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
    int catch_rate;
    int exp;
    int level_up_exp;
    int level;
    int affinity;
    int IV;
    int max_hp;
    int current_hp;
} PokemonBattle;

void searchPokemon(int wildIndex, PokemonBattle *wild);
int searchMove(moves move[], PokemonBattle *wild);
void wildPokemon(PokemonBattle *wild);
void printbattle(PokemonBattle *wild);
// void inventory();

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
        wild->level = 1;
        wild->affinity = 0;
    }
}


void printbattle(PokemonBattle *wild){
    // PokemonBattle wild;
    printf("Wild Pokemon\n");
    printf("Name: %s\n", wild->pokemon.name);
    printf("HP: %d\n", wild->pokemon.hp);
    printf("Level: %d\n", wild->level);
    printf("Moves:\n");
    for(int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, wild->moves[i].name);
    }
}

void wildPokemonSpawner(){
    PokemonBattle wild;
    wildPokemon(&wild);
    printbattle(&wild);
}

