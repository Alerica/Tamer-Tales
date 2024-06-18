int openMap(char file_name[], int total_data, int add_x, int add_y);

void read_values(char *text, int *x, int *y, char *map);
void save_values(char *text, int x, int y, char *map);
void strcat_char(char *str, char c);
int wildSpawn();

void dialog();
void writelineC(char *text, int time); // time is set for each character output
void writeC(char *text, int time); // Doesn`t include \n