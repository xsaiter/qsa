#ifndef QSA_STR_H
#define QSA_STR_H

#include <stdbool.h>

#include "../qsa_vector.h"

#ifdef __cplusplus
extern "C" {
#endif

    void qsa_str_remove_symbols(char *s, char c);
    void qsa_str_remove_spaces(char *s);
    bool qsa_str_is_palindrome(const char *s);

    char **qsa_str_split_by(char *s, char delim);
    int qsa_str_count_parts(const char *s, char delim);

    int *qsa_str_prefix_func(const char *s, size_t *rsize);
    int *qsa_str_z_func(const char *s, size_t *rsize);

    bool qsa_str_check_balanced_round_brackets(char *s);    
    
    int qsa_str_boyer_moore(const char *s, const char *p);
    int qsa_str_kmp(const char *s, const char *p);    

#ifdef __cplusplus
}
#endif

#endif /* QSA_STR_H */