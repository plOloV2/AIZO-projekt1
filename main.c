#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<stdlib.h>
#include"algorithms/buble_sort.h"
#include"algorithms/heap_sort.h"
#include"algorithms/insert_sort.h"
#include"algorithms/merge_sort.h"
#include"algorithms/quick_sort.h"
#include"algorithms/select_sort.h"

int* gen_data(int size){

    int num, *res = NULL;

    res = (int*)malloc(sizeof(int)*size);

    if(res == NULL)
        return NULL;

    for(int i = 0; i < size; i++){
        unsigned char *byte_ptr = (unsigned char *)&num;

        for (size_t k = 0; k < sizeof(int); k++) 
            *byte_ptr++ = rand() % 256;

        res[i] = num;
    }

    return res;
}

int main(){

    srand(time(NULL));

    int **data = (int**)malloc(sizeof(int*)*10);
    if(data == NULL)
        return -1;
    
    for(int i = 0; i < 10; i++){
        data[i] = gen_data(1000);
        if(data[i] == NULL)
            return -2;
    }

    
}
