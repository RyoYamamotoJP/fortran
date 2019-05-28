#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stddef.h>
#include <stdint.h>

void fquicksort(float *restrict a, size_t lo, size_t hi, size_t *restrict ip);
void iquicksort(int32_t *restrict a, size_t lo, size_t hi, size_t *restrict ip);

#endif /* QUICKSORT_H */
