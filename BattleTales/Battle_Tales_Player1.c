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


int main() {
    int exitCode;
    enableVirtualTerminalProcessing(); // Jangan di hapus!!
    initConsole();
    int x, y;
    // read_values("assets\\save_data\\slot_1\\save_temporary.txt",&x,&y);  
    exitCode = openMap("cobatown.txt", 210, x ,y);
    if (exitCode == 799) {
        openTown1("canvas.txt", 210, 0, 0);
    }
    cleanupConsole();
    return exitCode;
}
