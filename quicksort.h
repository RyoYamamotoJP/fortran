#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stddef.h>
#include <stdint.h>

void fsort(float *restrict a, size_t n, size_t *restrict ip);
void isort(int32_t *restrict a, size_t n, size_t *restrict ip);

#endif /* QUICKSORT_H */
