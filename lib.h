#include<omp.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<float.h>
#include<math.h>
#include<stdio.h>

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

    int int_a = *(const int *)a;
    int int_b = *(const int *)b;

    return (int_a > int_b) - (int_a < int_b);
}

int compare_arrays(int *a, int *b, int size){

    for(int i = 0; i < size; i++){
        // int x = a[i], y = b[i];
        // if(x > y)
        //     x++;

        if(a[i] != b[i])
            return 0;
    }
        
    
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
        return -1;
    }

    fprintf(fp, "Algorithm          | Average (s) | Std Dev   | Min (s)   | Max (s)\n");
    fprintf(fp, "------------------------------------------------------------------\n");

    const char *algorithm_names[] = {
        "QBubbleSort",
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
    return 0;
}
