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

27 May 2024 by Grace Birgitta H.
    - Add function printAllData
    - update condition function printData

28 May 2024 by Rafly Adha Prathama
    - Add function printAllMoveData
    - Add function printMove
    - Add new struct Move

29 May 2024 by Grace Birgitta H.
    - update printAllData function
    - update printAllMoveData function
    - update printData function
    - Add function : printPokemonType(char *type, int total_data)
4 June 2024 by Grace Birgitta H.
    - Add function : printSearchPokemon(char *name, int total_data)
7 June 2024 by Grace Birgitta H.
    - Update function : 
            - printSearchPokemon(char *name, int total_data)
            - update UI : searchPokemon(int Index) 
11 June 2024 by Grace Birgitta H.
    - update function : printAchievement() - add instruction
12 June 2024 by Grace Birgitta H.
    - update function : printAchievement() - add color
    - update UI : achievement()
16 June 2024 by Grace Birgitta H.
    - fix bug in printData() function
    - update UI : pokemonType()
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include "Tamer_Tales_UI.h"
#include "Tamer_Tales_Display.h"
// #include "Tamer_Tales_Graph.h"

#define MAX_LINE_LENGTH 1030
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

typedef struct{
    char name[MAX_NAME_LENGTH];
    char description[MAX_LINE_LENGTH];
} Achievement;

struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode* head;
};

struct Graph {
    int V;
    struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest);
struct Graph* createGraph(int V);
void addEdge(struct Graph* graph, int src, int dest); // Connect from source Node to destination Node
void printGraph(struct Graph* graph); // Display Graph
void add_edges_from_file(char* file_name, struct Graph* graph);
void printNext(struct Graph* graph, int src, int start);
void printEvolution(struct Graph* graph, int src, int start, Pokemon pokemons[]);
void searchPokemon(int index);

void printData(char file_name[], int total_data, int gen);
void printPokemon(Pokemon p);
void printMove(Move m);
void addData(Pokemon pokemons[]);
void printAllData(char file_name[], int start, int max_data, int total_data);
void printAllMoveData(char file_name[], int start, int max_data, int total_data);
void printPokemonType(char *type, int total_data);
// void add_edges_from_file(char* file_name, struct Graph* graph);
void printSearchPokemon(char *name, int total_data);

// void searchEvolution(int Index);
// void add_edges_from_file(char* file_name, struct Graph* graph);
void printAchievement();

//fungsi search
void printSearchPokemon(char *name, int total_data){
    FILE *file = fopen("./database/pokedex_all.txt", "r");
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

    int found =-1;

    
    for (int i = 0; i<count; i++){
        //jika name ditemukan di dalam nama pokemon dalam file yg dibaca
        if(strcmpi(pokemons[i].name, name)==0){
            //cetak pokemon dari index ke-i
            printf("--------------------------------------------------------------------------------------------------------\n");
            colorText("blue","| Index | Name            | Type 1          | Type 2          | HP   | Atk  | Def  | SpA  | SpD  | Spe |\n");
            printf("--------------------------------------------------------------------------------------------------------\n");
            printPokemon(pokemons[i]);
            found=i;
            break;
        }
    }

    if (found==-1){
        colorText("red","\n**********Pokemon not found**********\n");
    }
        colorText("green","\nPress any key to continue...");
        getch();
}

//print achivement
void printAchievement(){
    FILE *file = fopen("./database/achievement.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        printf("Press any key to continue..");
        getch();
        return;
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file);

    Achievement achievements[100];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        Achievement a;
        char *token;

        token = strtok(line, ",");
        strncpy(a.name, token, MAX_NAME_LENGTH);

        token = strtok(NULL, ",");
        strncpy(a.description, token, MAX_LINE_LENGTH);

        achievements[count++] = a;
    }

    fclose(file);
    printf("--------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        // printf("%-15s \n %-80s |\n", achievements[i].name, achievements[i].description);
        colorText("bright green", achievements[i].name);
        printf("\n");
        colorText("white", achievements[i].description);
        printf("\n");
        printf("--------------------------------------------------------------------------------------------------------\n");
    }
}

// void add_pokemon_from_file(char* file_name, struct Graph* graph) {
//     FILE* file = fopen("./database/pokedex_all.txt", "r");
//     if (file == NULL) {
//         printf("Cannot open file %s\n", file_name);
//         return;
//     }

void printPokemonType(char *type, int total_data){
    FILE *file = fopen("./database/pokedex_all.txt", "r");
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
    int start = 0;
    int muncul = 0;
    int sebelumnya;
    int end;
    // while(1){
        // system("cls");
        printf("--------------------------------------------------------------------------------------------------------\n");
        colorText("magenta","| Index | Name            | Type 1          | Type 2          | HP   | Atk  | Def  | SpA  | SpD  | Spe |\n");
        printf("--------------------------------------------------------------------------------------------------------\n");
        int indexStart[100];
        int curr = 0;
        bool first = true;
        for (int i = 0; i<count; i++){
        
            if(strcmp(pokemons[i].type1, type) == 0 || strcmp(pokemons[i].type2, type) == 0){
                if(first) {
                    // printf("\n\nIndexStart : %d\n\n", i);
                    indexStart[curr] = i;
                    curr++;
                    first = false;
                }
                printPokemon(pokemons[i]);
                muncul++;
                if(muncul == 1){
                    sebelumnya = start; // mau nyimpan apa yang pertama kali di print halaman sebelumnya
                } // tiap 20 = getch -> cls = maju
            }
            if(muncul == 20){
                first = true;
                char input = ' ';
                input =  _getch();
                if(input == 'a' || input == 'A') { 
                    i = indexStart[curr - 2] - 1;
                    curr-=2;
                }
                else if(input =='B' || input == 'b' ){
                    return;
                }
                muncul = 0;
                system("cls");
                printf("================================================================\n");
                printf("Main > Pokemon > View Pokedex > ");
                colorText("yellow", "View by Type");
                printf("\n");
                printf("================================================================\n");
                printf("                     << %s >>                        \n", type);
                colorText("red", "\n````````````````````````````````````````````````````````````````\n");
                colorText("red","Press 'a' | '<--' or 'd' | '-->' to iterate     \n" );
                colorText("red","Press 'b' to back                                               \n");
                colorText("red", "````````````````````````````````````````````````````````````````\n\n");
                printf("--------------------------------------------------------------------------------------------------------\n");
                colorText("magenta","| Index | Name            | Type 1          | Type 2          | HP   | Atk  | Def  | SpA  | SpD  | Spe |\n");
                printf("--------------------------------------------------------------------------------------------------------\n");
            }
        }
    }

int countLinesInFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        return -1;
    }

    int count = 0;
    char c;

    // Increment count for each newline character
    for (c = getc(file); c != EOF; c = getc(file)) {
        if (c == '\n') {
            count++;
        }
    }
    fclose(file);

    return count;
}

void printAllData(char file_name[], int start, int max_data, int total_data){
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        printf("Press any key to continue..");
        getch();
        return;
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); 

    int tot_data= countLinesInFile(file_name);
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

    if(count < max_data){
        max_data = count;
    }
    
    for (int i = start; i < max_data; i++) {
        if( i % 20 == 0){
            printf("--------------------------------------------------------------------------------------------------------\n");
            colorText("yellow","| Index | Name            | Type 1          | Type 2          | HP   | Atk  | Def  | SpA  | SpD  | Spe |\n");
            printf("--------------------------------------------------------------------------------------------------------\n");
            //jika sudah mencapai line akhir data lanjutkan cetak dari pekedex_gen%d.txt selanjutnya
        }
        
        printPokemon(pokemons[i]);

    }
}

void printData(char file_name[], int total_data, int gen) {
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
    
    // printf("--------------------------------------------------------------------------------------------------------\n");
    // colorText("bright green","| Index | Name            | Type 1          | Type 2          | HP   | Atk  | Def  | SpA  | SpD  | Spe |\n");
    // printf("--------------------------------------------------------------------------------------------------------\n");
    // for (int i = 0; i < count; i++) {
    //     if(i%20==0){
    //         // system("cls");
    //         printf("--------------------------------------------------------------------------------------------------------\n");
    //         colorText("bright green","| Index | Name            | Type 1          | Type 2          | HP   | Atk  | Def  | SpA  | SpD  | Spe |\n");
    //         printf("--------------------------------------------------------------------------------------------------------\n");
    //     }
    //     printPokemon(pokemons[i]);
    // }

    // printf("Press any key to continue..");
    // getch();

    int start_index = 0;
    while (1) {
        system("cls");
        viewGen(gen);
        colorText("red", "\n````````````````````````````````````````````````````````````````\n");
        colorText("red","Press 'a' | '<--' or 'd' | '-->' to iterate through generation    \n" );
        colorText("red","Press 'b' to back                                               \n");
        colorText("red", "````````````````````````````````````````````````````````````````\n\n");
        printf("--------------------------------------------------------------------------------------------------------\n");
        colorText("bright green","| Index | Name            | Type 1          | Type 2          | HP   | Atk  | Def  | SpA  | SpD  | Spe |\n");
        printf("--------------------------------------------------------------------------------------------------------\n");
        for (int i = start_index; i < start_index + 20 && i < count; i++) {
            printPokemon(pokemons[i]);
        }

        // printf("\nPress 'a' to go back, 'd' to go forward, or any other key to exit..\n");
        // char ch = getch();
        char input = ' ';
        input = _getch();
        switch (input) {
            case 'a':
                if (start_index >= 20) { // jika start_index >= 20, maka bisa mundur
                    start_index -= 20;
                }
                break;
            case 'd':
                if (start_index + 20 < count) { // jika +20 dari start_index < count, maka bisa maju
                    start_index += 20;
                }
                break;
            case 'b':
            case 'B':
                return;
                break;
            default: ;
                int a = input;
                switch (a) {
                    case 75: //left
                        if (start_index >= 20) { // jika start_index >= 20, maka bisa mundur
                        start_index -= 20;
                        break;
                    }
                    case 77: //right
                        if (start_index + 20 < count) { // jika +20 dari start_index < count, maka bisa maju
                        start_index += 20;
                        break;
                    }
                }
                break;
        }
    }
}

void printPokemon(Pokemon p) {
    //jika number = 0, maka tidak perlu di print (tidak print 0 dan None)
    if(p.number == 0) {
        return;
    }
    printf("| %-5d | %-15s | %-15s | %-15s | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d|\n",
        p.number, p.name, p.type1, p.type2[0] == '\0' ? "None" : p.type2, p.hp, p.attack, p.defense, p.sp_attack, p.sp_defense, p.speed);
}


void printAllMoveData(char file_name[], int start, int max_data, int total_data){
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        printf("Press any key to continue..");
        getch();
        return;
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); 

    Move moves[total_data];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        Move m;
        char *token;

        token = strtok(line, ",");
        m.number = atoi(token);

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
        strncpy(m.gen, token, MAX_TYPE_LENGTH);

        moves[count++] = m;
    }

    fclose(file);
    
    //printf("| Index | Name            | Type 1          | Type 2          | HP   | Atk  | Def  | SpA  | SpD  | Spe |\n");
    for (int i = start; i < max_data && i < total_data; i++) {
        if( i % 20 == 0){
            // system("cls");
            // printf("Press any key to continue..\n");
            // getch();
            printf("----------------------------------------------------------------------------------------------------------\n");
            colorText("cyan","| Index | Name                             | Type            | Category        | PP   | Power | Accuracy |\n");
            printf("----------------------------------------------------------------------------------------------------------\n");
            //jika sudah mencapai line akhir data lanjutkan cetak dari pekedex_gen%d.txt selanjutnya
        }
        
        printMove(moves[i]);

    }

}

void printMove(Move m) {
    //jika number = 0, maka tidak perlu di print (tidak print 0 dan None)
    if(m.number == 0) {
        return;
    }
    printf("| %-5d | %-32s | %-15s | %-15s | %-4d | %-5d | %-8d |\n",
        m.number, m.name, m.type, m.category, m.pp, m.power, m.accuracy);
    // printf("----------------------------------------------------------------------------------------------------------\n");
}

void addData(Pokemon pokemons[]) {
    FILE *file = fopen("./database/pokedex_all.txt", "r");
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

struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}

void add_edges_from_file(char* file_name, struct Graph* graph) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Cannot open file %s\n", file_name);
        return;
    }

    int src, dest; //node asal, node tujuan
    char *token;
    char line[MAX_LINE_LENGTH];
    while(fgets(line, sizeof(line), file) != NULL){
        token = strtok(line, ",");
        src = atoi(token);

        token = strtok(NULL, ",");
        dest = atoi(token);
        addEdge(graph, src, dest);
    }
    fclose(file);
}


void addEdge(struct Graph* graph, int src, int dest) {
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // newNode = newAdjListNode(src);
    // newNode->next = graph->array[dest].head;
    // graph->array[dest].head = newNode;
}


void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %03d\n head ", v);
        while (pCrawl) {
            printf("-> %03d", pCrawl->dest);
            printNext(graph, pCrawl->dest, v);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

void printNext(struct Graph* graph, int src, int start){
    struct AdjListNode* pCrawl = graph->array[src].head;
    if(pCrawl != NULL){
        if(start == pCrawl -> dest) {
            return;
        }
        printf("-> ");
        searchPokemon(pCrawl->dest+1);
        // printf("-> %03d", pCrawl->dest);
        printNext(graph, pCrawl->dest, start);
        // printf("\n");
    }

};

void printEvolution(struct Graph* graph, int src, int start, Pokemon pokemons[]){
    struct AdjListNode* pCrawl = graph->array[src].head;
    if(pCrawl != NULL){
        if(start == pCrawl -> dest) return;
        printf(" %s ->", pokemons[pCrawl->dest].name);
        // if(graph->array[p])
        printEvolution(graph, pCrawl->dest, start, pokemons);
    }
};

void searchPokemon(int Index){
    FILE *file = fopen("./database/pokedex_all.txt", "r");
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
        if(count == Index) {
            printf("%-10s ", p.name);
            break;
        }
    }
    fclose(file);
}