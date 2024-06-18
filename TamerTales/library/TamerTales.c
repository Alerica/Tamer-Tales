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
void addData(Pokemon pokemons[]);
void printNext(struct Graph* graph, int src, int start);
void printEvolution(struct Graph* graph, int src, int start, Pokemon pokemons[]);
void searchPokemon(int index);

int main() {
    int V = 1030;
    struct Graph* graph = createGraph(V);
    char file_name[MAX_LINE_LENGTH];
    system("cls");
    add_edges_from_file("./database/evolution_gen1.txt", graph);
    printf("Data evolusi 1 masuk\n");
    add_edges_from_file("./database/evolution_gen2.txt", graph);
    printf("Data evolusi 2 masuk\n");
    add_edges_from_file("./database/evolution_gen3.txt", graph);
    printf("Data evolusi 3 masuk\n");
    add_edges_from_file("./database/evolution_gen4.txt", graph);
    printf("Data evolusi 4 masuk\n");
    add_edges_from_file("./database/evolution_gen5.txt", graph);
    printf("Data evolusi 5 masuk\n");
    add_edges_from_file("./database/evolution_gen6.txt", graph);
    printf("Data evolusi 6 masuk\n");
    add_edges_from_file("./database/evolution_gen7.txt", graph);
    printf("Data evolusi 7 masuk\n");
    add_edges_from_file("./database/evolution_gen8.txt", graph);
    printf("Data evolusi 8 masuk\n");
    add_edges_from_file("./database/evolution_gen9.txt", graph);
    printf("Data evolusi 9 masuk\n");

    printNext(graph, 1, 1);
    printf("\n");
    printNext(graph, 152, 152);
    printf("\n");
    printNext(graph, 252, 252);
    printf("\n");
    printNext(graph, 906, 906);





    return 0;
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
        if(start == pCrawl -> dest) return;
        searchPokemon(pCrawl->dest+1);
        // printf("-> %03d", pCrawl->dest);
        printNext(graph, pCrawl->dest, start);
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
            printf("-> %s ", p.name);
            break;
        }
    }
    fclose(file);
}

// void displayMenuPokemon(Pokemon pokemons[], struct Graph* graph){
//     system("cls");
//     int menu;
//     printf("=======================\n");
//     printf("Main > Pokemon\n");
//     printf("=======================\n");
//     printf("1. Add Pokemon\n");
//     printf("2. View Pokedex\n");
//     printf("3. Search Pokemon\n");
//     printf("4. Update Pokemon\n");
//     printf("5. Delete Pokemon\n");
//     printf("6. Exit\n");

//     do {
//         printf(">> ");
//         scanf("%d", &menu);
//         switch(menu){
//             case 1:
//                 addPokemon();
//                 break;
//             case 2:
//                 printData();
//                 break;
//             case 3:
//                 searchPokemon(pokemons, graph);
//                 break;
//             case 4:
//                 updatePokemon();
//                 break;
//             case 5:
//                 deletePokemon();
//                 break;
//             case 6:
//                 break;
//             default:
//                 printf("Invalid input\n");
//                 break;
//         }  
//     } while(menu < 1 || menu > 6);
    
// };

// void addPokemon(){
//     system("cls");
//     printf("=======================\n");
//     printf("Main > Pokemon > Add\n");
//     printf("=======================\n");
//     // add Index,Name,Type 1,Type 2,HP,Attack,Defense,Sp.Attack,Sp.Defense,Speed
//     printf("Enter Pokemon Index: ");
    
// }
// void searchPokemon(Pokemon pokemons[], struct Graph* graph){
   
//     int menu;
//     system("cls");
//     printf("=======================\n");
//     printf("Main > Pokemon > Search\n");
//     printf("=======================\n");
//     printf("Enter Pokemon name: ");
//     char name[15];
//     scanf("%s", name);
//     printf("Pokemon index of %s is %d", name, pokemonSearch(pokemons, name));
//     printEvolution(graph, pokemonSearch(pokemons,name), pokemonSearch(pokemons,name), pokemons);

//     printf("\n\nPress any key to continue..");
//     getch();
// }

// /* Tambahan Ricky */
// int pokemonSearch(Pokemon pokemons[], char name[]){ // Input name, return Positition
//     for(int i; i < 151; i++ ) { // Use total Pokemon
//         // printf("Pokemons %s \n", pokemons[i].name); // Display for debugging
//         if(strcmp(pokemons[i].name,name) == 0) return i;
//     }
//     return 999;
// } 

// void updatePokemon(){
//     system("cls");
//     printf("=======================\n");
//     printf("Main > Pokemon > Update\n");
//     printf("=======================\n");
//     printf("1. Add Pokemon\n");
//     printf("2. View Pokedex\n");
//     printf("3. Search Pokemon\n");
//     printf("4. Update Pokemon\n");
//     printf("5. Delete Pokemon\n");
//     printf("6. Exit\n");
// }

// void deletePokemon(){
//     system("cls");
//     printf("=======================\n");
//     printf("Main > Pokemon > Delete\n");
//     printf("=======================\n");
//     printf("1. Add Pokemon\n");
//     printf("2. View Pokedex\n");
//     printf("3. Search Pokemon\n");
//     printf("4. Update Pokemon\n");
//     printf("5. Delete Pokemon\n");
//     printf("6. Exit\n");
// }