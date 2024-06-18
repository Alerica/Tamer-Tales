#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include <mmsystem.h>
#include <math.h>

#include "Battle_Tales_Display.h"
#include "Battle_Tales_UI.h"
#include "Battle_Tales_FileProcessing.h"
#include "Battle_Tales_Performance.h"
#include "Battle_Tales_PokemonStruct.h"
#include "Battle_Tales_Inventory.h"

void intro();
void clear_screen();

int BT_mainMenu();
void BT_mainMenuDisplay(int current);
void BT_mainMenuNavigation(int nav);

int BT_mainMenuPlay();
void BT_mainMenuPlayDisplay(int current);
void BT_mainMenuPlayNavigation(int nav);

int BT_mainMenuNewGame();
void BT_mainMenuNewGameDisplay(int current);
void BT_mainMenuNewGameNavigation(int nav);

int BT_mainMenuLoadGame();
void BT_mainMenuLoadGameDisplay(int current);
void BT_mainMenuLoadGameNavigation(int nav);

void intro(){
    system("cls");
    printf("================================================================\n");
    printf("                            Tamer Tales                         \n");
    printf("================================================================\n");
    printf("                                                                \n");
    printf("                                                                \n");
    printf("                             Created by                         \n");
    printf("                  2702224950 - Alexander Ricky B.               \n");
    printf("                  2702236925 - Grace Birgitta H.                \n");
    printf("                  2702343914 - Rafly Adha Prathama              \n");
    printf("                                                                \n");
    printf("                     Press Enter To continue...                 \n");
    printf("                                                                \n");
    printf("                                                                \n");
    printf("                                                                \n");
    printf("================================================================\n");
    getch();
}


int BT_mainMenu(){
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
                return count % 2 + 1;
            default:
                int a = input;
                switch (a) {
                case 72: //up
                    count--;
                    break;
                case 75: //left
                    break;
                case 77: //right
                    break;
                case 80: //down
                    count++;
                    break;
                }
                break;
        } 
        BT_mainMenuDisplay(count);
        input = _getch();  // Read a single character without pressing Enter
        
    }
}

void BT_mainMenuDisplay(int current){
    int atMenu = current % 2 + 1;
    switch(atMenu){
        case 1:
            system("cls");
            printf("================================================================\n");
            printf("                            Tamer Tales                         \n");
            printf("================================================================\n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                        > Play                                  \n");
            printf("                          View Database                         \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("================================================================\n");
            break;
        case 2:
            system("cls");
            printf("================================================================\n");
            printf("                            Tamer Tales                         \n");
            printf("================================================================\n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                          Play                                  \n");
            printf("                        > View Database                         \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("================================================================\n");
            break;
    }
}
void BT_mainMenuNavigation(int nav){
    switch (nav) {
    case 1:
        int menu1 = -1;
        while(menu1 != 5){
            menu1 = BT_mainMenuPlay();
            BT_mainMenuPlayNavigation(menu1);
        }
        break;
    case 2:
        system("Tamer_Tales.exe");
    default:
        break;
    }
}

int BT_mainMenuPlay() {
    char input = ' ';
    int count = 600;
    BT_mainMenuPlayDisplay(count);
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
                return 5;
                break;
            case '\r': // press 'enter'
                return count % 2 + 1;
            default:
                int a = input;
                switch (a) {
                case 72: //up
                    count--;
                    break;
                case 75: //left
                    break;
                case 77: //right
                    break;
                case 80: //down
                    count++;
                    break;
                }
                break;
        } 
        BT_mainMenuPlayDisplay(count);
    }
}
void BT_mainMenuPlayDisplay(int current) {
    int atMenu = current % 2 + 1;
    switch(atMenu){
        case 1:
            system("cls");
            printf("================================================================\n");
            printf("                            Tamer Tales                         \n");
            printf("================================================================\n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                        > Load Game                             \n");
            printf("                          New Game                              \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("================================================================\n");
            break;
        case 2:
            system("cls");
            printf("================================================================\n");
            printf("                            Tamer Tales                         \n");
            printf("================================================================\n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                          Load Game                             \n");
            printf("                        > New Game                              \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("================================================================\n");
            break;
    }
}
void BT_mainMenuPlayNavigation(int nav) {
    switch (nav) {
    case 1:
        void cleanupConsole();
        while(true){
            int exitCode = system("Battle_Tales_MapPalleteTown.exe");
            if( exitCode == 499) {
                mapMenu();
            } else if (exitCode == 899) {
                system("Battle_Tales_Battle.exe");
            } else if (exitCode == 99) {
                dialog();
            }
        }
        break;
    case 2:
        void cleanupConsole();
        save_values("assets\\save_data\\slot_1\\save_temporary.txt", 0, 0, "PalleteTown.txt"); // Reset to starting point
        while(true){
            int exitCode = system("Battle_Tales_MapPalleteTown.exe");
            if( exitCode == 499) {
                mapMenu();
            } else if (exitCode == 899) {
                system("Battle_Tales_Battle.exe");
            } else if (exitCode == 99) {
                dialog();
            }
        }
        break;
    default:
        break;
    }
}

int BT_mainMenuNewGame() {
    char input = ' ';
    int count = 600;
    BT_mainMenuNewGameDisplay(count);
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
                return 5;
                break;
            case '\r': // press 'enter'
                return count % 2 + 1;
            default:
                int a = input;
                switch (a) {
                case 72: //up
                    count--;
                    break;
                case 75: //left
                    break;
                case 77: //right
                    break;
                case 80: //down
                    count++;
                    break;
                }
                break;
        } 
        BT_mainMenuNewGameDisplay(count);
    }

}
void BT_mainMenuNewGameDisplay(int current) {
    int atMenu = current % 2 + 1;
    switch(atMenu){
        case 1:
            system("cls");
            printf("================================================================\n");
            printf("                            Tamer Tales                         \n");
            printf("================================================================\n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                  Do you want to start a new game?              \n");
            printf("                        > Yes                                   \n");
            printf("                          No                                    \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("================================================================\n");
            break;
        case 2:
            system("cls");
            printf("================================================================\n");
            printf("                            Tamer Tales                         \n");
            printf("================================================================\n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                  Do you want to start a new game?              \n");
            printf("                          Yes                                   \n");
            printf("                        > No                                    \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("================================================================\n");
            break;
    }
}
void BT_mainMenuNewGameNavigation(int nav) {
    int exitCode;
    switch (nav) {
    case 1:
        break;
    case 2:
        break;
    default:
        break;
    }
}

int BT_mainMenuLoadGame() {
    char input = ' ';
    int count = 600;
    BT_mainMenuLoadGameDisplay(count);
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
                return 5;
                break;
            case '\r': // press 'enter'
                return count % 3 + 1;
            default:
                int a = input;
                switch (a) {
                case 72: //up
                    count--;
                    break;
                case 75: //left
                    break;
                case 77: //right
                    break;
                case 80: //down
                    count++;
                    break;
                }
                break;
        } 
        BT_mainMenuLoadGameDisplay(count);
    }
}
void BT_mainMenuLoadGameDisplay(int current) {
    int atMenu = current % 3 + 1;
    switch(atMenu){
        case 1:
            system("cls");
            printf("================================================================\n");
            printf("                            Tamer Tales                         \n");
            printf("================================================================\n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                        Select game slot :                      \n");
            printf("                        > Empty                                 \n");
            printf("                          Empty                                 \n");
            printf("                          Empty                                 \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("================================================================\n");
            break;
        case 2:
            system("cls");
            printf("================================================================\n");
            printf("                            Tamer Tales                         \n");
            printf("================================================================\n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                        Select game slot :                      \n");
            printf("                          Empty                                 \n");
            printf("                        > Empty                                 \n");
            printf("                          Empty                                 \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("================================================================\n");
            break;
        case 3:
            system("cls");
            printf("================================================================\n");
            printf("                            Tamer Tales                         \n");
            printf("================================================================\n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                        Select game slot :                      \n");
            printf("                          Empty                                 \n");
            printf("                          Empty                                 \n");
            printf("                        > Empty                                 \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("                                                                \n");
            printf("================================================================\n");
            break;
    }
}
void BT_mainMenuLoadGameNavigation(int nav) {
    switch (nav) {
    case 1:
        void cleanupConsole();
        while(true){

            // int exitcode = system("Battle_Tales_MapPalleteTown.exe");
            // system("cls");
            // printf("exit code : %d\n",exitcode);
            // getch();
            // if( exitcode == 499) {
            //     mapMenu();
            // } else if( exitcode == 899) {
            //     PlaySound(TEXT("assets\\music\\battle.wav"), NULL, SND_ASYNC | SND_LOOP);
            //     transition();
            //     system("Battle_Tales_Battle.exe");
            // }
        }
        break;
    case 2:
        void cleanupConsole();
        while(true){
            system("Battle_Tales_Player2.exe");
        }
        break;
    case 3:
        void cleanupConsole();
        while(true){
            system("Battle_Tales_Player3.exe");
        }
        break;
    default:
        break;
    }
}

void clear_screen() {
    printf("\033[2J");  
    printf("\033[H");  
}