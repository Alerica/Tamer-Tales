#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main() {

    system("gcc -o Battle_Tales_MapPalleteTown Battle_Tales_MapPalleteTown.c Battle_Tales_Display.c Battle_Tales_UI.c Battle_Tales_FileProcessing.c Battle_Tales_Performance.c  Battle_Tales_PokemonStruct.c Battle_tales_Inventory.c Battle_Tales_Map.c -lwinmm");
    system("gcc -o Battle_Tales Battle_Tales_Main.c Battle_Tales_Display.c Battle_Tales_UI.c Battle_Tales_FileProcessing.c Battle_Tales_Performance.c  Battle_tales_Inventory.c Battle_Tales_PokemonStruct.c Battle_Tales_Map.c -lwinmm");
    system("gcc -o Battle_Tales_Battle Battle_Tales_PokemonStruct2.c Battle_Tales_UI.c");
}


