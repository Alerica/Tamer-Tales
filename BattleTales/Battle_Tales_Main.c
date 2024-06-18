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


int main() {
    
    initConsole();
    enableVirtualTerminalProcessing(); // Jangan di hapus!!
    swapBuffers();
    intro();
    int a = -1;
    while(a != 6) {
        a = BT_mainMenu();
        BT_mainMenuNavigation(a);
        // getch();
    }
    cleanupConsole();
    return 0;
}


