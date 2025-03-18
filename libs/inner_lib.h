#include<stdlib.h>

void* gen_data(int size, size_t type_size);

int compareINT(const void* a, const void* b);

int rev_compareINT(const void* a, const void* b);

int compare_arraysINT(int *a, int *b, int size);

int compareDOUBLE(const void* a, const void* b);

int rev_compareDOUBLE(const void* a, const void* b);

int compare_arraysDOUBLE(double *a, double *b, int size);

double sort(void *data, int size, int config, void *ref, void (*f)(void *, int, int));
