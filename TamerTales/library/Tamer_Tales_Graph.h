// struct AdjListNode* newAdjListNode(int dest);


// struct Graph* createGraph(int V);


// void addEdge(struct Graph* graph, int src, int dest); 
// /*
// Connect from source Node to destination Node (only one way)
// Example:
//     addEdge(1,2), 1 can go to 2, but not vice versa
// */

// void printGraph(struct Graph* graph);
// /*
// Display all graph nodes
// */

// void printNext(struct Graph* graph, int src, int start);
/*
Display the avalaible connect from source, then continue on recursively
    Example:
    addEdge(1,2)
    printNext(1), will display 2

    addEdge(2,3)
    printNext(1), will display 2 then 3
*/ 

// typedef struct {
//     int number;
//     char name[50];
//     char type1[20];
//     char type2[20];
//     int hp;
//     int attack;
//     int defense;
//     int sp_attack;
//     int sp_defense;
//     int speed;
// } Pokemon;

// struct AdjListNode* newAdjListNode(int dest);
// struct Graph* createGraph(int V);
// void addEdge(struct Graph* graph, int src, int dest); // Connect from source Node to destination Node
// void printGraph(struct Graph* graph); // Display Graph
// // void add_edges_from_file(char* file_name, struct Graph* graph);
// // void addData(Pokemon pokemons[]);
// void printNext(struct Graph* graph, int src, int start);
// void printEvolution(struct Graph* graph, int src, int start, Pokemon pokemons[]);

// #define MAX_LINE_LENGTH 256
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