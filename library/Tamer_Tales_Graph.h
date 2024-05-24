struct AdjListNode* newAdjListNode(int dest);


struct Graph* createGraph(int V);


void addEdge(struct Graph* graph, int src, int dest); 
/*
Connect from source Node to destination Node (only one way)
Example:
    addEdge(1,2), 1 can go to 2, but not vice versa
*/

void printGraph(struct Graph* graph);
/*
Display all graph nodes
*/

void printNext(struct Graph* graph, int src, int start);
/*
Display the avalaible connect from source, then continue on recursively
    Example:
    addEdge(1,2)
    printNext(1), will display 2

    addEdge(2,3)
    printNext(1), will display 2 then 3
*/ 
