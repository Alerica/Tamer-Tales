// void searchPokemon(int wildIndex);
// int searchMove();
// void wildPokemon();
// void inventori();
// void printbattle();

#define MAX_NAME_LENGTH 50
#define MAX_TYPE_LENGTH 20

typedef struct {
    int index;
    char name[MAX_NAME_LENGTH];
    char type[MAX_TYPE_LENGTH];
    char category[MAX_TYPE_LENGTH];
    int power;
    int accuracy;
    int pp;
} moves;

typedef struct {
    int number;
    char name[MAX_NAME_LENGTH];
    char type1[MAX_TYPE_LENGTH];
    char type2[MAX_TYPE_LENGTH];
    int hp;
    int attack;
    int defense;
    int sp_attack;
    int sp_defense;
    int speed;
} Pokemon;

typedef struct{
    Pokemon pokemon;
    moves moves[4];
    int catch_rate;
    int exp;
    int level_up_exp;
    int level;
    int affinity;
} PokemonBattle;

void searchPokemon(int wildIndex, PokemonBattle *wild);
int searchMove(moves move[], PokemonBattle *wild);
void wildPokemon(PokemonBattle *wild);
void printbattle(PokemonBattle *wild);
void wildPokemonSpawner();