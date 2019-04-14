#include <stdio.h>
#include <stdlib.h>

#include "qsa_utils.h"

#define FNV_32_PRIME (0x01000193)

unsigned int qsa_hash_str(const void *arg) {
  return qsa_fnv1_hash((char *)arg);
}

unsigned int qsa_fnv1_hash(char *buf) {
  unsigned int hval = 0x811c9dc5;

  while (*buf) {
    hval ^= (unsigned int)*buf++;
    hval *= FNV_32_PRIME;
  }

  return hval;
}
