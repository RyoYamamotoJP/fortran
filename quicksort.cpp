#include <utility>
using namespace std;

template<typename T>
static inline void swap_elements(T* a, size_t i, size_t j, size_t* ip)
{
    swap(a[i], a[j]);
    if (ip)
        swap(ip[i], ip[j]);
}

static inline size_t middle_index(size_t lo, size_t hi)
{
    return lo + ((hi - lo) >> 1);
}

template<typename T>
static inline T median3(T* a, size_t lo, size_t hi, size_t* ip)
{
    size_t mid = middle_index(lo, hi);

    if (a[lo] > a[mid])
        swap_elements(a, lo, mid, ip);
    if (a[lo] > a[hi])
        swap_elements(a, lo, hi, ip);
    if (a[mid] > a[hi])
        swap_elements(a, mid, hi, ip);

    return a[hi];
}

template<typename T>
static inline pair<size_t, size_t> partition(T* a, size_t lo, size_t hi, size_t* ip)
{
    T pivot = median3(a, lo, hi, ip);
    size_t i = lo;
    size_t j = hi;

    for (;;) {
        while (a[++i] < pivot)
            continue;
        while (a[--j] > pivot)
            continue;
        if (i >= j)
            break;
        swap_elements(a, i, j, ip);
    }
    swap_elements(a, i, hi, ip);

    return {j, i + 1};
}

template<typename T>
static inline void quicksort(T* a, size_t lo, size_t hi, size_t* ip)
{
    if (lo < hi) {
        auto [left, right] = partition(a, lo, hi, ip);
        quicksort(a, lo, left, ip);
        quicksort(a, right, hi, ip);
    }
}

static inline void init_ip(size_t* ip, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        ip[i] = i;
}

template<typename T>
void sort(T* a, size_t n, size_t* ip)
{
    if (ip)
        init_ip(ip, n);
    quicksort(a, 0, n - 1, ip);
}

extern "C" {
    #include "quicksort.h"

    void fsort(float* a, size_t n, size_t* ip)
    {
        sort(a, n, ip);
    }

    void isort(int32_t* a, size_t n, size_t* ip)
    {
        sort(a, n, ip);
    }
}
