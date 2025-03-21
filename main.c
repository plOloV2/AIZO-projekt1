#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#include"libs/lib.h"
// #include"algorithms/bubble_sort.h" -> unused
#include"algorithms/heap_sort.h"
#include"algorithms/insert_sort.h"
#include"algorithms/quick_sort.h"
#include"algorithms/shell_sort.h"

/*
    TO DO:
    -shell dwa ciągi kroków
    -opisać kod
*/

int main(int argc, char** argv){                    //in arguments user secifies sizes of data sets to sort

    if(argc < 2)
        return 1;

    srand(time(NULL));

    double **results = (double**)malloc(sizeof(double*)*100);      //array that holds all results for later procesing
    if(results == NULL)
        return 2;

    double **result_final = NULL;                   //array with final results that will be saved to file

    for(int n = 1; n < argc; n++){                  //main loop, executes as many times as specified in argv

        int ammount = atoi(argv[n]);

        int error = 0, progres = 0;
    
        #pragma omp parallel for                    //multi-thread part of program, every iteration of this for is executed on separate thread
        for(int i = 0; i < 100; i++){

            int **data_int = creat_dataINT(ammount);
            if(data_int == NULL){
                #pragma omp atomic write
                error = 3;
                continue;
            }

            double **data_double = creat_dataDOUBLE(ammount);
            if(data_double == NULL){
                #pragma omp atomic write
                error = 4;
                continue;
            }


            results[i] = (double*)malloc(sizeof(double) * 45);
            if(results[i] == NULL){
                #pragma omp atomic write
                error = 5;
                continue;
            }
            
            if(sort_results((void**)data_int, ammount, 0, HeapSort, results[i], 0) != 0){
                #pragma omp atomic write
                error = 6;
                continue;
            }
            
            if(sort_results((void**)data_int, ammount, 0, InsertSort, results[i], 5) != 0){
                #pragma omp atomic write
                error = 6;
                continue;
            }
            
            if(sort_results((void**)data_int, ammount, 0, QuickSort, results[i], 10) != 0){
                #pragma omp atomic write
                error = 6;
                continue;
            }
            
            if(sort_results((void**)data_int, ammount, 1, QuickSort, results[i], 15) != 0){
                #pragma omp atomic write
                error = 6;
                continue;
            }
            
            if(sort_results((void**)data_int, ammount, 2, QuickSort, results[i], 20) != 0){
                #pragma omp atomic write
                error = 6;
                continue;
            }
            
            if(sort_results((void**)data_int, ammount, 3, QuickSort, results[i], 25) != 0){
                #pragma omp atomic write
                error = 6;
                continue;
            }
            
            if(sort_results((void**)data_double, ammount, 4, QuickSort, results[i], 30) != 0){
                #pragma omp atomic write
                error = 6;
                continue;
            }
            
            if(sort_results((void**)data_int, ammount, 0, Shellsort, results[i], 35) != 0){
                #pragma omp atomic write
                error = 6;
                continue;
            }
            
            if(sort_results((void**)data_int, ammount, 1, Shellsort, results[i], 40) != 0){
                #pragma omp atomic write
                error = 6;
                continue;
            }

            for(int i = 0; i < 5; i++){                //frees local data
                free(data_int[i]);
                data_int[i] = NULL;

                free(data_double[i]);
                data_double[i] = NULL;
            }

            free(data_int);
            data_int = NULL;

            free(data_double);
            data_double = NULL;

            #pragma omp atomic                                              //used to display progres of stage
            progres++;

            if(omp_get_thread_num() == 0){
                #pragma omp critical
                printf("\rProgress: %i%%", progres);
                fflush(stdout);
            }

        }

        printf("\rProgress: 100%%\n");
        fflush(stdout);

        if(error)
            return error;

        result_final = final_result(results, 100, 9);                  //calculates avg, min, max and standard diviation
        if(result_final == NULL)
            return 9;

        if(print_results_to_file(result_final, 9, "Results", n, ammount) != 1)   //save calculated results to file "Results_x.txt" where x is iteration of main loop
            return 10;

        for(int i = 0; i < 100; i++){
            free(results[i]);
            results[i] = NULL;
        }
            
        for(int i = 0; i < 9; i++){
            free(result_final[i]);
            result_final[i] = NULL;
        }

        free(result_final);
        result_final = NULL;
            
    }

    free(results);
    
    return 0;

}
