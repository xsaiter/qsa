#ifndef Q_DICT_H
#define Q_DICT_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        void *key;
        void *value;
    } q_dict_pair;

    typedef struct {
        q_dict_pair **pairs;
        int len;
    } q_dict;


#ifdef __cplusplus
}
#endif

#endif /* Q_DICT_H */