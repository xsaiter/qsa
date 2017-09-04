#include <stdio.h>
#include <stdlib.h>

#include "q_utils.h"

void die(const char *text)
{
    perror(text);
    exit(EXIT_FAILURE);
}