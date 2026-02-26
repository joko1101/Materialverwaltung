// Autor: Joachim Schneider

#include "util.h"

void clearTerminal(char *header)
{
    system("clear");
    printf("\n%s\n\nInfo: 'x' zum Verlassen.\n", header);
}
