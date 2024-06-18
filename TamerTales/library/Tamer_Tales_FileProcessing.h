/*
28 may 2024 by Rafly Adha Prathama
    - Add function printAllMoveData
    - Add function printMove
    - Add new struct Move
*/
#define MAX_LINE_LENGTH 256
#define MAX_NAME_LENGTH 50
#define MAX_TYPE_LENGTH 20

// struct Graph {
//     int V;
//     struct AdjList* array;
// };

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
} Move;

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


void printData(char file_name[], int total_data, int gen);
void printPokemon(Pokemon p);
void addData(Pokemon pokemons[]);

void printAllData(char *file_name, int start, int max_data, int total_data);
void printMove(Move m);
void printAllMoveData(char *file_name, int start, int max_data, int total_data);

void printPokemonType(char *type, int total_data);
// void add_edges_from_file(char* file_name, struct Graph* graph);

void printSearchPokemon(char *name, int total_data);
void printAchievement(char *file_name, int total_data);