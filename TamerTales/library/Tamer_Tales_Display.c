/*
~~ Tamer Tales Display ~~
Contain all function for user Interface

Update Log :
23 May 2024 by Alexander Ricky B.
    - Seperate display function from main
    - Improve the interface
    - Improve user validation, now user can only use 'a','w','s','d', or any specific input
    - Add function :
        int menuPokemon();
        void menuPokemonDisplay(int current);
        void menuPokemonNavigation(int nav);
        int menuViewPokemon();
        void menuViewPokemonDisplay(int current);
        void menuViewPokemonNavigation(int nav);
24 May
    - Add function :
        int viewPokemonGeneration();
        void viewPokemonGenerationDisplay(int current);
        void viewPokemonGenerationNavigation(int nav);

25 May - Grace Birgitta H.
    - Add function :
        int viewPokemonType();
        void viewPokemonTypeDisplay(int current);
        void viewPokemonTypeNavigation(int nav); --> file tersendiri(pokedex_type.txt)
27 May - Grace Birgitta H.
    - Add function
        int viewAllPokemon();
        void viewAllPokemonDisplay(int current);
        void viewAllPokemonNavigation(int nav, int page);
        void viewAll_Navigation(int nav, int start, int max_data);
        printAllData(char file_name[], int start, int max_data, int total_data);

28 May - Alexander Ricky B.
    - Minor Change
        fix memory overflow, change size for file name from 20 > 30
        fix implicit declaration
        fix display error ( can`t iterate back ), change count to higher number

28 May - Rafly Adha Prathama
    - Add Function
        int viewPokemonMoveList();
        void viewAllMoveDisplay(int current);

29 May - Grace Birgitta H.
    - Update function:
            viewPokemonMoveList() 
            viewAllMoveDisplay(int current)
            viewAllMoveNavigation(int nav)
            viewPokemonTypeNavigation(int nav)
            viewPokemonGenerationNavigation(int nav)
    - move database folder to library
    - Add Function : 
            viewTypeMenu(char *type, char *file_name);
    - Improve the interface
    - Improve user validation, 'a', 'b', 'd' only without pressing enter to see data
30 May - Grace Birgitta H.
    - fix 'b' to back in viewPokemonMoveList() and viewPokemonType()
    - delete unused txt(type) file
31 May- Grace Birgitta H.
    - improve the interface (add color) 
            - \033[0;32m for green
            - \033[0;33m for yellow
            - \033[0m for reset
            - \033[1;37m for bold white
1 June-Grace Birgitta H.
    - improve the interface (change using color library)
    - change menuViewPokemonDisplay() : 
            - add pokemon -> view movelist pokemon
            - add view evolution
            - add view quest
    - move function movelist in view pokedex to main menu (view movelist)
4 June-Grace Birgitta H.
    - add function :
            - viewPokemonEvolutionNavigation(struct Graph* graph)
            - viewPokemonEvolutionDisplay(struct Graph *graph, int current)
            - viewPokemonEvolution(struct Graph* graph)
            - searchPokemon()
            - searchPokemonNavigation(int nav)
            - searchValidationDisplay(int current)
            - searchValidation()
            - viewAchievement()
5 June-Grace Birgitta H.
    - fix bug in viewPokemonEvolutionDisplay()
    - fix bug in viewPokemonEvolutionNavigation()
    - move graph.c code to display.c
7 June 2024 by Grace Birgitta H.
    - update Navigation system : using arrow key
    - update movelist to movelistp.txt
    - update UI void viewPokemonEvolutionDisplay(struct Graph *graph, int current);
11 June 2024 by Grace Birgitta H.
    - fix bug in viewPokemonEvolutionNavigation()
12 June 2024 by Grace Birgitta H.
    - Update searchValidation() : add 'b' to back
14 June 2024 by Grace Birgitta H.
    - add function : 
            - void viewPokemonGenerationNavigation(int nav);
16 June 2024 by Grace Birgitta H.
    - add function : 
            - void viewGen(int gen);
            - int menuGenPokemon();
    - update function : 
            - void viewPokemonGenerationDisplay(int current);
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include "Tamer_Tales_FileProcessing.h"
#include "Tamer_Tales_UI.h"
// #include "Tamer_Tales_Graph.h"


int menuPokemon();
void menuPokemonDisplay(int current);
void menuPokemonNavigation(int nav);

int menuViewPokemon();
void menuViewPokemonDisplay(int current);
void menuViewPokemonNavigation(int nav);

//View Pokemon Generation
// int viewPokemonGeneration();
void viewPokemonGenerationDisplay(int current);
void viewGen(int gen); //new
void viewPokemonGenerationNavigation(int nav);
int menuGenPokemon(); //new

//view pokemon type
int viewPokemonType();
void viewPokemonTypeDisplay(int current);
// void viewPokemonTypeNavigation(int nav);
void viewTypeMenu(char *type);


//view all pokemon
int viewAllPokemon();
void viewAllPokemonDisplay(int current);
void viewAllPokemonNavigation(int nav);

//view all move
int viewPokemonMoveList();
void viewAllMoveDisplay(int current);

// void viewAll_Navigation(int nav, int start, int max_data);
// void viewAll_Navigation(int page);
int viewPokemonEvolutionNavigation(struct Graph* graph);
void viewPokemonEvolutionDisplay(struct Graph *graph, int current);

void SearchPokemonMenu();
void searchValidationDisplay(int current);
int searchValidation();
void searchPokemonNavigation(int nav);

void viewAchievement();

void menuPokemonNavigation(int nav) {
    struct Graph* graph = createGraph(1030);
    switch (nav) {
        case 1: ;
            // search pokemon
            int menu1 = -1;
            while (menu1 !=  2)
            {
                menu1 = searchValidation();
                searchPokemonNavigation(menu1);
            }
            break;
        case 2: ;
            int menu2 = -1;
            while (menu2 !=  4)
            {
                menu2 = menuViewPokemon();
                menuViewPokemonNavigation(menu2);
            }
            break;
        case 3:
            // view evolution
            viewPokemonEvolutionNavigation(graph);
            break;
        case 4:
            // view move list 
                viewPokemonMoveList();

            break;
        case 5:
            // view achievement
            viewAchievement();
            break;
        case 6:
            exit(1);
            break;
    }
}

//saat user press "enter" maka akan return nilai dari menu yang dipilih
int menuPokemon() {
    char input = ' ';
    int count = 600;
    while (true) {
        switch (input) {
            case 'S':
            case 's':
                count++;
                break;
            case 'W':
            case 'w':
                count--;
                break;
            case '\r': // press 'enter'
                return count % 6 + 1;
            default: ;
                int a = input;
                switch (a) {
                case 72: //up
                    count--;
                    break;
                case 80: //down
                    count++;
                    break;
                }
                break;
        }
        menuPokemonDisplay(count);
        input = _getch();  // Read a single character without pressing Enter
    }
}

//display main menu
void menuPokemonDisplay(int current) {
    int atMenu = current % 6 + 1;
    switch(atMenu) {
        case 1:
            system("cls");
            printf("================================================================\n");
            printf("Main > ");
            colorText("yellow", "Pokemon");
            printf("\n");
            printf("================================================================\n");
            printf("  "); colorTextunderline("green", "Search Pokemon\n");
            printf("   View Pokedex\n");
            printf("   View Evolution\n");
            printf("   View Movelist\n");
            printf("   View Achievement\n");
            printf("   Exit\n");
            break;
        case 2:
            system("cls");
            printf("================================================================\n");
            printf("Main > ");
            colorText("yellow", "Pokemon");
            printf("\n");
            printf("================================================================\n");
            printf("   Search Pokemon\n");
            printf("  "); colorTextunderline("green", "View Pokedex\n");
            printf("   View Evolution\n");
            printf("   View Movelist\n");
            printf("   View Achievement\n");
            printf("   Exit\n");
            break;
        case 3:
            system("cls");
            printf("================================================================\n");
            printf("Main > ");
            colorText("yellow", "Pokemon");
            printf("\n");
            printf("================================================================\n");
            printf("   Search Pokemon\n");
            printf("   View Pokedex\n");
            printf("  "); colorTextunderline("green", "View Evolution\n");
            printf("   View Movelist\n");
            printf("   View Achievement\n");
            printf("   Exit\n");
            break;
        case 4:
            system("cls");
            printf("================================================================\n");
            printf("Main > ");
            colorText("yellow", "Pokemon");
            printf("\n");
            printf("================================================================\n");
            printf("   Search Pokemon\n");
            printf("   View Pokedex\n");
            printf("   View Evolution\n");
            printf("  "); colorTextunderline("green", "View Movelist\n");
            printf("   View Achievement\n");
            printf("   Exit\n");
            break;
        case 5:
            system("cls");
            printf("================================================================\n");
            printf("Main > ");
            colorText("yellow", "Pokemon");
            printf("\n");
            printf("================================================================\n");
            printf("   Search Pokemon\n");
            printf("   View Pokedex\n");
            printf("   View Evolution\n");
            printf("   View Movelist\n");
            printf("  "); colorTextunderline("green", "View Achievement\n");
            printf("   Exit\n");
            break;
        case 6:
            system("cls");
            printf("================================================================\n");
            printf("Main > ");
            colorText("yellow", "Pokemon");
            printf("\n");
            printf("================================================================\n");
            printf("   Search Pokemon\n");
            printf("   View Pokedex\n");
            printf("   View Evolution\n");
            printf("   View Movelist\n");
            printf("   View Achievement\n");
            printf("  "); colorTextunderline("red", "Exit\n");
            break;
    }
}

void SearchPokemonMenu(){
    system("cls");
    char name[50];
    printf("================================================================\n");
    printf("Main > Pokemon > ");
    colorText("yellow", "Search Pokemon");
    printf("\n");
    printf("================================================================\n");
    //minta inputan user
    printf("Enter Pokemon Name : ");
    scanf(" %[^\n]", name);
    printSearchPokemon(name, 1030);
}


void searchValidationDisplay(int current){
    int atMenu = current % 2 + 1;
    switch(atMenu){
        case 1:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > Search Pokemon\n");
            printf("================================================================\n");
            printf("  "); colorTextunderline("green", "Search\n");
            printf("   Back\n");
            break;
        case 2:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > Search Pokemon\n");
            printf("================================================================\n");
            printf("   Search\n");
            printf("  "); colorTextunderline("red", "Back\n");
            break;
    }
}

void searchPokemonNavigation(int nav){
    switch(nav){
        case 1:
            //search
            SearchPokemonMenu();
            break;
        case 2: 
            //back
            return;
            break;
    }
}


int searchValidation(){
    char input = ' ';
    int count = 200;
    while (true) {
        searchValidationDisplay(count);
        input = _getch();  // Read a single character without pressing Enter
        switch (input) {
            case 'S':
            case 's':
                count--;
                break;
            case 'W':
            case 'w':
                count++;
                break;
            case 'B':
            case 'b':
                return 2; // back to menu
                break;
            case '\r': // press 'enter'
                return count % 2 + 1;
            default: ;
                int a = input;
                switch (a) {
                case 72: //up
                    count--;
                    break;
                case 80: //down
                    count++;
                    break;
                }
                break;
        }
    }
}

//fungsi view pokedex 
int menuViewPokemon() {
    char input = ' ';
    int count = 400;
    menuViewPokemonDisplay(count);
    while (true) {
        input = _getch();  // Read a single character without pressing Enter
        switch (input) {
            case 'S':
            case 's':
                count++;
                break;
            case 'W':
            case 'w':
                count--;
                break;
            case 'B':
            case 'b':
                return 0; // back to menu
                break;
            case '\r': // press 'enter'
                return count % 4 + 1;
                break;
            default: ;
                int a = input;
                switch (a) {
                case 72: //up
                    count--;
                    break;
                case 80: //down
                    count++;
                    break;
                case 'B':
                case 'b':
                    return 0; // back to menu
                    break;
                }
            break;
        }
        menuViewPokemonDisplay(count);
    }
}

void menuViewPokemonNavigation(int nav) {
    switch(nav){

        case 1: ;
            int menu2=-1;
            while (menu2 !=  0)
            {
                menu2 = viewAllPokemon();
                // viewAllPokemonNavigation(menu2);
            }
            break;
        case 2: ;
            menu2 = -1;
            while (menu2 !=  10)
            {
                menu2 = menuGenPokemon();
                viewPokemonGenerationNavigation(menu2);
            }     

            break;
        case 3: ;
            // view by type
            menu2 = -1;
            while (menu2 !=  0)
            {
                menu2 = viewPokemonType();
                // getchar;
                viewPokemonTypeDisplay(menu2);
            }   

            break;
        case 4:
            // back
            return;
            break;   
    }
}


//display view pokedex menu
void menuViewPokemonDisplay(int current){
    int atMenu = current % 5 + 1;
    switch(atMenu){
        case 1:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > ");
            colorText("yellow", "View Pokedex");
            printf("\n");
            printf("================================================================\n");
            printf("  "); colorTextunderline("green", "View All\n");
            printf("   View by Generation\n");
            printf("   View by Type\n");
            printf("   Back\n");
            break;
        case 2:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > ");
            colorText("yellow", "View Pokedex");
            printf("\n");
            printf("================================================================\n");
            printf("   View All\n");
            printf("  "); colorTextunderline("green", "View by Generation\n");
            printf("   View by Type\n");
            printf("   Back\n");
            break;
        case 3:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > ");
            colorText("yellow", "View Pokedex");
            printf("\n");
            printf("================================================================\n");
            printf("   View All\n");
            printf("   View by Generation\n");
            printf("  "); colorTextunderline("green", "View by Type\n");
            printf("   Back\n");
            break;
        case 4:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > ");
            colorText("yellow", "View Pokedex");
            printf("\n");
            printf("================================================================\n");
            printf("   View All\n");
            printf("   View by Generation\n");
            printf("   View by Type\n");
            printf("  "); colorTextunderline("red", "Back\n");
            break;
    }
}


void viewAchievement(){
    system("cls");
    char file_name[50] = "./database/achievement.txt";
    printf("================================================================\n");
    printf("Main > Pokemon > ");
    colorText("yellow", "View Achievement");
    printf("\n");
    printf("================================================================\n");
    colorText("red", "\n````````````````````````````````````````````````````````````````\n");
    colorText("red","Press 'b' to back                                               \n");
    colorText("red", "\n````````````````````````````````````````````````````````````````\n\n");
    printAchievement(file_name, 1000);
    getch();
}


// fungsi view pokemon evolution
int viewPokemonEvolutionNavigation(struct Graph* graph){
    char input = ' ';
    int count = 200;
    while (true) {
        viewPokemonEvolutionDisplay(graph, count);
        input = getch(); 
        switch (input) {
            case 'A':
            case 'a':
                count--;
                break;
            case 'D':
            case 'd':
                count++;
                break;
            case 'B':
            case 'b':
                return 0; // back to menu
                break;

            default: ;
                int a = input;
                switch (a) {
                case 75: //left
                    count--;
                    break;
                case 77: //right
                    count++;
                    break;
                case 'B':
                case 'b':
                    return 0; // back to menu
                    break;
                }
            break;
        }
    }
}


void viewPokemonEvolutionDisplay(struct Graph *graph, int current){

    int atMenu = current % 2 + 1;
    char file_name[30]="./database/evolution_all.txt";
    add_edges_from_file(file_name, graph);
    int start_index=(atMenu-1)*10;
    int end_index=start_index+10;
    int total_data=1026;

    system("cls");
    printf("================================================================\n");
    printf("Main > Pokemon > View Pokedex > ");
    colorText("yellow", "View Evolution");
    printf("\n");
    printf("================================================================\n");
    printf("                     << Page %d >>                        \n", atMenu);
    colorText("red", "\n````````````````````````````````````````````````````````````````\n");
    colorText("red","Press 'a' | '<--' or 'd' | '-->' to iterate through generation    \n" );
    colorText("red","Press 'b' to back                                               \n");
    colorText("red", "````````````````````````````````````````````````````````````````\n\n");

    printf("---------------------------------------------------------------------------------\n", (start_index/10)+1, (total_data/10)+1);
    colorText("yellow", "| Name\t\t\t\t| Evolution Path                                |\n");
    printf("---------------------------------------------------------------------------------\n");
    for(int i=start_index; i<=end_index; i++){
        //jika tidak ada evolusi maka tidak akan ditampilkan nama pokemon tsb
        if(graph->array[i].head ==NULL){
            //tidak usah di print
            continue;
        }
        searchPokemon(i+1);
        printf("\t\t\t ");
        printNext(graph, i, i);
        printf("\n");
        printf("---------------------------------------------------------------------------------\n");
    }
} 

int menuGenPokemon(){
    char input = ' ';
    int count = 1000;
    while (true) {
        viewPokemonGenerationDisplay(count);
        input = _getch();  // Read a single character without pressing Enter
        switch (input) {
            case 'S':
            case 's':
                count++;
                break;
            case 'W':
            case 'w':
                count--;
                break;
            case 'B':
            case 'b':
                return 10; // back to menu
                break;
            case '\r': // press 'enter'
                viewPokemonGenerationDisplay(count);
                return count % 10 + 1;
                break;
            default: ;
                int a = input;
                switch (a) {
                case 72: //up
                    count--;
                    break;
                case 80: //down
                    count++;
                    break;
                }
            break;
        }
    }
}

int menuTypePokemon(){
    char input = ' ';
    int count = 1000;
    while (true) {
        // viewPokemonGenerationDisplay(count);
        input = _getch();  // Read a single character without pressing Enter
        switch (input) {
            case 'S':
            case 's':
                count++;
                break;
            case 'W':
            case 'w':
                count--;
                break;
            case 'B':
            case 'b':
                return 2; // back to menu
                break;
            case '\r': // press 'enter'
                viewPokemonGenerationDisplay(count);
                return count % 10 + 1;
                break;
            default: ;
                int a = input;
                switch (a) {
                case 72: //up
                    count--;
                    break;
                case 80: //down
                    count++;
                    break;
                }
            break;
        }
        // viewPokemonGenerationDisplay(count);
    }
}

void viewGen(int gen){
    // int atMenu = current % 9 + 1;
    system("cls");
            printf("===================================================================\n");
            printf("Main > Pokemon > View Pokedex > View by Generation > ");
            printf("\033[33m Generation %d\033[0m", gen);
            printf("\n");
            printf("===================================================================\n");
}

void viewPokemonGenerationNavigation(int nav){
    char file_name[30];
    switch(nav){
        case 1: ;
            strcpy(file_name,"./database/pokedex_gen1.txt");
            printData(file_name, 200, 1);
            break;
        case 2: ;
            strcpy(file_name,"./database/pokedex_gen2.txt");
            printData(file_name, 200, 2);
            break;
        case 3:
            strcpy(file_name,"./database/pokedex_gen3.txt");
            printData(file_name, 200, 3);
            break;
        case 4:
            strcpy(file_name,"./database/pokedex_gen4.txt");
            printData(file_name, 200, 4);
            break;
        case 5:
            strcpy(file_name,"./database/pokedex_gen5.txt");
            printData(file_name, 200, 5);
            break;
        case 6:
            strcpy(file_name,"./database/pokedex_gen6.txt");
            printData(file_name, 200, 6);
            break;
        case 7:
            strcpy(file_name,"./database/pokedex_gen7.txt");
            printData(file_name, 200, 7);
            break;
        case 8:
            strcpy(file_name,"./database/pokedex_gen8.txt");
            printData(file_name, 200, 8);
            break;
        case 9:
            strcpy(file_name,"./database/pokedex_gen9.txt");
            printData(file_name, 200, 9);
            break;
    }
}

void viewPokemonGenerationDisplay(int current){
    int atMenu = current % 10 + 1;
    switch(atMenu){
        case 1:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > ");
            colorText("yellow", "View by Generation");
            printf("\n");
            printf("================================================================\n");
            printf("  "); colorTextunderline("green", "Generation 1\n");
            printf("   Generation 2\n");
            printf("   Generation 3\n");
            printf("   Generation 4\n");
            printf("   Generation 5\n");
            printf("   Generation 6\n");
            printf("   Generation 7\n");
            printf("   Generation 8\n");
            printf("   Generation 9\n");
            printf("   Back\n");
            break;
        case 2:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > ");
            colorText("yellow", "View by Generation");
            printf("\n");
            printf("================================================================\n");
            printf("   Generation 1\n");
            printf("  "); colorTextunderline("green", "Generation 2\n");
            printf("   Generation 3\n");
            printf("   Generation 4\n");
            printf("   Generation 5\n");
            printf("   Generation 6\n");
            printf("   Generation 7\n");
            printf("   Generation 8\n");
            printf("   Generation 9\n");
            printf("   Back\n");
            break;
        case 3:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > ");
            colorText("yellow", "View by Generation");
            printf("\n");
            printf("================================================================\n");
            printf("   Generation 1\n");
            printf("   Generation 2\n");
            printf("  "); colorTextunderline("green", "Generation 3\n");
            printf("   Generation 4\n");
            printf("   Generation 5\n");
            printf("   Generation 6\n");
            printf("   Generation 7\n");
            printf("   Generation 8\n");
            printf("   Generation 9\n");
            printf("   Back\n");
            break;
        case 4:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > ");
            colorText("yellow", "View by Generation");
            printf("\n");
            printf("================================================================\n");
            printf("   Generation 1\n");
            printf("   Generation 2\n");
            printf("   Generation 3\n");
            printf("  "); colorTextunderline("green", "Generation 4\n");
            printf("   Generation 5\n");
            printf("   Generation 6\n");
            printf("   Generation 7\n");
            printf("   Generation 8\n");
            printf("   Generation 9\n");
            printf("   Back\n");
            break;
        case 5:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > ");
            colorText("yellow", "View by Generation");
            printf("\n");
            printf("================================================================\n");
            printf("   Generation 1\n");
            printf("   Generation 2\n");
            printf("   Generation 3\n");
            printf("   Generation 4\n");
            printf("  "); colorTextunderline("green", "Generation 5\n");
            printf("   Generation 6\n");
            printf("   Generation 7\n");
            printf("   Generation 8\n");
            printf("   Generation 9\n");
            printf("   Back\n");
            break;
        case 6:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > ");
            colorText("yellow", "View by Generation");
            printf("\n");
            printf("================================================================\n");
            printf("   Generation 1\n");
            printf("   Generation 2\n");
            printf("   Generation 3\n");
            printf("   Generation 4\n");
            printf("   Generation 5\n");
            printf("  "); colorTextunderline("green", "Generation 6\n");
            printf("   Generation 7\n");
            printf("   Generation 8\n");
            printf("   Generation 9\n");
            printf("   Back\n");
            break;
        case 7:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > ");
            colorText("yellow", "View by Generation");
            printf("\n");
            printf("================================================================\n");
            printf("   Generation 1\n");
            printf("   Generation 2\n");
            printf("   Generation 3\n");
            printf("   Generation 4\n");
            printf("   Generation 5\n");
            printf("   Generation 6\n");
            printf("  "); colorTextunderline("green", "Generation 7\n");
            printf("   Generation 8\n");
            printf("   Generation 9\n");
            printf("   Back\n");
            break;
        case 8:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > ");
            colorText("yellow", "View by Generation");
            printf("\n");
            printf("================================================================\n");
            printf("   Generation 1\n");
            printf("   Generation 2\n");
            printf("   Generation 3\n");
            printf("   Generation 4\n");
            printf("   Generation 5\n");
            printf("   Generation 6\n");
            printf("   Generation 7\n");
            printf("  "); colorTextunderline("green", "Generation 8\n");
            printf("   Generation 9\n");
            printf("   Back\n");
            break;
        case 9:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > ");
            colorText("yellow", "View by Generation");
            printf("\n");
            printf("================================================================\n");
            printf("   Generation 1\n");
            printf("   Generation 2\n");
            printf("   Generation 3\n");
            printf("   Generation 4\n");
            printf("   Generation 5\n");
            printf("   Generation 6\n");
            printf("   Generation 7\n");
            printf("   Generation 8\n");
            printf("  "); colorTextunderline("green", "Generation 9\n");
            printf("   Back\n");
            break;
        case 10:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > ");
            colorText("yellow", "View by Generation");
            printf("\n");
            printf("================================================================\n");
            printf("   Generation 1\n");
            printf("   Generation 2\n");
            printf("   Generation 3\n");
            printf("   Generation 4\n");
            printf("   Generation 5\n");
            printf("   Generation 6\n");
            printf("   Generation 7\n");
            printf("   Generation 8\n");
            printf("   Generation 9\n");
            printf("  "); colorTextunderline("red", "Back\n");
            break;
    }
}

int viewPokemonType(){
    char input = ' ';
    int count = 180;
    while (true) {
        viewPokemonTypeDisplay(count);
        input = _getch();  // Read a single character without pressing Enter
        switch (input) {
            case 'A':
            case 'a':
                count--;
                break;
            case 'D':
            case 'd':
                count++;
                break;
            case 'B':
            case 'b':
                return 0; // back to menu
                break;
            default: ;
            int a = input;
                switch (a) {
                case 75: //left
                    count--;
                    break;
                case 77: //right
                    count++;
                    break;
                }
            break;
        }
    }
}

void viewTypeMenu(char *type){
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
    printPokemonType(type, 1030);
}

void viewPokemonTypeDisplay(int current){
    int atMenu = current % 18 + 1;
    
    switch(atMenu){
        case 1:
            viewTypeMenu("Normal");
            break;
        case 2:
            viewTypeMenu("Fire");
            break;
        case 3:
            viewTypeMenu("Water");
            break;
        case 4:
            viewTypeMenu("Electric");
            break;
        case 5:
            viewTypeMenu("Grass");
            break;
        case 6:
            viewTypeMenu("Ice");
            break;
        case 7:
            viewTypeMenu("Fighting");
            break;
        case 8:
            viewTypeMenu("Poison");
            break;
        case 9:
            viewTypeMenu("Ground");
            break;
        case 10:
            viewTypeMenu("Flying");
            break;
        case 11:
            viewTypeMenu("Psychic");
            break;
        case 12:
            viewTypeMenu("Bug");
            break;
        case 13:
            viewTypeMenu("Rock");
            break;
        case 14:
            viewTypeMenu("Ghost");
            break;
        case 15:
            viewTypeMenu("Dragon");
            break;
        case 16:
            viewTypeMenu("Dark");
            break;
        case 17:
            viewTypeMenu("Steel");
            break;    
        case 18:
            viewTypeMenu("Fairy");
            break;
    }
}

//fungsi view all pokemon gen 1-9
int viewAllPokemon(){
    char input = ' ';
    int count = 5200;
    while (true) {
        viewAllPokemonDisplay(count);
        input = _getch();  // Read a single character without pressing Enter
        switch (input) {
            case 'A':
            case 'a':
                count--;
                break;
            case 'D':
            case 'd':
                count++;
                break;
            case 'B':
            case 'b':
                return 0; // back to menu
                break;
            case '\r': // press 'enter'
                // viewAllPokemonNavigation(count % 19 + 1);
                // _getch();
                break;
            default: ;
            int a = input;
                switch (a) {
                case 75: //left
                    count--;
                    break;
                case 77: //right
                    count++;
                    break;
                }
            break;
            
        }
    }
}

void viewAllPokemonDisplay(int current){
    int atMenu = current % 52 +1;
    char file_name[50] = "./database/pokedex_all.txt";
    //start dari index ke 0, end index ke 20, dst
    int start_index=(atMenu-1)*20;
    int end_index=start_index+20;
    system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > ");
            colorText("yellow", "View All");
            printf("\n");
            printf("================================================================\n");
            printf("                     << Page %d >>                        \n", atMenu);
            colorText("red", "\n````````````````````````````````````````````````````````````````\n");
            colorText("red","Press 'a' | '<--' or 'd' | '-->' to iterate    \n" );
            colorText("red","Press 'b' to back                                               \n");
            colorText("red", "````````````````````````````````````````````````````````````````\n\n");
            printAllData(file_name, start_index, end_index, 10000);
}

void viewAllPokemonNavigation(int nav){
    viewAllPokemonDisplay(nav);
}

int viewPokemonMoveList(){
    char input = ' ';
    int count = 4600;
    while (true) {
        viewAllMoveDisplay(count);
        input = _getch();  // Read a single character without pressing Enter
        switch (input) {
            case 'A':
            case 'a':
                count--;
                break;
            case 'D':
            case 'd':
                count++;
                break;
            case 'B':
            case 'b':
                return 0; // back to menu
                break;
            // case '\r': // press 'enter'
            //     return count % 18 + 1;
            default: ;
            int a = input;
                switch (a) {
                case 75: //left
                    count--;
                    break;
                case 77: //right
                    count++;
                    break;
                }
            break;
        }
    }
}

// Function to display all move list
void viewAllMoveDisplay(int current){
    int atMenu = current % 46 +1;
    char file_name[50] = "./database/movelist.txt";
    int start_index=(atMenu-1)*20;
    int end_index=start_index+20;
    system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > ");
            colorText("yellow", "Move List");
            printf("\n");
            printf("================================================================\n");
            printf("                     << Page %d >>                        \n", atMenu);
            colorText("red", "\n````````````````````````````````````````````````````````````````\n");
            colorText("red","Press 'a' | '<--' or 'd' | '-->' to iterate    \n" );
            colorText("red","Press 'b' to back                                               \n");
            colorText("red", "````````````````````````````````````````````````````````````````\n");
            printAllMoveData(file_name, start_index, end_index, 10000);
}