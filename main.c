#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#include"libs/lib.h"
// #include"algorithms/bubble_sort.h"   ->  niewykorzystywane
#include"algorithms/heap_sort.h"
#include"algorithms/insert_sort.h"
#include"algorithms/quick_sort.h"
#include"algorithms/shell_sort.h"


int main(int argc, char** argv){                    // W argumentach startowych użytkownik podaje rozmiar tablic do sortowania

    if(argc < 2)
        return 1;

    double **results = (double**)malloc(sizeof(double*)*100);      // Tablica przechowująca czasy sortowań do późniejszej obróbki
    if(results == NULL)
        return 2;

    double **result_final = NULL;                   // Tablica z końcowymi wynikami, zostaje zapisana jako plik .csv

    for(int n = 1; n < argc; n++){                  // Główna pętla, wykonuje się tyle razy, ile arumentów zostało podane do pragramu jako rozmiary tablic

        int ammount = atoi(argv[n]);

        int error = 0, progres = 0;
    
        #pragma omp parallel for                    // Wielo-wątkowa część programu, każda iteracja poniższej pętli for wykonywana jest przez osobny wątek
        for(int i = 0; i < 100; i++){

                                                    // Tworzenie tablic z zmiennymi int to późniejszego sortowania
            int **data_int = creat_dataINT(ammount);
            if(data_int == NULL){
                #pragma omp atomic write
                error = 3;
                continue;
            }
                                                    // Tworzenie tablic z zmiennymi double to późniejszego sortowania
            double **data_double = creat_dataDOUBLE(ammount);
            if(data_double == NULL){
                #pragma omp atomic write
                error = 4;
                continue;
            }

                                                    // Tablica na lokale wyniki sortowań
            results[i] = (double*)malloc(sizeof(double) * 45);
            if(results[i] == NULL){
                #pragma omp atomic write
                error = 5;
                continue;
            }

                                                    // Wywołania algorytmów sortowania, zwrócenie innego kodu jak 0 ozancza wykrycie błędu
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

            for(int i = 0; i < 7; i++){                // Zwalnianie lokalnej pamięci
                free(data_int[i]);
                data_int[i] = NULL;

                free(data_double[i]);
                data_double[i] = NULL;
            }

            free(data_int);
            data_int = NULL;

            free(data_double);
            data_double = NULL;

            #pragma omp atomic                          // Licznik postępu
            progres++;

            if(omp_get_thread_num() == 0){              // Wątek 0 wypisuje postęp do konsoli
                #pragma omp critical
                printf("\rProgress: %i%%", progres);
                fflush(stdout);
            }

        }

        printf("\rProgress: 100%%\n");
        fflush(stdout);

        if(error)
            return error;

                                                        // Wyznaczenie średniej, min, max oraz odchylenia standardowego wyników
        result_final = final_result(results, 100, 9);
        if(result_final == NULL)
            return 9;

                                                        // Zapisanie otrzymanych wyników do pliku "Results_x.csv", x to iteracja głownej pętli
        if(print_results_to_file(result_final, 9, "Results", n, ammount) != 1)
            return 10;

                                                        // Zwalnienie niewykorzystywanej już pamięci
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
