#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

#define MAX_LINE_LENGTH 200

void readDialogFromFile(char *file_name);
int main () {

}


void readDialogFromFile(char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        printf("Press any key to continue..");
        getch();
        return 399;
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); 
    char NPC_NAME[16];
    strcpy(NPC_NAME, line);
    NPC_NAME[strlen(NPC_NAME) - 1] = '\0';
    printf("%s", line);

    while(fgets(line, sizeof(line), file)) {
        printf("%-15s: %s", line);
    }
}
