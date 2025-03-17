#include<omp.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<float.h>
#include<math.h>
#include<stdio.h>

void* gen_data(int size, size_t type_size){

    void *res = malloc(type_size * size);

    if(res == NULL)
        return NULL;

    for(int i = 0; i < size; i++){
        unsigned char *byte_ptr = (unsigned char *)res + (i * type_size);

        for(int k = 0; k < type_size; k++) 
            byte_ptr[k] = rand() % 256;

    }

    return res;
}

int compare(const void* a, const void* b){

    int int_a = *(const int *)a;
    int int_b = *(const int *)b;

    return (int_a > int_b) - (int_a < int_b);
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
    
    if(!compare_arrays(data, ref, size))
        return -1.0;

    return t;
}

double** final_result(double **results, int size, int num_of_sets){

    double **final = (double**)malloc(sizeof(double*) * num_of_sets);
    if(final == NULL)
        return NULL;

    for(int j = 0; j < num_of_sets; j++){

        final[j] = (double*)malloc(sizeof(double) * 4);
        if(final[j] == NULL)
            return NULL;

        final[j][0] = 0.0;
        final[j][1] = 0.0;
        final[j][2] = DBL_MAX;
        final[j][3] = 0.0;

        for(int i = 0; i < size; i++){

            if(results[i][j] < 0)
                return NULL;

            if(results[i][j] > final[j][3])
                final[j][3] = results[i][j];

            if(results[i][j] < final[j][2])
                final[j][2] = results[i][j];

            final[j][0] += results[i][j]/(double)size;

        }

        for(int i = 0; i < size; i++)
            final[j][1] += (results[i][j] - final[j][0]) * (results[i][j] - final[j][0]);

        final[j][1] = sqrt(final[j][1] / (double)size);
    }
    
    return final;
}

int print_results_to_file(double **result, int num_algorithms, const char *filename_pref, int n){

    char filename[256];
    snprintf(filename, sizeof(filename), "%s_%d.txt", filename_pref, n);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 0;
    }

    fprintf(fp, "Algorithm          | Average (s) | Std Dev   | Min (s)   | Max (s)\n");
    fprintf(fp, "------------------------------------------------------------------\n");

    const char *algorithm_names[] = {
        "BubbleSort",
        "BubbleSortASM",
        "HeapSort",
        "InsertSort",
        "MergeSort",
        "QuickSort",
        "SelectSort"
    };

    for (int i = 0; i < num_algorithms; i++){
        if (result[i] == NULL){
            fprintf(stderr, "Skipping invalid algorithm entry %d\n", i);
            continue;
        }

        fprintf(fp, "%-18s %-11.6f %-10.6f %-10.6f %-10.6f\n",
                algorithm_names[i],
                result[i][0],  // Average
                result[i][1],  // Standard Deviation
                result[i][2],  // Minimum
                result[i][3]); // Maximum
    }

    fclose(fp);
    return 1;
    
}
