#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "q_list.h"

#include "str/q_str.h"

struct person{
    int age;
    char *name;
};
static void print_(void *data){
    char* s = (char*)data;
    printf("%s", s);
}

int main(int argc, char** argv)
{     
    return (EXIT_SUCCESS);
}