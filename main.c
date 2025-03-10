#include"lib.h"
#include"algorithms/bubble_sort.h"
#include"algorithms/heap_sort.h"
#include"algorithms/insert_sort.h"
#include"algorithms/merge_sort.h"
#include"algorithms/quick_sort.h"
#include"algorithms/select_sort.h"

int main(int argc, char** argv){

    if(argc < 2)
        return 1;

    srand(time(NULL));                              //preparation for generating random data set

    int **data = (int**)malloc(sizeof(int*)*10);    //alocating memory for data sets
    if(data == NULL)
        return 2;

    int **ref = (int**)malloc(sizeof(int*)*10);     //sorted arrays for reference to check if sorting was succesful
    if(ref == NULL)
        return 3;

    double **results = (double**)malloc(sizeof(double*)*1000);      //array that holds all results for later procesing
    if(results == NULL)
        return 4;

    double **result = NULL;

    for(int n = 1; n < argc; n++){                  //main loop

        int ammount = atoi(argv[n]);

        for(int i = 0; i < 10; i++){

            data[i] = gen_data(ammount);
            if(data[i] == NULL)
                return 5;

            ref[i] = (int*)malloc(sizeof(int)*ammount);
            if(ref[i] == NULL)
                return 6;

            memcpy(ref[i], data[i], sizeof(int)*ammount);

            qsort(ref[i], ammount, sizeof(int), compare);

        }

        int error = 0;
    
        #pragma omp parallel for
        for(int i = 0; i < 1000; i++){

            int *x = (int*)malloc(sizeof(int) * ammount);
            if(x == NULL){
                #pragma omp atomic write
                error = 7;
                continue;
            }
            
            memcpy(x, data[i%10], sizeof(int)*ammount);

            results[i] = (double*)malloc(sizeof(double) * 7);
            if(results[i] == NULL){
                #pragma omp atomic write
                error = 8;
                continue;
            }

            results[i][0] = sort(x, ammount, ref[i%10], BubbleSort);

            memcpy(x, data[i%10], sizeof(int)*ammount);

            results[i][1] = sort(x, ammount, ref[i%10], QBubbleSort);

            // memcpy(x, data[i%10], sizeof(int)*ammount);

            // results[i][2] = sort(x, ammount, ref[i%10], HeapSort);

            // memcpy(x, data[i%10], sizeof(int)*ammount);

            // results[i][3] = sort(x, ammount, ref[i%10], InsertSort);

            // memcpy(x, data[i%10], sizeof(int)*ammount);

            // results[i][4] = sort(x, ammount, ref[i%10], MergeSort);

            // memcpy(x, data[i%10], sizeof(int)*ammount);

            // results[i][5] = sort(x, ammount, ref[i%10], QuickSort);

            // memcpy(x, data[i%10], sizeof(int)*ammount);

            // results[i][6] = sort(x, ammount, ref[i%10], SelectSort);

            free(x);
            x = NULL;

        }

        if(error)
            return error;

        result = final_result(results, 1000, 7);
        if(result == NULL)
            return 9;

        if(!print_results_to_file(result, 7, "Results", n))
            return 10;

        for(int i = 0; i < 10; i++){
            free(data[i]);
            data[i] = NULL;

            free(ref[i]);
            ref[i] = NULL;
        }

        for(int i = 0; i < 1000; i++){
            free(results[i]);
            results[i] = NULL;
        }
            
        for(int i = 0; i < 7; i++){
            free(result[i]);
            result[i] = NULL;
        }

        free(result);
        result = NULL;
            
    }

    free(results);
    free(data);
    free(ref);
    
    return 0;

}
