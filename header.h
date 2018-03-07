#include "utils.h"
#include <string.h>
#include <signal.h>

#define SECONDAIRE_N 0
#define SECONDAIRE_PID_PRIMAIRE 1
#define SECONDAIRE_PROGRAMME 2
#define TRAFIC_I 0
#define TRAFIC_PID_STI 1
#define TRAFIC_DELAI_MIN_REQUETE 2
#define TRAFIC_DELAI_MAX_REQUETE 3
#define TRAFIC_PROGRAMME 4

//valeur global
int state;
char *string_state;

int min(int a, int b);
