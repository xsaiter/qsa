#include <stdio.h>
#include <stdlib.h>

#include "q_utils.h"

inline void die(const char *text)
{
    perror(text);
    exit(EXIT_FAILURE);
}

void *xmalloc(size_t size)
{
    void *p = malloc(size);
    if(!p){
        die("xmalloc");
    }    
    return p;
}

void *xmalloc0(size_t size)
{
   
    void *p = calloc(1, size);
    if(!p){
        die("xmalloc0");
    }    
    return p;
}