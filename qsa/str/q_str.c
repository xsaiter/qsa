#include <stdlib.h>
#include <string.h>

#include "q_str.h"

void q_str_remove_symbols(char *s, char c)
{
    char *p = s;
    while (*p != '\0') {
        if (*p != c) {
            *s++ = *p++;
        } else {
            p++;
        }
    }
}

void q_str_remove_spaces(char *s)
{
    q_str_remove_symbols(s, ' ');
}

bool q_str_is_palindrome(const char *s)
{
    int i = 0, j = strlen(s) - 1;
    while (i < j) {
        if (s[i++] != s[j--]) {
            return false;
        }
    }
    return true;
}

int q_str_count_parts(const char *s, char delim)
{
    int n = 1;
    const char *p = s;

    while (*p) {
        if (*p == delim) {
            ++n;
        }
        ++p;
    }

    return n;
}

char **q_str_split_by(char *s, char delim)
{
    int n = q_str_count_parts(s, delim);
    char ** res = malloc(n * sizeof (char*));

    if (!res) {
        return NULL;
    }

    char delims[2];
    delims[0] = delim;
    delims[1] = 0;

    int pos = 0;
    char *part = strtok(s, delims);    

    while (part) {
        *(res + pos++) = strdup(part);
        part = strtok(NULL, delims);
    }

    *(res + pos) = NULL;

    return res;
}

int *q_str_prefix_func(const char *s, size_t *res_size)
{
    size_t n = strlen(s);

    int *res = malloc(sizeof(int)*n);
    if(!res){
        return NULL;
    }
    
    *res_size = n;

    for (int i = 0; i < n; ++i) {
        for (int k = 1; k <= i; ++k) {
            int j = 0;
            while (j + k <= i && s[j] == s[j + k]) {
                ++j;
            }

            if (j + k == i + 1) {
                res[i] = j;                
                break;
            }
        }
    }

    return res;
}

int *q_str_z_func(const char *s, size_t *res_size)
{
    size_t n = strlen(s);

    int *res = malloc(sizeof(int)*n);
    if(!res){
        return res;
    }
    *res_size = n;

    res[0] = n;    

    for (int i = 1; i < n; ++i) {
        int j = i;
        while (j < n && s[j] == s[j - i]) {
            ++j;
        }

        int k = j - i;
        res[i] = k;        
    }

    return res;
}

bool q_check_balanced_round_brackets(char *s)
{
    int n = 0;
    while (*s != '\0') {
        if (*s == '(') {
            ++n;
        } else if (*s == ')') {
            --n;
        }
        if (n < 0) {
            return false;
        }
        ++s;
    }

    return (n == 0);
}

int q_boyer_moore(const char *s, const char *p)
{
    int n, m, i;

    n = strlen(s);
    m = strlen(p);

    int d[256] = {-1};

    int shift = -1;
    for (i = m - 2; i >= 0; --i) {
        int j = m - 1;
        while (j >= 0) {
            if (s[i + j] != p[j]) {
                if (d[s[i + j]] == -1) {
                    shift = m;
                } else {
                    shift = d[s[i + j]];
                }
                break;
            }
            --j;
        }

        if (j == -1) {
            return i;
        }
    }

    return -1;
}

int q_kmp(const char *s, const char *p)
{
    int n = strlen(s);
    int m = strlen(p);

    int j = 0;
    int res = -1;

    size_t pfx_size = 0;
    
    int *pfx = q_str_prefix_func(p, &pfx_size);
    if(!pfx){
        return res;
    }

    for (int i = 0; i < n; ++i) {
        while (j > 0 && (j >= m || p[j] != s[i])) {
            j = pfx[j-1];
        }

        if (s[i] == p[j]) {
            j++;
        }

        if (j == m) {            
            res = i - j + 1;
            break;
        }
    }
    
    free(pfx);

    return res;
}