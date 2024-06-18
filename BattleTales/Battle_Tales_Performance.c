#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include "Battle_Tales_Display.h"
#include "Battle_Tales_UI.h"
#include "Battle_Tales_FileProcessing.h"
#include <windows.h>

WORD textColor = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;

void enableVirtualTerminalProcessing();

void initConsole();
void clearScreen();
void draw(char text[], int x, int y);
void swapBuffers();
void cleanupConsole();
void intToString(int num, char *str);

void setTextColor(WORD foregroundColor, WORD backgroundColor);

HANDLE hConsole;
HANDLE hBuffer;


void enableVirtualTerminalProcessing() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        return;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        return;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) {
        return;
    }
}

void intToString(int num, char *str) {
    sprintf(str, "%d", num);
}
void initConsole() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    hBuffer = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    SetConsoleScreenBufferSize(hBuffer, csbi.dwSize);
    SetConsoleActiveScreenBuffer(hBuffer);
    swapBuffers();
}

void clearScreen() {
    COORD coordScreen = {0, 0}; 
    DWORD charsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD consoleSize;

    GetConsoleScreenBufferInfo(hBuffer, &csbi);
    consoleSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hBuffer, (TCHAR) ' ', consoleSize, coordScreen, &charsWritten);
    FillConsoleOutputAttribute(hBuffer, csbi.wAttributes, consoleSize, coordScreen, &charsWritten);
    SetConsoleCursorPosition(hBuffer, coordScreen);
}

void draw(char text[], int x, int y) {
    COORD coord = {x, y};
    DWORD charsWritten;
    WriteConsoleOutputCharacter(hBuffer, text, strlen(text), coord, &charsWritten);
}

void swapBuffers() { 
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    SetConsoleActiveScreenBuffer(hBuffer);
    HANDLE temp = hConsole;
    hConsole = hBuffer;
    hBuffer = temp;
    DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD coordScreen = {0, 0};
    DWORD charsWritten;
    FillConsoleOutputAttribute(hConsole, textColor, consoleSize, coordScreen, &charsWritten);
}

void cleanupConsole() {
    SetConsoleActiveScreenBuffer(hConsole);
    CloseHandle(hBuffer);
    CloseHandle(hConsole);
}

void setTextColor(WORD foregroundColor, WORD backgroundColor) {
    WORD attributes = foregroundColor | backgroundColor;
    SetConsoleTextAttribute(hBuffer, attributes);
}
