// /*
// ~~ Tamer Tales Graph ~~
// Contain all function for graph (Adjency List)

// Update Log :
// 21 May 2024 by Alexander Ricky B. 
//     - Create adjency list function
// 22 May 2024 by Alexander Ricky B.  
//     - Impove adjency list function (display the list recursively)
//     - Fix infinite list bug
// */

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <conio.h>
// #include <string.h>

// // struct AdjListNode {
// //     int dest;
// //     struct AdjListNode* next;
// // };

// // struct AdjList {
// //     struct AdjListNode* head;
// // };

// // struct Graph {
// //     int V;
// //     struct AdjList* array;
// // };

// // struct AdjListNode* newAdjListNode(int dest);
// // struct Graph* createGraph(int V);
// // void addEdge(struct Graph* graph, int src, int dest); // Connect from source Node to destination Node
// // void printGraph(struct Graph* graph); // Display Graph
// // void printNext(struct Graph* graph, int src, int start); 

// // struct AdjListNode* newAdjListNode(int dest) {
// //     struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
// //     newNode->dest = dest;
// //     newNode->next = NULL;
// //     return newNode;
// // }

// // struct Graph* createGraph(int V) {
// //     struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
// //     graph->V = V;

// //     graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

// //     for (int i = 0; i < V; ++i) {
// //         graph->array[i].head = NULL;
// //     }

// //     return graph;
// // }

// // void addEdge(struct Graph* graph, int src, int dest) {
// //     struct AdjListNode* newNode = newAdjListNode(dest);
// //     newNode->next = graph->array[src].head;
// //     graph->array[src].head = newNode;
// // }


// // void printGraph(struct Graph* graph) {
// //     for (int v = 0; v < graph->V; ++v) {
// //         struct AdjListNode* pCrawl = graph->array[v].head;
// //         printf("\n Adjacency list of vertex %03d\n head ", v);
// //         while (pCrawl) {
// //             printf("-> %03d", pCrawl->dest);
// //             printNext(graph, pCrawl->dest, v);
// //             pCrawl = pCrawl->next;
// //         }
// //         printf("\n");
// //     }
// // }

// // void printNext(struct Graph* graph, int src, int start){
// //     struct AdjListNode* pCrawl = graph->array[src].head;
// //     if(pCrawl != NULL){
// //         if(start == pCrawl -> dest) return;
// //         printf("-> %03d", pCrawl->dest);
// //         printNext(graph, pCrawl->dest, start);
// //     }
// // };

// #define MAX_NAME_LENGTH 50
// #define MAX_TYPE_LENGTH 20


// typedef struct {
//     int number;
//     char name[MAX_NAME_LENGTH];
//     char type1[MAX_TYPE_LENGTH];
//     char type2[MAX_TYPE_LENGTH];
//     int hp;
//     int attack;
//     int defense;
//     int sp_attack;
//     int sp_defense;
//     int speed;
// } Pokemon;

// struct AdjListNode {
//     int dest;
//     struct AdjListNode* next;
// };

// struct AdjList {
//     struct AdjListNode* head;
// };

// struct Graph {
//     int V;
//     struct AdjList* array;
// };


// struct AdjListNode* newAdjListNode(int dest);
// struct Graph* createGraph(int V);
// void addEdge(struct Graph* graph, int src, int dest); // Connect from source Node to destination Node
// void printGraph(struct Graph* graph); // Display Graph
// // void add_edges_from_file(char* file_name, struct Graph* graph);
// // void addData(Pokemon pokemons[]);
// void printNext(struct Graph* graph, int src, int start);
// void printEvolution(struct Graph* graph, int src, int start, Pokemon pokemons[]);
// // void searchPokemon(int index);

// struct AdjListNode* newAdjListNode(int dest) {
//     struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
//     newNode->dest = dest;
//     newNode->next = NULL;
//     return newNode;
// }

// struct Graph* createGraph(int V) {
//     struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
//     graph->V = V;

//     graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

//     for (int i = 0; i < V; ++i) {
//         graph->array[i].head = NULL;
//     }

//     return graph;
// }

// void addEdge(struct Graph* graph, int src, int dest) {
//     struct AdjListNode* newNode = newAdjListNode(dest);
//     newNode->next = graph->array[src].head;
//     graph->array[src].head = newNode;
// }


// void printGraph(struct Graph* graph) {
//     for (int v = 0; v < graph->V; ++v) {
//         struct AdjListNode* pCrawl = graph->array[v].head;
//         printf("\n Adjacency list of vertex %03d\n head ", v);
//         while (pCrawl) {
//             printf("-> %03d", pCrawl->dest);
//             printNext(graph, pCrawl->dest, v);
//             pCrawl = pCrawl->next;
//         }
//         printf("\n");
//     }
// }

// void printNext(struct Graph* graph, int src, int start){
//     struct AdjListNode* pCrawl = graph->array[src].head;
//     if(pCrawl != NULL){
//         if(start == pCrawl -> dest) return;
//         printf("-> %03d", pCrawl->dest);
//         printNext(graph, pCrawl->dest, start);
//     }
// };

// void printEvolution(struct Graph* graph, int src, int start, Pokemon pokemons[]){
//     struct AdjListNode* pCrawl = graph->array[src].head;
//     if(pCrawl != NULL){
//         if(start == pCrawl -> dest) return;
//         printf(" %s ->", pokemons[pCrawl->dest].name);
//         // if(graph->array[p])
//         printEvolution(graph, pCrawl->dest, start, pokemons);
//     }
// };

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

// int main() {
//     int V = 1030;
//     struct Graph* graph = createGraph(V);
//     char file_name[MAX_LINE_LENGTH];
//     system("cls");
//     add_edges_from_file("./database/evolution_gen1.txt", graph);
//     add_edges_from_file("./database/evolution_gen2.txt", graph);
//     add_edges_from_file("./database/evolution_gen3.txt", graph);
//     add_edges_from_file("./database/evolution_gen4.txt", graph);
//     add_edges_from_file("./database/evolution_gen5.txt", graph);
//     add_edges_from_file("./database/evolution_gen6.txt", graph);
//     add_edges_from_file("./database/evolution_gen7.txt", graph);
//     add_edges_from_file("./database/evolution_gen8.txt", graph);
//     add_edges_from_file("./database/evolution_gen9.txt", graph);

//     // printNext(graph, 1, 1);
//     // printf("\n");
//     // printNext(graph, 152, 152);
//     // printf("\n");
//     // printNext(graph, 252, 252);
//     // printf("\n");
//     // printNext(graph, 906, 906);





//     return 0;
// }

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