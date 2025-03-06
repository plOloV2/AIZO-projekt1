#include<omp.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<float.h>

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

double* final_result(double *results, int size){

    double *final = (double*)malloc(sizeof(double)*4);
    if(final == NULL)
        return NULL;

    final[2] = DBL_MAX;
    final[3] = 0;

    for(int i = 0; i < size; i++){

        if(results[i] > final[3])
            final[3] = results[i];

        if(results[i] < final[2])
            final[2] = results[i];

        final[0] = results[i]/(double)size;

    }

    for(int i = 0; i < size; i++){

        final[1] = (results[i] - final[0]) * (results[i] - final[0]);

    }

    final[1] /= (double)size;

    final[1] = sqrt(final[1]);

    return final;
}
