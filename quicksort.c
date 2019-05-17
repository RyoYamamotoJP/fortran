void fquicksort(float a[], int lo, int hi, int ip[]);
void iquicksort(int a[], int lo, int hi, int ip[]);

struct partition fpartition(float a[], int lo, int hi, int ip[]);
struct partition ipartition(int a[], int lo, int hi, int ip[]);

float fmedian3(float a[], int lo, int hi, int ip[]);
int imedian3(int a[], int lo, int hi, int ip[]);

void fswap_elements(float a[], int i, int j, int ip[]);
void iswap_elements(int a[], int i, int j, int ip[]);

void fswap(float *a, float *b);
void iswap(int *a, int *b);

struct partition {
	int left;
	int right;
};

void fquicksort(float a[], int lo, int hi, int ip[])
{
	struct partition p;

	if (lo < hi) {
		p = fpartition(a, lo, hi, ip);
		fquicksort(a, lo, p.left, ip);
		fquicksort(a, p.right, hi, ip);
	}
}

void iquicksort(int a[], int lo, int hi, int ip[])
{
	struct partition p;

	if (lo < hi) {
		p = ipartition(a, lo, hi, ip);
		iquicksort(a, lo, p.left, ip);
		iquicksort(a, p.right, hi, ip);
	}
}

struct partition fpartition(float a[], int lo, int hi, int ip[])
{
	float pivot = fmedian3(a, lo, hi, ip);
	int i = lo - 1;
	int j = hi;

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

struct partition ipartition(int a[], int lo, int hi, int ip[])
{
	int pivot = imedian3(a, lo, hi, ip);
	int i = lo - 1;
	int j = hi;

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

float fmedian3(float a[], int lo, int hi, int ip[])
{
	int mid = lo + (hi - lo) / 2;

	if (a[lo] > a[mid])
		fswap_elements(a, lo, mid, ip);
	if (a[lo] > a[hi])
		fswap_elements(a, lo, hi, ip);
	if (a[mid] > a[hi])
		fswap_elements(a, mid, hi, ip);

	return a[hi];
}

int imedian3(int a[], int lo, int hi, int ip[])
{
	int mid = lo + (hi - lo) / 2;

	if (a[lo] > a[mid])
		iswap_elements(a, lo, mid, ip);
	if (a[lo] > a[hi])
		iswap_elements(a, lo, hi, ip);
	if (a[mid] > a[hi])
		iswap_elements(a, mid, hi, ip);

	return a[hi];
}

void fswap_elements(float a[], int i, int j, int ip[])
{
	fswap(&a[i], &a[j]);
	if (ip)
		iswap(&ip[i], &ip[j]);
}

void iswap_elements(int a[], int i, int j, int ip[])
{
	iswap(&a[i], &a[j]);
	if (ip)
		iswap(&ip[i], &ip[j]);
}

void fswap(float *a, float *b)
{
	float temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void iswap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
