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

#define MAX_LINE_LENGTH 200
#define SCREEN_WIDTH  74
#define SCREEN_HEIGHT 24
#define TRANSITION_FRAMES 24

void strcat_char(char *str, char c);
int openMap(char file_name[], int total_data, int add_x, int add_y);
int openTown1(char file_name[], int total_data, int add_x, int add_y);
void printData(char file_name[], int total_data);

void dialog();
void writelineC(char *text, int time); // time is set for each character output
void writeC(char *text, int time); // Doesn`t include \n
void clearScreen();
void drawCircle(int radius);
void transition();
int wildSpawn();

int chance = -15;

void strcat_char(char *str, char c) {
    size_t len = strlen(str);
    str[len] = c;
    str[len + 1] = '\0';
}

void save_values(char *text, int x, int y, char *map) {
    FILE *file_save = fopen(text, "w");
    if (file_save == NULL) {
        fprintf(stderr, "Could not open file\n");
        printf("Press any key to continue..");
        getch();
        return;
    }

    fprintf(file_save, "%d,%d\n", x, y);
    fprintf(file_save, "%s\n", map);
    fclose(file_save);
}

void read_values(char *text, int *x, int *y, char *map) {
    FILE *file_save = fopen(text, "r");
    if (file_save == NULL) {
        fprintf(stderr, "Could not open file\n");
        printf("Press any key to continue..");
        getch();
        return;
    }

    fscanf(file_save, "%d,%d\n", x, y);
    fscanf(file_save, "%s", map);
    fclose(file_save);
}


int openMap(char file_name[], int total_data, int add_x, int add_y) {
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
        // printf("%d\n", chance);
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
                strcat(text,"\033[42m"); // Green
                strcat_char(text, '\\');
            } else if (map[i][start_width] == '|') {
                strcat(text,"\033[42m"); // Green
                strcat_char(text, '|');
            } else if(map[i][start_width] == ' ') {
                strcat(text,"\033[42m"); // Green 
                strcat_char(text, ' ');
            } else {
                strcat(text,"\033[42m"); // Green
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
                    strcat(text,"\033[42m"); // green
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
                            strcat(text,"\033[42m");  // green 
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
                            strcat(text,"\033[42m");  // green 
                            strcat_char(text,' ');
                            continue;
                        } else { 
                            strcat_char(text,' ');
                            continue;
                        }
                    } else {
                        strcat(text,"\033[42m");
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
                if(player_x < 167 &&  go_right){ 
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
                save_values("assets\\save_data\\slot_1\\save_temporary.txt", add_x, add_y, "PalleteTown.txt");
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
        if(player_x == 167 && player_y == 22){
            save_values("assets\\save_data\\slot_1\\save_temporary.txt", -9, 27, "Mountain1.txt");
            return 399;
        }
        if(player_x == 167 && player_y == 23){
            save_values("assets\\save_data\\slot_1\\save_temporary.txt", -9, 28, "Mountain1.txt");
            return 399;
        }
        if(player_x == 113 && player_y == 30){
            save_values("assets\\save_data\\slot_1\\save_temporary.txt", 2, 17, "House1.txt");
            return 399;
        }
        if(player_x == 70 && player_y == 27) {
            save_values("assets\\save_data\\slot_1\\save_temporary.txt", 2, 17, "House2.txt");
            return 399;
        }
        if(player_x == 69 && player_y == 27) {
            save_values("assets\\save_data\\slot_1\\save_temporary.txt", 2, 17, "House2.txt");
            return 399;
        }
        Sleep(20);
    }
}

void drawCircle(int radius) {
    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;
    
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            int dx = centerX - x;
            int dy = centerY - y;
            if (sqrt(dx * dx + dy * dy) < radius) {
                printf("O");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void transition() {
    for (int frame = 0; frame <= TRANSITION_FRAMES; frame++) {
        system("cls");
        
        float progress = (float)frame / (float)TRANSITION_FRAMES;
        int radius = (int)(progress * (SCREEN_WIDTH > SCREEN_HEIGHT ? SCREEN_WIDTH : SCREEN_HEIGHT) / 2);
        
        drawCircle(radius);
        
        usleep(10000);  // Sleep for 100,000 microseconds (0.1 seconds)
    }
    
    system("cls");
}

int wildSpawn(){
    int rate = rand() % 100+1;
    if(rate > chance){
        chance++;
        return 0;
    }
    else{
        chance = -5;
        return 1;
    }
}

void writelineC(char *text, int time) {
	for(int i = 0; i < strlen(text); i++) {
		printf("%c", text[i]);
		Sleep(time);
	}
	printf("\n");
}

void writeC(char *text, int time) {
	for(int i = 0; i < strlen(text); i++) {
		printf("%c", text[i]);
		Sleep(time);
	}
}

void dialog() {
    system("cls");
    // printf("Hello Trainers!");
    writelineC("Hello trainers!", 10);
    writelineC("Welcome to the laboratorium!, I need your help!", 10);
    getch();

    system("cls");
    writelineC("I have a tools to collect data from pokemon all over the World!", 10);
    writelineC("Its called Pokedex, but I need you to collect and find all pokemon to fill the pokedex", 10);
    getch();

    system("cls");
    writelineC("Thank you Trainers!", 10);
    writelineC("Goodluck on your Journey!", 10);
    getch();

}



