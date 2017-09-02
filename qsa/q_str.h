#ifndef Q_STR_H
#define Q_STR_H

#include <stdbool.h>

#include "q_vector.h"

#ifdef __cplusplus
extern "C" {
#endif

    void q_str_remove_symbols(char *s, char c);
    void q_str_remove_spaces(char *s);
    bool q_str_is_palindrome(const char *s);

    char **q_str_split_by(char *s, char delim);
    int q_str_count_parts(const char *s, char delim);

    int *q_str_prefix_func(const char *s, size_t *rsize);
    int *q_str_z_func(const char *s, size_t *rsize);

    bool q_check_balanced_round_brackets(char *s);    
    
    int q_boyer_moore(const char *s, const char *p);
    int q_kmp(const char *s, const char *p);    

#ifdef __cplusplus
}
#endif

#endif /* Q_STR_H */