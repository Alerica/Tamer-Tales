/*
~~ Tamer Tales Main ~~
Main Program

Update Log :
23 Mei 2024 by Ricky
    Create Tamer_Tales_Main
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include "Tamer_Tales_Graph.h"
#include "Tamer_Tales_FileProcessing.h"
#include "Tamer_Tales_Display.h"

int main() {
    printf("================================================================\n");
    printf("                            Tamer Tales                         \n");
    printf("================================================================\n");
    printf("                             Created by                         \n");
    printf("                  2702224950 - Alexander Ricky B.               \n");
    printf("                  2702236925 - Grace Birgitta H.                \n");
    printf("                  2702343914 - Rafly Adha Prathama              \n");
    printf("                                                                \n");
    printf("                     Press Enter To continue...                   ");
    getch();
    // int V = 5;
    // struct Graph* graph = createGraph(V);
    // addEdge(graph, 1, 2);
    // addEdge(graph, 2, 3);
    // printGraph(graph);
    int a = -1;
    while(a != 6) {
        a = menuPokemon();
        menuPokemonNavigation(a);
    }
    printf("Return with %d", a);
    // char file_name[] = "pokedex_gen1.txt";
    // printData(file_name, 200);
    // printf("Hello World");
}