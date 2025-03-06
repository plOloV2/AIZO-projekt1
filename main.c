#include"lib.h"
#include"algorithms/bubble_sort.h"
#include"algorithms/heap_sort.h"
#include"algorithms/insert_sort.h"
#include"algorithms/merge_sort.h"
#include"algorithms/quick_sort.h"
#include"algorithms/select_sort.h"

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

        int error = 0;
    
        #pragma omp parallel for
        for(int i = 0; i < 1000; i++){

            int *x = (int*)malloc(sizeof(int) * ammount);
            if(x == NULL){
                error = -7;
                continue;;
            }
            
            memcpy(x, data[i%10], sizeof(int)*ammount);

            double w = sort(x,ammount, ref[i%10], BubbleSort);

            free(x);
            x = NULL;

            results[i] = w;

        }

        if(error)
            return error;

        double *result = final_result(results, 1000);
        if(result = NULL)
            return -8;

        for(int i = 0; i < 10; i++){
            free(data[i]);
            data[i] = NULL;

            free(ref[i]);
            ref[i] = NULL;
        }

        free(results);
        results = NULL;

        free(result);
        result = NULL;
            
    }

    free(data);
    free(ref);
    
    return 0;

}
