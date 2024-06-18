#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

/*
Text Color:
Black: \033[0;30m
Red: \033[0;31m
Green: \033[0;32m
Yellow: \033[0;33m
Blue: \033[0;34m
Magenta: \033[0;35m
Cyan: \033[0;36m
White: \033[0;37m
Background Color:

Black: \033[40m
Red: \033[41m
Green: \033[42m
Yellow: \033[43m
Blue: \033[44m
Magenta: \033[45m
Cyan: \033[46m
White: \033[47m
Reset Color: \033[0m
*/

void colorReset();
void colorChar(char color[], char a);
void colorText(char color[], char text[]);
void colorBackgroundChar(char color[], char a);
void colorBackgroundText(char color[], char text[]);
void colorCustomText(int r, int g, int b, char text[]);
void colorBackgroundCustomText(int r, int g, int b, char text[]);
void colorDefault(int r, int g, int b);
void colorDefaultBackground(int r, int g, int b);
void colorBackgroundCustomChar(int r, int g, int b, char c);

void colorTextunderline(char color[], char text[]);

/*
int main() {
    colorChar("black", 'A');
    colorChar("red", 'B');
    colorChar("green", 'C');
    colorChar("yellow", 'D');
    colorChar("blue", 'E');
    colorChar("magenta", 'F');
    colorChar("cyan", 'G');
    colorChar("white", 'H');
    colorChar("bright black", 'I');
    colorChar("bright red", 'J');
    colorChar("bright green", 'K');
    colorChar("bright yellow", 'L');
    colorChar("bright blue", 'M');
    colorChar("bright magenta", 'N');
    colorChar("bright cyan", 'O');
    colorChar("bright white", 'P');
    colorChar("gray", 'Q');
    printf("\n");

    colorBackgroundChar("black", 'A');
    colorBackgroundChar("red", 'B');
    colorBackgroundChar("green", 'C');
    colorBackgroundChar("yellow", 'D');
    colorBackgroundChar("blue", 'E');
    colorBackgroundChar("magenta", 'F');
    colorBackgroundChar("cyan", 'G');
    colorBackgroundChar("white", 'H');
    colorBackgroundChar("gray", 'I'); 
    colorBackgroundChar("bright black", 'J');
    colorBackgroundChar("bright red", 'K');
    colorBackgroundChar("bright green", 'L');
    colorBackgroundChar("bright yellow", 'M');
    colorBackgroundChar("bright blue", 'N');
    colorBackgroundChar("bright magenta", 'O');
    colorBackgroundChar("bright cyan", 'P');
    colorBackgroundChar("bright white", 'Q');

    colorBackgroundText("black", "Black background\n");
    colorBackgroundText("red", "Red background\n");
    colorBackgroundText("green", "Green background\n");
    colorBackgroundText("yellow", "Yellow background\n");
    colorBackgroundText("blue", "Blue background\n");
    colorBackgroundText("magenta", "Magenta background\n");
    colorBackgroundText("cyan", "Cyan background\n");
    colorBackgroundText("white", "White background\n");
    colorBackgroundText("gray", "Gray background\n"); 
    printf("\n");

    colorText("black", "Black text\n");
    colorText("red", "Red text\n");
    colorText("green", "Green text\n");
    colorText("yellow", "Yellow text\n");
    colorText("blue", "Blue text\n");
    colorText("magenta", "Magenta text\n");
    colorText("cyan", "Cyan text\n");
    colorText("white", "White text\n");
    colorText("gray", "Gray text\n"); 

    colorText("bright black", "Bright black text\n");
    colorText("bright red", "Bright red text\n");
    colorText("bright green", "Bright green text\n");
    colorText("bright yellow", "Bright yellow text\n");
    colorText("bright blue", "Bright blue text\n");
    colorText("bright magenta", "Bright magenta text\n");
    colorText("bright cyan", "Bright cyan text\n");
    colorText("bright white", "Bright white text\n");

    printf("\n");

    colorBackgroundText("bright black", "Bright black background\n");
    colorBackgroundText("bright red", "Bright red background\n");
    colorBackgroundText("bright green", "Bright green background\n");
    colorBackgroundText("bright yellow", "Bright yellow background\n");
    colorBackgroundText("bright blue", "Bright blue background\n");
    colorBackgroundText("bright magenta", "Bright magenta background\n");
    colorBackgroundText("bright cyan", "Bright cyan background\n");
    colorBackgroundText("bright white", "Bright white background\n");

    for (int i = 0; i < 100; i++) {
        int r = rand() % 256; 
        int g = rand() % 256; 
        int b = rand() % 256; 
     
        char colorName[20];
        sprintf(colorName, "Color_%d_%d_%d", r, g, b);
        
        colorCustomText(r, g, b, colorName);
        printf("\n");
    }

    for (int i = 0; i < 100; i++) {
        int r = rand() % 256; 
        int g = rand() % 256;
        int b = rand() % 256; 
        
        char colorName[20];
        sprintf(colorName, "BackgroundColor_%d_%d_%d", r, g, b);
        
        colorBackgroundCustomText(r, g, b, colorName);
        printf("\n");
    }

    return 0;
}
*/


void colorReset() {
    printf("\033[0m");
}

void colorChar(char color[], char a) {
    strlwr(color); 

    if (strcmp(color, "black") == 0) {
        printf("\033[0;30m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "red") == 0) {
        printf("\033[0;31m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "green") == 0) {
        printf("\033[0;32m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "yellow") == 0) {
        printf("\033[0;33m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "blue") == 0) {
        printf("\033[0;34m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "magenta") == 0) {
        printf("\033[0;35m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "cyan") == 0) {
        printf("\033[0;36m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "white") == 0) {
        printf("\033[0;37m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "bright black") == 0 || strcmp(color, "gray") == 0) {
        printf("\033[1;30m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "bright red") == 0) {
        printf("\033[1;31m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "bright green") == 0) {
        printf("\033[1;32m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "bright yellow") == 0) {
        printf("\033[1;33m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "bright blue") == 0) {
        printf("\033[1;34m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "bright magenta") == 0) {
        printf("\033[1;35m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "bright cyan") == 0) {
        printf("\033[1;36m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "bright white") == 0) {
        printf("\033[1;37m");
        printf("%c", a);
        colorReset();
        return;
    }

    printf("%c", a);
    colorReset();
}

void colorBackgroundChar(char color[], char a) {
    strlwr(color);  

    if (strcmp(color, "black") == 0) {
        printf("\033[40m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "red") == 0) {
        printf("\033[41m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "green") == 0) {
        printf("\033[42m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "yellow") == 0) {
        printf("\033[43m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "blue") == 0) {
        printf("\033[44m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "magenta") == 0) {
        printf("\033[45m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "cyan") == 0) {
        printf("\033[46m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "white") == 0) {
        printf("\033[47m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "bright black") == 0 || strcmp(color, "gray") == 0) {
        printf("\033[100m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "bright red") == 0) {
        printf("\033[101m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "bright green") == 0) {
        printf("\033[102m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "bright yellow") == 0) {
        printf("\033[103m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "bright blue") == 0) {
        printf("\033[104m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "bright magenta") == 0) {
        printf("\033[105m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "bright cyan") == 0) {
        printf("\033[106m");
        printf("%c", a);
        colorReset();
        return;
    }

    if (strcmp(color, "bright white") == 0) {
        printf("\033[107m");
        printf("%c", a);
        colorReset();
        return;
    }

    printf("%c", a);
    colorReset();
}

void colorBackgroundText(char color[], char text[]) {
    strlwr(color);  
    if (strcmp(color, "black") == 0) {
        printf("\033[40m");
    } else if (strcmp(color, "red") == 0) {
        printf("\033[41m");
    } else if (strcmp(color, "green") == 0) {
        printf("\033[42m");
    } else if (strcmp(color, "yellow") == 0) {
        printf("\033[43m");
    } else if (strcmp(color, "blue") == 0) {
        printf("\033[44m");
    } else if (strcmp(color, "magenta") == 0) {
        printf("\033[45m");
    } else if (strcmp(color, "cyan") == 0) {
        printf("\033[46m");
    } else if (strcmp(color, "white") == 0) {
        printf("\033[47m");
    } else if (strcmp(color, "bright black") == 0 || strcmp(color, "gray") == 0) {
        printf("\033[100m");
    } else if (strcmp(color, "bright red") == 0) {
        printf("\033[101m");
    } else if (strcmp(color, "bright green") == 0) {
        printf("\033[102m");
    } else if (strcmp(color, "bright yellow") == 0) {
        printf("\033[103m");
    } else if (strcmp(color, "bright blue") == 0) {
        printf("\033[104m");
    } else if (strcmp(color, "bright magenta") == 0) {
        printf("\033[105m");
    } else if (strcmp(color, "bright cyan") == 0) {
        printf("\033[106m");
    } else if (strcmp(color, "bright white") == 0) {
        printf("\033[107m");
    } else {
        printf("\033[0m");
    }

    printf("%s", text);
    colorReset();  
}

void colorText(char color[], char text[]) {
    strlwr(color); 
    if (strcmp(color, "black") == 0) {
        printf("\033[30m");
    } else if (strcmp(color, "red") == 0) {
        printf("\033[31m");
    } else if (strcmp(color, "green") == 0) {
        printf("\033[32m");
    } else if (strcmp(color, "yellow") == 0) {
        printf("\033[33m");
    } else if (strcmp(color, "blue") == 0) {
        printf("\033[34m");
    } else if (strcmp(color, "magenta") == 0) {
        printf("\033[35m");
    } else if (strcmp(color, "cyan") == 0) {
        printf("\033[36m");
    } else if (strcmp(color, "white") == 0) {
        printf("\033[37m");
    } else if (strcmp(color, "gray") == 0 || strcmp(color, "bright black") == 0) {
        printf("\033[1;30m");
    } else if (strcmp(color, "bright red") == 0) {
        printf("\033[1;31m");
    } else if (strcmp(color, "bright green") == 0) {
        printf("\033[1;32m");
    } else if (strcmp(color, "bright yellow") == 0) {
        printf("\033[1;33m");
    } else if (strcmp(color, "bright blue") == 0) {
        printf("\033[1;34m");
    } else if (strcmp(color, "bright magenta") == 0) {
        printf("\033[1;35m");
    } else if (strcmp(color, "bright cyan") == 0) {
        printf("\033[1;36m");
    } else if (strcmp(color, "bright white") == 0) {
        printf("\033[1;37m");
    } else {
        printf("\033[0m");
    }

    printf("%s", text);
    colorReset();  
}

void colorCustomText(int r, int g, int b, char text[]) {
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        r = 255;
        g = 255;
        b = 255;
    }

    printf("\033[38;2;%d;%d;%dm", r, g, b);
    printf("%s", text);
    colorReset();
}



void colorDefault(int r, int g, int b) {
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        r = 255;
        g = 255;
        b = 255;
    }
    printf("\033]10;rgb:%02x/%02x/%02x\033\\", r, g, b);
}

void colorDefaultBackground(int r, int g, int b) {
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        r = 255;
        g = 255;
        b = 255;
    }
    printf("\033]11;rgb:%02x/%02x/%02x\033\\", r, g, b);
}

void colorBackgroundCustomText(int r, int g, int b, char text[]) {
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        r = 255;
        g = 255;
        b = 255;
    }
    printf("\033[48;2;%d;%d;%dm", r, g, b);
    printf("%s", text);
    colorReset();
}

void colorBackgroundCustomChar(int r, int g, int b, char c) {
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        r = 255;
        g = 255;
        b = 255;
    }
    printf("\033[48;2;%d;%d;%dm", r, g, b);
    printf("%c", c);
    colorReset();
}


void colorTextunderline(char color[], char text[]) {
    
    strlwr(color); 
    if(strcmp(color, "green") == 0){
        printf("\033[4;32m"); // under_line green
    }
    else if(strcmp(color, "red")==0){
        printf("\033[4;31m"); // under_line red
    }
    else if(strcmp(color, "yellow")==0){
        printf("\033[4;33m"); // under_line yellow
    }
    else if(strcmp(color, "blue")==0){
        printf("\033[4;34m"); // under_line blue
    }
    else if(strcmp(color, "magenta")==0){
        printf("\033[4;35m"); // under_line magenta
    }
    else if(strcmp(color, "cyan")==0){
        printf("\033[4;36m"); // under_line cyan
    }
    else if(strcmp(color, "white")==0){
        printf("\033[4;37m"); // under_line white
    }
    else{
        printf("\033[0m]");
    }
    printf("%s", text);
    colorReset();  
}


