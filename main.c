#include<omp.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include"algorithms/bubble_sort.h"
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

int compare_arrays(int *a, int *b, int size){

    for(int i = 0; i < size; i++)
        if(a[i] != b[i])
            return 0;
    
    return 1;

}

double sort(int *data, int size, int *ref, void (*f)(int *, int)){

    double t = omp_get_wtime();
    (*f)(data, size);
    t = omp_get_wtime() - t;
    
    if(compare_arrays(data, ref, size)){
        return t;
    }

    return 0;
}

int main(int argc, char** argv){

    if(argc < 2)
        return -1;

    srand(time(NULL));

    int **data = (int**)malloc(sizeof(int*)*10);
    if(data == NULL)
        return -2;

    int **ref = (int**)malloc(sizeof(int*)*10);
    if(ref == NULL)
        return -3;

    for(int n = 1; n < argc; n++){

        int ammount = atoi(argv[n]);

        double *results = (double*)malloc(sizeof(double)*1000);
        if(results == NULL)
            return -4;

        for(int i = 0; i < 10; i++){
            data[i] = gen_data(ammount);
            if(data[i] == NULL)
                return -5;
        }

        for(int i = 0; i < 10; i++){

            ref[i] = (int*)malloc(sizeof(int)*ammount);
            if(ref[i] == NULL)
                return -6;
    
            memcpy(ref[i], data[i], sizeof(int)*ammount);
    
            qsort(ref[i], ammount, sizeof(int), compare);
    
        }
    
        #pragma omp parallel for
        for(int i = 0; i < 1000; i++){

            int *x = (int*)malloc(sizeof(int) * ammount);
            if(x == NULL)
                return -7;
            
            memcpy(x, data[i%10], sizeof(int)*ammount);

            double w = sort(x,ammount, ref[i%10], BubbleSort);

            free(x);
            x = NULL;

            results[i] = w;

        }

        for(int i = 0; i < 10; i++){
            free(data[i]);
            data[i] = NULL;

            free(ref[i]);
            ref[i] = NULL;
        }

        free(results);
        results = NULL;
            
    }

    free(data);
    free(ref);
    
    return 0;

}
