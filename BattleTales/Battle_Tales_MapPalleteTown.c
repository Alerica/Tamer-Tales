#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>


#include "Battle_Tales_Display.h"
#include "Battle_Tales_UI.h"
#include "Battle_Tales_FileProcessing.h"
#include "Battle_Tales_Performance.h"
#include "Battle_Tales_PokemonStruct.h"
#include "Battle_Tales_Inventory.h"
#include "Battle_Tales_Map.h"

int main() {
    int exitCode, x, y;
    char map[50]; // Read from saves temporary
    

    initConsole();
    enableVirtualTerminalProcessing(); // Don`t delete this

    read_values("assets\\save_data\\slot_1\\save_temporary.txt",&x,&y, map);
    char path[40] = "assets\\map\\";
    strcat(path,map);  
    if(strcmp(map,"PalleteTown.txt") == 0){
        exitCode = openMap(path, 210, x ,y); // Change the path with map assets
    } else if(strcmp(map,"House1.txt") == 0) {
        exitCode = openMapHouse1(path, 210, x , y);
    } else if (strcmp(map,"House2.txt") == 0) {
        exitCode = openMapHouse2(path, 210, x , y);
    } else if (strcmp(map,"Mountain1.txt") == 0) {
        exitCode = openMountain(path, 210, x , y);
    } else if (strcmp(map,"Cave1.txt") == 0 ) {
        exitCode = openCave1(path, 210, x , y);
    }
    
    cleanupConsole();
    return exitCode;
}