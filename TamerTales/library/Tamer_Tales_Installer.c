#include <stdio.h>
#include <stdlib.h>

int main() {
    system("gcc -o Tamer_Tales Tamer_Tales_Main.c Tamer_Tales_FileProcessing.c Tamer_Tales_Display.c Tamer_Tales_UI.c");
    system("Tamer_Tales.exe");
}