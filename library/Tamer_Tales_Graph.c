/*
~~ Tamer Tales Graph ~~
Contain all function for graph (Adjency List)

Update Log :
21 May 2024 by Alexander Ricky B. 
    - Create adjency list function
22 May 2024 by Alexander Ricky B.  
    - Impove adjency list function (display the list recursively)
    - Fix infinite list bug
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>

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
void printNext(struct Graph* graph, int src, int start); 

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

void addEdge(struct Graph* graph, int src, int dest) {
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
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
        printf("-> %03d", pCrawl->dest);
        printNext(graph, pCrawl->dest, start);
    }
};
