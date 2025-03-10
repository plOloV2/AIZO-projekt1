#include"algorithms/bubble_sort.h"
#include<omp.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<float.h>
#include<math.h>
#include<stdio.h>

int compare(const void* a, const void* b){
    return (*(int *)a - *(int *)b);
}

int main(){
    int x[] = {12, 3, 29, 91, -1, 5, -32, 21, 10, 4};
    qsort(x, 10, sizeof(int), compare);
    // BubbleSort(x, 10);
    for(int i = 0; i < 10; i++)
        printf("%d\n", x[i]);

    return 0;
}
