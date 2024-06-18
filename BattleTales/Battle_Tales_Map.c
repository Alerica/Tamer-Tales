#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include <unistd.h>
#include "Battle_Tales_Display.h"
#include "Battle_Tales_UI.h"
#include "Battle_Tales_PokemonStruct.h"
#include "Battle_Tales_Performance.h"
#include "Battle_Tales_Inventory.h"
#include "Battle_Tales_FileProcessing.h"

#define MAX_LINE_LENGTH 200
#define SCREEN_WIDTH  74
#define SCREEN_HEIGHT 24
#define TRANSITION_FRAMES 24

int openMapHouse1(char file_name[], int total_data, int add_x, int add_y);
int openMapHouse2(char file_name[], int total_data, int add_x, int add_y);
int openMountain(char file_name[], int total_data, int add_x, int add_y);
int openCave1(char file_name[], int total_data, int add_x, int add_y);

int openMapHouse1(char file_name[], int total_data, int add_x, int add_y) {
FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        printf("Press any key to continue..");
        getch();
        return 399;
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); 

    char map[total_data][total_data];
    
    int counter = 0;
    while (fgets(line, sizeof(line), file)) {
        for(int i = 0; i < strlen(line); i++){
            map[counter][i] = line[i];
            
        }
        counter++;
    }

    fclose(file);

    int player_x = 44 + add_x;
    int player_y = 17 + add_y;
    int start_height = 10 + add_y; // 2010; // 14 7
    int start_width = 10 + add_x; // 2010;// 64 32
    int height =  24 + add_y;// 2024 
    int width =  74 + add_x;// 2074; // 74
    PlaySound(TEXT("assets\\music\\town.wav"), NULL, SND_ASYNC | SND_LOOP);
    while(true) {
        clearScreen();
        draw("\033[40m===================================================================", 0, 0);
        draw("\033[40m                            Tamer Tales                            ", 0, 1);
        draw("\033[40m===================================================================", 0, 2);
        char text[1500];
        strcpy(text,"");
        int row = 3;
        bool go_left = false, go_right = false, go_up = false, go_down = false;
        for(int i = start_height; i < height; i++){
            strcat(text,"\033[0m==");

            if(map[i][start_width] == '0') {
                strcat(text,"\033[40m"); // Black
                strcat_char(text, ' ');
            } else if (map[i][start_width] == '\\') {
                // \033[48;5;94m
                strcat(text,""); // Brown
                strcat_char(text, '\\');
            } else if (map[i][start_width] == '|') {
                strcat(text,"\033[48;5;94m"); // Brown
                strcat_char(text, '|');
            } else if(map[i][start_width] == ' ') {
                strcat(text,"\033[48;5;94m"); // Brown 
                strcat_char(text, ' ');
            } else {
                strcat(text,"\033[48;5;94m"); // Brown
                strcat_char(text, map[i][start_width]);
            }
            
            bool first = true;
            for(int j = start_width; j < width; j++) {
                if(i == player_y + 1 && j == player_x) {
                    if(map[i][j] == ' ') {
                        go_down = true;
                    }
                }

                if(i == player_y - 1 && j == player_x) {
                    if(map[i][j] == ' ') {
                        go_up = true;
                    }
                }

                if(i == player_y && j == player_x + 1) {
                    if(map[i][j] == ' ') {
                        go_right = true;
                    }
                }

                if(i == player_y && j == player_x - 1) {
                    if(map[i][j] == ' ') {
                        go_left = true;
                    }
                }

                if(first == true){
                    first = false;
                    continue;
                }

                if(i == player_y && j == player_x) { // print player
                    strcat(text,"\033[48;5;94m"); // Brown
                    strcat_char(text,'@');   
                    continue;
                } else if(map[i][j] == map[i][j-1]) {
                    if (map[i][j] == '0') {
                        strcat_char(text, ' ');
                        continue;
                    } else if (map[i][j-1] == '\\') {
                        strcat_char(text, '\\');
                        continue;
                    } else if (map[i][j-1] == '|') {
                        strcat_char(text, '|');
                        continue;
                    } else if (map[i][j-1] == '_') {
                        strcat_char(text, '_');
                        continue;
                    } else if (map[i][j-1] == '-') {
                        strcat_char(text, '-');
                        continue;
                    } else if (map[i][j-1] == 'v') {
                        strcat_char(text, 'v');
                        continue;
                    } else if (map[i][j-1] == ' ') {
                        strcat_char(text, ' ');
                        continue;
                    } else {
                        strcat_char(text, map[i][j-1]);
                        continue;
                    }
                } else {
                    if(map[i][j] == '0') {
                        strcat(text,"\033[40m"); // Black
                        strcat_char(text,' ');
                        continue;
                    } else if (map[i][j] == '\\') {
                        strcat_char(text,'\\');
                        continue;
                    } else if (map[i][j] == '/') {
                        strcat_char(text, '/');
                        continue;
                    } else if (map[i][j] == 'o') {
                        strcat_char(text, 'o');
                        continue;
                    } else if (map[i][j] == '#') {
                        if (map[i][j-1] == '0') {
                            strcat(text,"\033[48;5;94m");  // Brown 
                            strcat_char(text,'#');
                            continue;
                        } else { 
                            strcat_char(text,'#');
                            continue;
                        }
                    } else if (map[i][j] == '|') {
                        strcat_char(text, '|');
                        continue;
                    } else if (map[i][j] == '_') {
                        strcat_char(text, '_');
                        continue;
                    } else if (map[i][j] == '-') {
                        strcat_char(text, '-');
                        continue;
                    } else if (map[i][j] == 'v') {
                        strcat_char(text, 'v');
                        continue;
                    } else if(map[i][j] == ' ') {
                        if (map[i][j-1] == '0') {
                            strcat(text,"\033[48;5;94m");  // Brown 
                            strcat_char(text,' ');
                            continue;
                        } else { 
                            strcat_char(text,' ');
                            continue;
                        }
                    } else {
                        strcat(text,"\033[48;5;94m");
                        strcat_char(text, map[i][j]);
                        continue;
                    }
                } 
            }
            strcat(text,"\033[0m"); // Reset Color
            strcat(text,"== ");
            draw(text, 0, row++);
            strcpy(text,"");
            
        }
        draw("\033[40m===================================================================", 0, row++);
        draw("\033[40m                            Tamer Tales                            ", 0, row++);
        draw("\033[40m===================================================================", 0, row++);
        // char coordinates[10];
        // char strcoor[10];
        // sprintf(strcoor, "%d", player_x);
        // strcat(coordinates, strcoor);
        // strcat(coordinates,",");
        // strcpy(strcoor,"");
        // sprintf(strcoor, "%d", player_y);
        // strcat(coordinates, strcoor);
        // draw(coordinates, 0, row++);
        // row = 0;
        colorReset();
        swapBuffers();
        char input = ' ';
        input = _getch(); 
        
        switch (input) {
            case 'S':
            case 's':
                if(player_y < 35 && go_down) {
                    height++;
                    start_height++;
                    player_y++;
                    add_y++;
                }
                break;
            case 'W':
            case 'w':
                if(player_y > 17 && go_up) {
                    height--;
                    start_height--;
                    player_y--;
                    add_y--;
                }
                break;
            case 'A':
            case 'a':
                if(player_x > 34 && go_left) {
                    width--;
                    start_width--;
                    player_x--;
                    add_x--;
                }
                break;
            case 'D':
            case 'd':
                if(player_x < 77 && go_right){ 
                    width++;
                    start_width++;
                    player_x++;
                    add_x++;
                }
                break;
            case 'B':
            case 'b':
                break;
            case 'M':
            case 'm':
                return 499;
                break;
            case '\033':
                save_values("assets\\save_data\\slot_1\\save_temporary.txt", add_x, add_y, "House1.txt");
                return 399;
            case '\r': // press 'enter'
            default:
                int a = input;
                switch (a) {
                case 72: //up
                    if(player_y > 17 && go_up) {
                        height--;
                        start_height--;
                        player_y--;
                        add_y--;
                    }
                    break;
                case 75: //left
                    if(player_x > 34 && go_left) {
                        width--;
                        start_width--;
                        player_x--;
                        add_x--;
                    }
                    break;
                case 77: //right
                    if(player_x < 77 && go_right) { 
                        width++;
                        start_width++;
                        player_x++;
                        add_x++;
                    }
                    break;
                case 80: //down
                    if(player_y < 35 && go_down) {
                        height++;
                        start_height++;
                        player_y++;
                        add_y++;
                    }
                    break;
                }
                break;
        } 
        if(player_x == 46 && player_y == 35) {
            save_values("assets\\save_data\\slot_1\\save_temporary.txt",69, 13, "PalleteTown.txt");
            return 399;
        } else if (player_x == 47 && player_y == 35) {
            save_values("assets\\save_data\\slot_1\\save_temporary.txt",69, 13, "PalleteTown.txt");
            return 399;
        }
        if(player_x == 63 && player_y == 24) {
            return 99;
        } else if(player_x == 65 && player_y == 24) {
            return 99;
        } else if(player_x == 64 && player_y == 23) {
            return 99;
        } else if(player_x == 64 && player_y == 25) {
            return 99;
        }
        Sleep(20);
        save_values("assets\\save_data\\slot_1\\save_temporary.txt",add_x, add_y, "House1.txt");
    }
}

int openMapHouse2(char file_name[], int total_data, int add_x, int add_y) {
FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        printf("Press any key to continue..");
        getch();
        return 399;
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); 

    char map[total_data][total_data];
    
    int counter = 0;
    while (fgets(line, sizeof(line), file)) {
        for(int i = 0; i < strlen(line); i++){
            map[counter][i] = line[i];
            
        }
        counter++;
    }

    fclose(file);

    int player_x = 44 + add_x;
    int player_y = 17 + add_y;
    int start_height = 10 + add_y; // 2010; // 14 7
    int start_width = 10 + add_x; // 2010;// 64 32
    int height =  24 + add_y;// 2024 
    int width =  74 + add_x;// 2074; // 74
    PlaySound(TEXT("assets\\music\\town.wav"), NULL, SND_ASYNC | SND_LOOP);
    while(true) {
        clearScreen();
        draw("\033[40m===================================================================", 0, 0);
        draw("\033[40m                            Tamer Tales                            ", 0, 1);
        draw("\033[40m===================================================================", 0, 2);
        char text[1500];
        strcpy(text,"");
        int row = 3;
        bool go_left = false, go_right = false, go_up = false, go_down = false;
        for(int i = start_height; i < height; i++){
            strcat(text,"\033[0m==");

            if(map[i][start_width] == '0') {
                strcat(text,"\033[40m"); // Black
                strcat_char(text, ' ');
            } else if (map[i][start_width] == '\\') {
                // \033[48;5;94m
                strcat(text,""); // Brown
                strcat_char(text, '\\');
            } else if (map[i][start_width] == '|') {
                strcat(text,"\033[48;5;94m"); // Brown
                strcat_char(text, '|');
            } else if(map[i][start_width] == ' ') {
                strcat(text,"\033[48;5;94m"); // Brown 
                strcat_char(text, ' ');
            } else {
                strcat(text,"\033[48;5;94m"); // Brown
                strcat_char(text, map[i][start_width]);
            }
            
            bool first = true;
            for(int j = start_width; j < width; j++) {
                if(i == player_y + 1 && j == player_x) {
                    if(map[i][j] == ' ') {
                        go_down = true;
                    }
                }

                if(i == player_y - 1 && j == player_x) {
                    if(map[i][j] == ' ') {
                        go_up = true;
                    }
                }

                if(i == player_y && j == player_x + 1) {
                    if(map[i][j] == ' ') {
                        go_right = true;
                    }
                }

                if(i == player_y && j == player_x - 1) {
                    if(map[i][j] == ' ') {
                        go_left = true;
                    }
                }

                if(first == true){
                    first = false;
                    continue;
                }

                if(i == player_y && j == player_x) { // print player
                    strcat(text,"\033[48;5;94m"); // Brown
                    strcat_char(text,'@');   
                    continue;
                } else if(map[i][j] == map[i][j-1]) {
                    if (map[i][j] == '0') {
                        strcat_char(text, ' ');
                        continue;
                    } else if (map[i][j-1] == '\\') {
                        strcat_char(text, '\\');
                        continue;
                    } else if (map[i][j-1] == '|') {
                        strcat_char(text, '|');
                        continue;
                    } else if (map[i][j-1] == '_') {
                        strcat_char(text, '_');
                        continue;
                    } else if (map[i][j-1] == '-') {
                        strcat_char(text, '-');
                        continue;
                    } else if (map[i][j-1] == 'v') {
                        strcat_char(text, 'v');
                        continue;
                    } else if (map[i][j-1] == ' ') {
                        strcat_char(text, ' ');
                        continue;
                    } else {
                        strcat_char(text, map[i][j-1]);
                        continue;
                    }
                } else {
                    if(map[i][j] == '0') {
                        strcat(text,"\033[40m"); // Black
                        strcat_char(text,' ');
                        continue;
                    } else if (map[i][j] == '\\') {
                        strcat_char(text,'\\');
                        continue;
                    } else if (map[i][j] == '/') {
                        strcat_char(text, '/');
                        continue;
                    } else if (map[i][j] == 'o') {
                        strcat_char(text, 'o');
                        continue;
                    } else if (map[i][j] == '#') {
                        if (map[i][j-1] == '0') {
                            strcat(text,"\033[48;5;94m");  // Brown 
                            strcat_char(text,'#');
                            continue;
                        } else { 
                            strcat_char(text,'#');
                            continue;
                        }
                    } else if (map[i][j] == '|') {
                        strcat_char(text, '|');
                        continue;
                    } else if (map[i][j] == '_') {
                        strcat_char(text, '_');
                        continue;
                    } else if (map[i][j] == '-') {
                        strcat_char(text, '-');
                        continue;
                    } else if (map[i][j] == 'v') {
                        strcat_char(text, 'v');
                        continue;
                    } else if(map[i][j] == ' ') {
                        if (map[i][j-1] == '0') {
                            strcat(text,"\033[48;5;94m");  // Brown 
                            strcat_char(text,' ');
                            continue;
                        } else { 
                            strcat_char(text,' ');
                            continue;
                        }
                    } else {
                        strcat(text,"\033[48;5;94m");
                        strcat_char(text, map[i][j]);
                        continue;
                    }
                } 
            }
            strcat(text,"\033[0m"); // Reset Color
            strcat(text,"== ");
            draw(text, 0, row++);
            strcpy(text,"");
            
        }
        draw("\033[40m===================================================================", 0, row++);
        draw("\033[40m                            Tamer Tales                            ", 0, row++);
        draw("\033[40m===================================================================", 0, row++);
        row = 0;
        colorReset();
        swapBuffers();
        char input = ' ';
        input = _getch(); 
        
        switch (input) {
            case 'S':
            case 's':
                if(player_y < 35 && go_down) {
                    height++;
                    start_height++;
                    player_y++;
                    add_y++;
                }
                break;
            case 'W':
            case 'w':
                if(player_y > 17 && go_up) {
                    height--;
                    start_height--;
                    player_y--;
                    add_y--;
                }
                break;
            case 'A':
            case 'a':
                if(player_x > 34 && go_left) {
                    width--;
                    start_width--;
                    player_x--;
                    add_x--;
                }
                break;
            case 'D':
            case 'd':
                if(player_x < 77 && go_right){ 
                    width++;
                    start_width++;
                    player_x++;
                    add_x++;
                }
                break;
            case 'B':
            case 'b':
                break;
            case 'M':
            case 'm':
                return 499;
                break;
            case '\033':
                save_values("assets\\save_data\\slot_1\\save_temporary.txt", add_x, add_y, "House2.txt");
                return 399;
            case '\r': // press 'enter'
            default:
                int a = input;
                switch (a) {
                case 72: //up
                    if(player_y > 17 && go_up) {
                        height--;
                        start_height--;
                        player_y--;
                        add_y--;
                    }
                    if(player_x == 113, player_y == 29){
                        return 799;
                    }
                    break;
                case 75: //left
                    if(player_x > 34 && go_left) {
                        width--;
                        start_width--;
                        player_x--;
                        add_x--;
                    }
                    break;
                case 77: //right
                    if(player_x < 77 && go_right){ 
                        width++;
                        start_width++;
                        player_x++;
                        add_x++;
                    }
                    break;
                case 80: //down
                    if(player_y < 35 && go_down) {
                        height++;
                        start_height++;
                        player_y++;
                        add_y++;
                    }
                    break;
                }
                break;
        } 
        if(player_x == 46 && player_y == 35) {
            save_values("assets\\save_data\\slot_1\\save_temporary.txt",26, 10, "PalleteTown.txt");
            return 399;
        } else if (player_x == 47 && player_y == 35) {
            save_values("assets\\save_data\\slot_1\\save_temporary.txt",26, 10, "PalleteTown.txt");
            return 399;
        }
        Sleep(20);
        save_values("assets\\save_data\\slot_1\\save_temporary.txt",add_x, add_y, "House2.txt");
    }
}

int openMountain(char file_name[], int total_data, int add_x, int add_y) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        printf("Press any key to continue..");
        getch();
        return 399;
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); 

    char map[total_data][total_data];
    
    int counter = 0;
    while (fgets(line, sizeof(line), file)) {
        for(int i = 0; i < strlen(line); i++){
            map[counter][i] = line[i];
            
        }
        counter++;
    }

    fclose(file);

    int player_x = 44 + add_x; 
    int player_y = 17 + add_y;
    int start_height = 10 + add_y; // 2010; // 14 7
    int start_width = 10 + add_x; // 2010;// 64 32
    int height =  24 + add_y;// 2024 
    int width =  74 + add_x;// 2074; // 74
    PlaySound(TEXT("assets\\music\\town.wav"), NULL, SND_ASYNC | SND_LOOP);
    while(true) {
        clearScreen();
        draw("\033[40m===================================================================", 0, 0);
        draw("\033[40m                            Tamer Tales                            ", 0, 1);
        draw("\033[40m===================================================================", 0, 2);
        char text[1500];
        strcpy(text,"");
        int row = 3;
        bool go_left = false, go_right = false, go_up = false, go_down = false;
        for(int i = start_height; i < height; i++){
            strcat(text,"\033[0m==");

            if(map[i][start_width] == '0') {
                strcat(text,"\033[40m"); // Black
                strcat_char(text, ' ');
            } else if (map[i][start_width] == '\\') {
                strcat(text,"\033[100m"); // Gray
                strcat_char(text, '\\');
            } else if (map[i][start_width] == '|') {
                strcat(text,"\033[100m"); // Gray
                strcat_char(text, '|');
            } else if(map[i][start_width] == ' ') {
                strcat(text,"\033[100m"); // Gray 
                strcat_char(text, ' ');
            } else {
                strcat(text,"\033[100m"); // Gray
                strcat_char(text, map[i][start_width]);
            }
            
            bool first = true;
            for(int j = start_width; j < width; j++) {
                if(i == player_y + 1 && j == player_x) {
                    if(map[i][j] == ' ' || map[i][j] == '.' ) {
                        go_down = true;
                    }
                }

                if(i == player_y - 1 && j == player_x) {
                    if(map[i][j] == ' ' || map[i][j] == '.') {
                        go_up = true;
                    }
                }

                if(i == player_y && j == player_x + 1) {
                    if(map[i][j] == ' ' || map[i][j] == '.') {
                        go_right = true;
                    }
                }

                if(i == player_y && j == player_x - 1) {
                    if(map[i][j] == ' ' || map[i][j] == '.') {
                        go_left = true;
                    }
                }

                if(first == true){
                    first = false;
                    continue;
                }

                if(i == player_y && j == player_x) { // print player
                    strcat(text,"\033[100m"); // Gray
                    strcat_char(text,'@');   
                    continue;
                } else if(map[i][j] == map[i][j-1]) {
                    if (map[i][j] == '0') {
                        strcat_char(text, ' ');
                        continue;
                    } else if (map[i][j-1] == '\\') {
                        strcat_char(text, '\\');
                        continue;
                    } else if (map[i][j-1] == '|') {
                        strcat_char(text, '|');
                        continue;
                    } else if (map[i][j-1] == '_') {
                        strcat_char(text, '_');
                        continue;
                    } else if (map[i][j-1] == '-') {
                        strcat_char(text, '-');
                        continue;
                    } else if (map[i][j-1] == 'v') {
                        strcat_char(text, 'v');
                        continue;
                    } else if (map[i][j-1] == ' ') {
                        strcat_char(text, ' ');
                        continue;
                    } else {
                        strcat_char(text, map[i][j-1]);
                        continue;
                    }
                } else {
                    if(map[i][j] == '0') {
                        strcat(text,"\033[40m"); // Black
                        strcat_char(text,' ');
                        continue;
                    } else if (map[i][j] == '\\') {
                        strcat_char(text,'\\');
                        continue;
                    } else if (map[i][j] == '/') {
                        strcat_char(text, '/');
                        continue;
                    } else if (map[i][j] == 'o') {
                        strcat_char(text, 'o');
                        continue;
                    } else if (map[i][j] == '#') {
                        if (map[i][j-1] == '0') {
                            strcat(text,"\033[100m");  // Gray 
                            strcat_char(text,'#');
                            continue;
                        } else { 
                            strcat_char(text,'#');
                            continue;
                        }
                    } else if (map[i][j] == '|') {
                        strcat_char(text, '|');
                        continue;
                    } else if (map[i][j] == '_') {
                        strcat_char(text, '_');
                        continue;
                    } else if (map[i][j] == '-') {
                        strcat_char(text, '-');
                        continue;
                    } else if (map[i][j] == 'v') {
                        strcat_char(text, 'v');
                        continue;
                    } else if(map[i][j] == ' ') {
                        if (map[i][j-1] == '0') {
                            strcat(text,"\033[100m");  // Gray 
                            strcat_char(text,' ');
                            continue;
                        } else { 
                            strcat_char(text,' ');
                            continue;
                        }
                    } else {
                        strcat(text,"\033[100m");
                        strcat_char(text, map[i][j]);
                        continue;
                    }
                } 
            }
            strcat(text,"\033[0m"); // Reset Color
            strcat(text,"== ");
            draw(text, 0, row++);
            strcpy(text,"");
            
        }
        draw("\033[40m===================================================================", 0, row++);
        draw("\033[40m                            Tamer Tales                            ", 0, row++);
        draw("\033[40m===================================================================", 0, row++);
        // char coordinates[10];
        // char strcoor[10];
        // sprintf(strcoor, "%d", player_x);
        // strcat(coordinates, strcoor);
        // strcat(coordinates,",");
        // strcpy(strcoor,"");
        // sprintf(strcoor, "%d", player_y);
        // strcat(coordinates, strcoor);
        // draw(coordinates, 0, row++);
        row = 0;
        colorReset();
        swapBuffers();
        char input = ' ';
        input = _getch(); 
        
        switch (input) {
            case 'S':
            case 's':
                if(player_y < 70 && go_down) {
                    height++;
                    start_height++;
                    player_y++;
                    add_y++;
                }
                break;
            case 'W':
            case 'w':
                if(player_y > 17 && go_up) {
                    height--;
                    start_height--;
                    player_y--;
                    add_y--;
                }
                break;
            case 'A':
            case 'a':
                if(player_x > 34 && go_left) {
                    width--;
                    start_width--;
                    player_x--;
                    add_x--;
                }
                break;
            case 'D':
            case 'd':
                if(player_x < 167 && go_right){ 
                    width++;
                    start_width++;
                    player_x++;
                    add_x++;
                }
                break;
            case 'B':
            case 'b':
                break;
            case 'M':
            case 'm':
                return 499;
                break;
            case '\033':
                save_values("assets\\save_data\\slot_1\\save_temporary.txt", add_x, add_y, "Mountain1.txt");
                return 399;
            case '\r': // press 'enter'
            default:
                int a = input;
                switch (a) {
                case 72: //up
                    if(player_y > 17 && go_up) {
                        height--;
                        start_height--;
                        player_y--;
                        add_y--;
                    }
                    break;
                case 75: //left
                    if(player_x > 34 && go_left) {
                        width--;
                        start_width--;
                        player_x--;
                        add_x--;
                    }
                    break;
                case 77: //right
                    if(player_x < 167 && go_right){ 
                        width++;
                        start_width++;
                        player_x++;
                        add_x++;
                    }
                    break;
                case 80: //down
                    if(player_y < 167 && go_down) {
                        height++;
                        start_height++;
                        player_y++;
                        add_y++;
                    }
                    break;
                }
                break;
        } 
        if(player_x == 34 && player_y == 44) {
            save_values("assets\\save_data\\slot_1\\save_temporary.txt", 123, 5, "PalleteTown.txt");
            return 399;
        }
        if(player_x == 34 && player_y == 45) {
            save_values("assets\\save_data\\slot_1\\save_temporary.txt", 123, 6, "PalleteTown.txt");
            return 399;
        }
        if(player_x == 50 && player_y == 26) {
            save_values("assets\\save_data\\slot_1\\save_temporary.txt", 64, 18, "Cave1.txt");
            return 399;
        }
        if(player_x == 51 && player_y == 26) {
            save_values("assets\\save_data\\slot_1\\save_temporary.txt", 65, 18, "Cave1.txt");
            return 399;
        }
        if(player_x == 52 && player_y == 26) {
            save_values("assets\\save_data\\slot_1\\save_temporary.txt", 66, 18, "Cave1.txt");
            return 399;
        }
        if(player_x == 53 && player_y == 26) {
            save_values("assets\\save_data\\slot_1\\save_temporary.txt", 67, 18, "Cave1.txt");
            return 399;
        }
        Sleep(20);
        save_values("assets\\save_data\\slot_1\\save_temporary.txt",add_x, add_y, "Mountain1.txt");
        int wild = 0;
        wild = wildSpawn();
        if(wild == 1){
            return 899;
        } 
    }
}

int openCave1(char file_name[], int total_data, int add_x, int add_y) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        printf("Press any key to continue..");
        getch();
        return 399;
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); 

    char map[total_data][total_data];
    
    int counter = 0;
    while (fgets(line, sizeof(line), file)) {
        for(int i = 0; i < strlen(line); i++){
            map[counter][i] = line[i];
            
        }
        counter++;
    }

    fclose(file);

    int player_x = 44 + add_x; 
    int player_y = 17 + add_y;
    int start_height = 10 + add_y; // 2010; // 14 7
    int start_width = 10 + add_x; // 2010;// 64 32
    int height =  24 + add_y;// 2024 
    int width =  74 + add_x;// 2074; // 74
    PlaySound(TEXT("assets\\music\\cave.wav"), NULL, SND_ASYNC | SND_LOOP);
    while(true) {
        clearScreen();
        draw("\033[40m===================================================================", 0, 0);
        draw("\033[40m                            Tamer Tales                            ", 0, 1);
        draw("\033[40m===================================================================", 0, 2);
        char text[1500];
        strcpy(text,"");
        int row = 3;
        bool go_left = false, go_right = false, go_up = false, go_down = false;
        for(int i = start_height; i < height; i++){
            strcat(text,"\033[0m==");

            if(map[i][start_width] == '0') {
                strcat(text,"\033[40m"); // Black
                strcat_char(text, ' ');
            } else if (map[i][start_width] == '\\') {
                strcat(text,"\033[100m"); // Gray
                strcat_char(text, '\\');
            } else if (map[i][start_width] == '|') {
                strcat(text,"\033[100m"); // Gray
                strcat_char(text, '|');
            } else if(map[i][start_width] == ' ') {
                strcat(text,"\033[100m"); // Gray 
                strcat_char(text, ' ');
            } else {
                strcat(text,"\033[100m"); // Gray
                strcat_char(text, map[i][start_width]);
            }
            
            bool first = true;
            for(int j = start_width; j < width; j++) {
                if(i == player_y + 1 && j == player_x) {
                    if(map[i][j] == ' ' || map[i][j] == '.' || map[i][j] == '-') {
                        go_down = true;
                    }
                }

                if(i == player_y - 1 && j == player_x) {
                    if(map[i][j] == ' ' || map[i][j] == '.' || map[i][j] == '-') {
                        go_up = true;
                    }
                }

                if(i == player_y && j == player_x + 1) {
                    if(map[i][j] == ' ' || map[i][j] == '.' || map[i][j] == '-') {
                        go_right = true;
                    }
                }

                if(i == player_y && j == player_x - 1) {
                    if(map[i][j] == ' ' || map[i][j] == '.' || map[i][j] == '-') {
                        go_left = true;
                    }
                }

                if(first == true){
                    first = false;
                    continue;
                }

                if(i == player_y && j == player_x) { // print player
                    strcat(text,"\033[100m"); // Gray
                    strcat_char(text,'@');   
                    continue;
                } else if(map[i][j] == map[i][j-1]) {
                    if (map[i][j] == '0') {
                        strcat_char(text, ' ');
                        continue;
                    } else if (map[i][j-1] == '\\') {
                        strcat_char(text, '\\');
                        continue;
                    } else if (map[i][j-1] == '|') {
                        strcat_char(text, '|');
                        continue;
                    } else if (map[i][j-1] == '_') {
                        strcat_char(text, '_');
                        continue;
                    } else if (map[i][j-1] == '-') {
                        strcat_char(text, '-');
                        continue;
                    } else if (map[i][j-1] == 'v') {
                        strcat_char(text, 'v');
                        continue;
                    } else if (map[i][j-1] == ' ') {
                        strcat_char(text, ' ');
                        continue;
                    } else {
                        strcat_char(text, map[i][j-1]);
                        continue;
                    }
                } else {
                    if(map[i][j] == '0') {
                        strcat(text,"\033[40m"); // Black
                        strcat_char(text,' ');
                        continue;
                    } else if (map[i][j] == '\\') {
                        strcat_char(text,'\\');
                        continue;
                    } else if (map[i][j] == '/') {
                        strcat_char(text, '/');
                        continue;
                    } else if (map[i][j] == 'o') {
                        strcat_char(text, 'o');
                        continue;
                    } else if (map[i][j] == '#') {
                        if (map[i][j-1] == '0') {
                            strcat(text,"\033[100m");  // Gray 
                            strcat_char(text,'#');
                            continue;
                        } else { 
                            strcat_char(text,'#');
                            continue;
                        }
                    } else if (map[i][j] == '|') {
                        strcat_char(text, '|');
                        continue;
                    } else if (map[i][j] == '_') {
                        strcat_char(text, '_');
                        continue;
                    } else if (map[i][j] == '-') {
                        strcat_char(text, '-');
                        continue;
                    } else if (map[i][j] == 'v') {
                        strcat_char(text, 'v');
                        continue;
                    } else if(map[i][j] == ' ') {
                        if (map[i][j-1] == '0') {
                            strcat(text,"\033[100m");  // Gray 
                            strcat_char(text,' ');
                            continue;
                        } else { 
                            strcat_char(text,' ');
                            continue;
                        }
                    } else {
                        strcat(text,"\033[100m");
                        strcat_char(text, map[i][j]);
                        continue;
                    }
                } 
            }
            strcat(text,"\033[0m"); // Reset Color
            strcat(text,"== ");
            draw(text, 0, row++);
            strcpy(text,"");
            
        }
        draw("\033[40m===================================================================", 0, row++);
        draw("\033[40m                            Tamer Tales                            ", 0, row++);
        draw("\033[40m===================================================================", 0, row++);
        // char coordinates[10];
        // char strcoor[10];
        // sprintf(strcoor, "%d", player_x);
        // strcat(coordinates, strcoor);
        // strcat(coordinates,",");
        // strcpy(strcoor,"");
        // sprintf(strcoor, "%d", player_y);
        // strcat(coordinates, strcoor);
        // draw(coordinates, 0, row++);
        row = 0;
        colorReset();
        swapBuffers();
        char input = ' ';
        input = _getch(); 
        
        switch (input) {
            case 'S':
            case 's':
                if(player_y < 70 && go_down) {
                    height++;
                    start_height++;
                    player_y++;
                    add_y++;
                }
                break;
            case 'W':
            case 'w':
                if(player_y > 17 && go_up) {
                    height--;
                    start_height--;
                    player_y--;
                    add_y--;
                }
                break;
            case 'A':
            case 'a':
                if(player_x > 34 && go_left) {
                    width--;
                    start_width--;
                    player_x--;
                    add_x--;
                }
                break;
            case 'D':
            case 'd':
                if(player_x < 167 && go_right){ 
                    width++;
                    start_width++;
                    player_x++;
                    add_x++;
                }
                break;
            case 'B':
            case 'b':
                break;
            case 'M':
            case 'm':
                return 499;
                break;
            case '\033':
                save_values("assets\\save_data\\slot_1\\save_temporary.txt", add_x, add_y, "Cave1.txt");
                return 399;
            case '\r': // press 'enter'
            default:
                int a = input;
                switch (a) {
                case 72: //up
                    if(player_y > 17 && go_up) {
                        height--;
                        start_height--;
                        player_y--;
                        add_y--;
                    }
                    break;
                case 75: //left
                    if(player_x > 34 && go_left) {
                        width--;
                        start_width--;
                        player_x--;
                        add_x--;
                    }
                    break;
                case 77: //right
                    if(player_x < 167 && go_right){ 
                        width++;
                        start_width++;
                        player_x++;
                        add_x++;
                    }
                    break;
                case 80: //down
                    if(player_y < 167 && go_down) {
                        height++;
                        start_height++;
                        player_y++;
                        add_y++;
                    }
                    break;
                }
                break;
        } 
        if(player_x == 108 && player_y == 34){
            save_values("assets\\save_data\\slot_1\\save_temporary.txt", 6, 10, "Mountain1.txt");
            return 399;
        }
        if(player_x == 109 && player_y == 34){
            save_values("assets\\save_data\\slot_1\\save_temporary.txt", 7, 10, "Mountain1.txt");
            return 399;
        }
        if(player_x == 110 && player_y == 34){
            save_values("assets\\save_data\\slot_1\\save_temporary.txt", 8, 10, "Mountain1.txt");
            return 399;
        }
        if(player_x == 111 && player_y == 34){
            save_values("assets\\save_data\\slot_1\\save_temporary.txt", 9, 10, "Mountain1.txt");
            return 399;
        }
        // if(player_x == 70 && player_y == 26) {
        //     save_values("assets\\save_data\\slot_1\\save_temporary.txt", 2, 17, "House2.txt");
        //     return 399;
        // }
        // if(player_x == 69 && player_y == 26) {
        //     save_values("assets\\save_data\\slot_1\\save_temporary.txt", 2, 17, "House2.txt");
        //     return 399;
        // }
        Sleep(20);
        save_values("assets\\save_data\\slot_1\\save_temporary.txt",add_x, add_y, "Cave1.txt");
        // int wild = 0;
        // wild = wildSpawn();
        // if(wild == 1){
        //     PlaySound(NULL, NULL, SND_ASYNC);
        //     swapBuffers();
        //     PlaySound(TEXT("assets\\music\\battle.wav"), NULL, SND_ASYNC | SND_LOOP);
        //     transition();
        //     // wildPokemon();
        //     // printbattle();
            
        //     wildPokemonSpawner();
        //     char battle_input = '\r';
           
        //     printf("Press enter to continue..");
        //     while (true)
        //     {
        //         battle_input = _getch(); 
        //         if(battle_input == '\r') break;
        //     }
        //     return 399;
        //     PlaySound(TEXT("assets\\music\\town.wav"), NULL, SND_ASYNC | SND_LOOP);
        // } 
    }
}