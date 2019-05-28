#include "quicksort.h"

struct partition {
	size_t left;
	size_t right;
};

static inline void fswap(float *a, float *b)
{
	float temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static inline void iswap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static inline void size_tswap(size_t *a, size_t *b)
{
	size_t temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static inline void fswap_elements(float a[], size_t i, size_t j, size_t ip[])
{
	fswap(&a[i], &a[j]);
	if (ip)
		size_tswap(&ip[i], &ip[j]);
}

static inline void iswap_elements(int a[], size_t i, size_t j, size_t ip[])
{
	iswap(&a[i], &a[j]);
	if (ip)
		size_tswap(&ip[i], &ip[j]);
}

static inline float fmedian3(float a[], size_t lo, size_t hi, size_t ip[])
{
	size_t mid = lo + (hi - lo) / 2;

	if (a[lo] > a[mid])
		fswap_elements(a, lo, mid, ip);
	if (a[lo] > a[hi])
		fswap_elements(a, lo, hi, ip);
	if (a[mid] > a[hi])
		fswap_elements(a, mid, hi, ip);

	return a[hi];
}

static inline int imedian3(int a[], size_t lo, size_t hi, size_t ip[])
{
	size_t mid = lo + (hi - lo) / 2;

	if (a[lo] > a[mid])
		iswap_elements(a, lo, mid, ip);
	if (a[lo] > a[hi])
		iswap_elements(a, lo, hi, ip);
	if (a[mid] > a[hi])
		iswap_elements(a, mid, hi, ip);

	return a[hi];
}

static inline struct partition fpartition(float a[], size_t lo, size_t hi, size_t ip[])
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

static inline struct partition ipartition(int a[], size_t lo, size_t hi, size_t ip[])
{
	int pivot = imedian3(a, lo, hi, ip);
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

void fquicksort(float a[], size_t lo, size_t hi, size_t ip[])
{
	if (lo < hi) {
		struct partition p = fpartition(a, lo, hi, ip);
		fquicksort(a, lo, p.left, ip);
		fquicksort(a, p.right, hi, ip);
	}
}

void iquicksort(int a[], size_t lo, size_t hi, size_t ip[])
{
	if (lo < hi) {
		struct partition p = ipartition(a, lo, hi, ip);
		iquicksort(a, lo, p.left, ip);
		iquicksort(a, p.right, hi, ip);
	}
}
