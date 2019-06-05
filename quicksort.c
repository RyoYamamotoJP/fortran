#include "quicksort.h"

struct partition {
	size_t left;
	size_t right;
};

static inline void fswap(float *restrict a, size_t i, size_t j)
{
	float temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

static inline void iswap(int32_t *restrict a, size_t i, size_t j)
{
	int32_t temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

static inline void size_tswap(size_t *restrict a, size_t i, size_t j)
{
	size_t temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

static inline void fswap_elements(float *restrict a, size_t i, size_t j, size_t *restrict ip)
{
	fswap(a, i, j);
	if (ip)
		size_tswap(ip, i, j);
}

static inline void iswap_elements(int32_t *restrict a, size_t i, size_t j, size_t *restrict ip)
{
	iswap(a, i, j);
	if (ip)
		size_tswap(ip, i, j);
}

static inline size_t mid_index(size_t lo, size_t hi)
{
	return lo + ((hi - lo) >> 1);
}

static inline float fmedian3(float *restrict a, size_t lo, size_t hi, size_t *restrict ip)
{
	size_t mid = mid_index(lo, hi);

	if (a[lo] > a[mid])
		fswap_elements(a, lo, mid, ip);
	if (a[lo] > a[hi])
		fswap_elements(a, lo, hi, ip);
	if (a[mid] > a[hi])
		fswap_elements(a, mid, hi, ip);

	return a[hi];
}

static inline int32_t imedian3(int32_t *restrict a, size_t lo, size_t hi, size_t *restrict ip)
{
	size_t mid = mid_index(lo, hi);

	if (a[lo] > a[mid])
		iswap_elements(a, lo, mid, ip);
	if (a[lo] > a[hi])
		iswap_elements(a, lo, hi, ip);
	if (a[mid] > a[hi])
		iswap_elements(a, mid, hi, ip);

	return a[hi];
}

static inline struct partition fpartition(float *restrict a, size_t lo, size_t hi, size_t *restrict ip)
{
	float pivot = fmedian3(a, lo, hi, ip);
	size_t i = lo - 1;
	size_t j = hi;

	for (;;) {
		while (a[++i] < pivot)
			continue;
		while (a[--j] > pivot)
			continue;
		if (i >= j)
			break;
		fswap_elements(a, i, j, ip);
	}
	fswap_elements(a, i, hi, ip);

	return (struct partition){j, i + 1};
}

static inline struct partition ipartition(int32_t *restrict a, size_t lo, size_t hi, size_t *restrict ip)
{
	int32_t pivot = imedian3(a, lo, hi, ip);
	size_t i = lo - 1;
	size_t j = hi;

	for (;;) {
		while (a[++i] < pivot)
			continue;
		while (a[--j] > pivot)
			continue;
		if (i >= j)
			break;
		iswap_elements(a, i, j, ip);
	}
	iswap_elements(a, i, hi, ip);

	return (struct partition){j, i + 1};
}

static inline void fquicksort(float *restrict a, size_t lo, size_t hi, size_t *restrict ip)
{
	if (lo < hi) {
		struct partition p = fpartition(a, lo, hi, ip);
		fquicksort(a, lo, p.left, ip);
		fquicksort(a, p.right, hi, ip);
	}
}

static inline void iquicksort(int32_t *restrict a, size_t lo, size_t hi, size_t *restrict ip)
{
	if (lo < hi) {
		struct partition p = ipartition(a, lo, hi, ip);
		iquicksort(a, lo, p.left, ip);
		iquicksort(a, p.right, hi, ip);
	}
}

static inline void init_ip(size_t *restrict ip, size_t n)
{
	for (size_t i = 0; i < n; ++i)
		ip[i] = i;
}

void fsort(float *restrict a, size_t n, size_t *restrict ip)
{
	if (ip)
		init_ip(ip, n);
	fquicksort(a, 0, n - 1, ip);
}

void isort(int32_t *restrict a, size_t n, size_t *restrict ip)
{
	if (ip)
		init_ip(ip, n);
	iquicksort(a, 0, n - 1, ip);
}
