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

int compare(const void* a, const void* b){
    return (*(int *)a - *(int *)b);
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

    int **ref = (int**)malloc(sizeof(int*)*10);
    if(ref == NULL)
        return -3;
    
    for(int i = 0; i < 10; i++){

        ref[i] = (int*)malloc(sizeof(int)*1000);
        if(ref[i] == NULL)
            return -4;

        memcpy(ref[i], data[i], sizeof(int)*1000);

        qsort(ref[i], 1000, sizeof(int), compare);

    }

    for(int i = 0; i < 1000; i++){
        
    }

    return 0;

}
