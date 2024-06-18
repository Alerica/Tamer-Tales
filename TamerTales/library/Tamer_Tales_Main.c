/*
~~ Tamer Tales Main ~~
Main Program

Update Log :
23 May 2024 by Alexander Ricky B.
    Create Tamer_Tales_Main
28 May - Alexander Ricky B.
    move opening introduction into Tamer_Tales_Display.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
// #include "Tamer_Tales_Graph.h"
#include "Tamer_Tales_FileProcessing.h"
#include "Tamer_Tales_Display.h"

int main() {
    system("cls");
    int a = -1;
    while(a != 6) {
        a = menuPokemon();
        menuPokemonNavigation(a);
    }
    printf("Return with %d", a);
}

    // int V = 5;
    // struct Graph* graph = createGraph(V);
    // addEdge(graph, 1, 2);
    // addEdge(graph, 2, 3);
    // printGraph(graph);