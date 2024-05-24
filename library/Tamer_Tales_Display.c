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
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include "Tamer_Tales_FileProcessing.h"


int menuPokemon();
void menuPokemonDisplay(int current);
void menuPokemonNavigation(int nav);

int menuViewPokemon();
void menuViewPokemonDisplay(int current);
void menuViewPokemonNavigation(int nav);


int viewPokemonGeneration();
void viewPokemonGenerationDisplay(int current);
void viewPokemonGenerationNavigation(int nav);


void menuPokemonNavigation(int nav) {
    switch (nav) {
        case 1:
            // add pokemon
            break;
        case 2:
            int menu2 = -1;
            while (menu2 !=  4)
            {
                menu2 = menuViewPokemon();
                menuViewPokemonNavigation(menu2);
            }
            break;
        case 3:
            // search pokemon
            break;
        case 4:
            // update pokemon
            break;
        case 5:
            // delete pokemon
            break;
        case 6:
            exit(1);
            break;
    }
}

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
            default:
                break;
        }
        menuPokemonDisplay(count);
        input = _getch();  // Read a single character without pressing Enter
    }
}

void menuPokemonDisplay(int current) {
    int atMenu = current % 6 + 1;
    switch(atMenu) {
        case 1:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon\n");
            printf("================================================================\n");
            printf(">  Add Pokemon\n");
            printf("   View Pokedex\n");
            printf("   Search Pokemon\n");
            printf("   Update Pokemon\n");
            printf("   Delete Pokemon\n");
            printf("   Exit\n");
            break;
        case 2:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon\n");
            printf("================================================================\n");
            printf("   Add Pokemon\n");
            printf(">  View Pokedex\n");
            printf("   Search Pokemon\n");
            printf("   Update Pokemon\n");
            printf("   Delete Pokemon\n");
            printf("   Exit\n");
            break;
        case 3:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon\n");
            printf("================================================================\n");
            printf("   Add Pokemon\n");
            printf("   View Pokedex\n");
            printf(">  Search Pokemon\n");
            printf("   Update Pokemon\n");
            printf("   Delete Pokemon\n");
            printf("   Exit\n");
            break;
        case 4:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon\n");
            printf("================================================================\n");
            printf("   Add Pokemon\n");
            printf("   View Pokedex\n");
            printf("   Search Pokemon\n");
            printf(">  Update Pokemon\n");
            printf("   Delete Pokemon\n");
            printf("   Exit\n");
            break;
        case 5:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon\n");
            printf("================================================================\n");
            printf("   Add Pokemon\n");
            printf("   View Pokedex\n");
            printf("   Search Pokemon\n");
            printf("   Update Pokemon\n");
            printf(">  Delete Pokemon\n");
            printf("   Exit\n");
            break;
        case 6:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon\n");
            printf("================================================================\n");
            printf("   Add Pokemon\n");
            printf("   View Pokedex\n");
            printf("   Search Pokemon\n");
            printf("   Update Pokemon\n");
            printf("   Delete Pokemon\n");
            printf(">  Exit\n");
            break;
    }
}

int menuViewPokemon() {
    char input = ' ';
    int count = 600;
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
            case '\r': // press 'enter'
                return count % 4 + 1;
            default:
                break;
            
        }
        menuViewPokemonDisplay(count);
    }
}

void menuViewPokemonNavigation(int nav) {
    switch(nav){
        case 1:
            break;
        case 2:
            int menu2 = -1;
            while (menu2 !=  0)
            {
                menu2 = viewPokemonGeneration();
                viewPokemonGenerationNavigation(menu2);
            }     
            break;
        case 3:
            break;
        case 4:
            break;
        
    }
}

void menuViewPokemonDisplay(int current){
    int atMenu = current % 4 + 1;
    switch(atMenu){
        case 1:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex\n");
            printf("================================================================\n");
            printf(">  View All\n");
            printf("   View by Generation\n");
            printf("   View by Type\n");
            printf("   Back\n");
            break;
        case 2:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex\n");
            printf("================================================================\n");
            printf("   View All\n");
            printf(">  View by Generation\n");
            printf("   View by Type\n");
            printf("   Back\n");
            break;
        case 3:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex\n");
            printf("================================================================\n");
            printf("   View All\n");
            printf("   View by Generation\n");
            printf(">  View by Type\n");
            printf("   Back\n");
            break;
        case 4:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex\n");
            printf("================================================================\n");
            printf("   View All\n");
            printf("   View by Generation\n");
            printf("   View by Type\n");
            printf(">  Back\n");
            break;
    }
}

int viewPokemonGeneration(){
    char input = ' ';
    int count = 600;
    while (true) {
        viewPokemonGenerationDisplay(count);
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
                return count % 9 + 1;
            default:
                break;
            
        }
        input = _getch();  // Read a single character without pressing Enter
    }
}

void viewPokemonGenerationDisplay(int current){
    int atMenu = current % 9 + 1;
    switch(atMenu){
        case 1:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > View by Generation\n");
            printf("================================================================\n");
            printf("                     << Generation 1 >>                        \n");
            printf("Press 'a' or 'd' to iterate through generation\n" );
            printf("Press 'b' to back, 'enter' to see the pokedex\n");
            break;
        case 2:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > View by Generation\n");
            printf("================================================================\n");
            printf("                      << Generation 2 >>                        \n");
            printf("Press 'a' or 'd' to iterate through generation\n" );
            printf("Press 'b' to back, 'enter' to see the pokedex\n");
            break;
        case 3:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > View by Generation\n");
            printf("================================================================\n");
            printf("                      << Generation 3 >>                        \n");
            printf("Press 'a' or 'd' to iterate through generation\n" );
            printf("Press 'b' to back, 'enter' to see the pokedex\n");
            break;
        case 4:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > View by Generation\n");
            printf("================================================================\n");
            printf("                      << Generation 4 >>                        \n");
            printf("Press 'a' or 'd' to iterate through generation\n" );
            printf("Press 'b' to back, 'enter' to see the pokedex\n");
            break;
        case 5:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > View by Generation\n");
            printf("================================================================\n");
            printf("                      << Generation 5 >>                        \n");
            printf("Press 'a' or 'd' to iterate through generation\n" );
            printf("Press 'b' to back, 'enter' to see the pokedex\n");
            break;
        case 6:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > View by Generation\n");
            printf("================================================================\n");
            printf("                      << Generation 6 >>                        \n");
            printf("Press 'a' or 'd' to iterate through generation\n" );
            printf("Press 'b' to back, 'enter' to see the pokedex\n");
            break;
        case 7:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > View by Generation\n");
            printf("================================================================\n");
            printf("                      << Generation 7 >>                        \n");
            printf("Press 'a' or 'd' to iterate through generation\n" );
            printf("Press 'b' to back, 'enter' to see the pokedex\n");
            break;
        case 8:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > View by Generation\n");
            printf("================================================================\n");
            printf("                      << Generation 8 >>                        \n");
            printf("Press 'a' or 'd' to iterate through generation\n" );
            printf("Press 'b' to back, 'enter' to see the pokedex\n");
            break;
        case 9:
            system("cls");
            printf("================================================================\n");
            printf("Main > Pokemon > View Pokedex > View by Generation\n");
            printf("================================================================\n");
            printf("                      << Generation 9 >>                        \n");
            printf("Press 'a' or 'd' to iterate through generation\n" );
            printf("Press 'b' to back, 'enter' to see the pokedex\n");
            break;    
    }
}
void viewPokemonGenerationNavigation(int nav){
    char file_name[20];
    switch(nav){
        case 1:
            strcpy(file_name,"pokedex_gen1.txt");
            printData(file_name, 200);
            break;
        case 2:
            strcpy(file_name,"pokedex_gen2.txt");
            printData(file_name, 200);
            break;
        case 3:
            strcpy(file_name,"pokedex_gen3.txt");
            printData(file_name, 200);
            break;
        case 4:
            strcpy(file_name,"pokedex_gen4.txt");
            printData(file_name, 200);
            break;
        case 5:
            strcpy(file_name,"pokedex_gen5.txt");
            printData(file_name, 200);
            break;
        case 6:
            strcpy(file_name,"pokedex_gen6.txt");
            printData(file_name, 200);
            break;
        case 7:
            strcpy(file_name,"pokedex_gen7.txt");
            printData(file_name, 200);
            break;
        case 8:
            strcpy(file_name,"pokedex_gen8.txt");
            printData(file_name, 200);
            break;
        case 9:
            strcpy(file_name,"pokedex_gen9.txt");
            printData(file_name, 200);
            break;
        
    }
}
/*

system("cls");
    int menu;
    printf("=======================\n");
    printf("Main > Pokemon\n");
    printf("=======================\n");
    printf("Add Pokemon\n");
    printf("View Pokedex\n");
    printf("Search Pokemon\n");
    printf("Update Pokemon\n");
    printf("Delete Pokemon\n");
    printf("Exit\n");
*/
