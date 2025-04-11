#include<omp.h>
#include<string.h>
#include<float.h>
#include<math.h>
#include<stdio.h>
#include<limits.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include"inner_lib.h"


int** creat_dataINT(int ammount){
                                                    // Funkcja tworzące zestaw danych int o rozmiaże ammount

    int **data = (int**)malloc(sizeof(int*) * 7);
    if(data == NULL)
        return NULL;

    for(int i = 1; i < 7; i++){
        data[i] = (int*)malloc(sizeof(int) * ammount);
        if(data[i] == NULL)
            return NULL;
    }

    unsigned int seed;
    FILE *f = fopen("/dev/urandom", "rb");
    fread(&seed, sizeof(seed), 1, f);
    fclose(f);
    seed += omp_get_thread_num();
                                                    // Pierwsza tablica -> losowe zmienne
    data[0] = gen_data(ammount, sizeof(int), &seed);

                                                    // Druga -> posortowane rosnąco
    memcpy(data[1], data[0], sizeof(int)*ammount);
    qsort(data[1], ammount, sizeof(int), compareINT);

                                                    // Trzecia -> posortowane malejąco
    memcpy(data[2], data[0], sizeof(int)*ammount);
    qsort(data[2], ammount, sizeof(int), rev_compareINT);

                                                    // Czwarta -> pierwsze 33% posortowane
    memcpy(data[3], data[0], sizeof(int)*ammount);
    int count33 = (ammount * 33) / 100;
    for(int i = 0; i < count33; i++){
        data[3][i] = INT_MIN;
    }

                                                    // Piąta -> tablica kontrolna do sprawdzenia poprawności sortowania dla 33%
    memcpy(data[4], data[3], sizeof(int)*ammount);
    qsort(data[4], ammount, sizeof(int), compareINT);

                                                    // Szósta -> pierwsze 67% posortowane
    memcpy(data[5], data[0], sizeof(int)*ammount);
    int count67 = (ammount * 67) / 100;
    for(int i = 0; i < count67; i++){
        data[5][i] = INT_MIN;
    }

                                                    // Siudma -> tablica kontrolna do sprawdzenia poprawności sortowania dla 67%
    memcpy(data[6], data[5], sizeof(int)*ammount);
    qsort(data[6], ammount, sizeof(int), compareINT);

    return data;
}

double** creat_dataDOUBLE(int ammount){
                                                    // Funkcja tworzące zestaw danych double o rozmiaże ammount

    double **data = (double**)malloc(sizeof(double*) * 7);
    if(data == NULL)
        return NULL;

    for(int i = 1; i < 7; i++){
        data[i] = (double*)malloc(sizeof(double) * ammount);
        if(data[i] == NULL)
            return NULL;
    }

    unsigned int seed;
    FILE *f = fopen("/dev/urandom", "rb");
    fread(&seed, sizeof(seed), 1, f);
    fclose(f);
    seed += omp_get_thread_num();

                                                    // Pierwsza tablica -> losowe zmienne
    data[0] = gen_data(ammount, sizeof(double), &seed);

    for(int i = 0; i < ammount; i++)
        if(isnan(data[0][i]))
            data[0][i] = ((double)rand_r(&seed) / RAND_MAX) * 2e100 - 1e100;
        
    
                                                    // Druga -> posortowane rosnąco
    memcpy(data[1], data[0], sizeof(double)*ammount);
    qsort(data[1], ammount, sizeof(double), compareDOUBLE);

                                                    // Trzecia -> posortowane malejąco
    memcpy(data[2], data[0], sizeof(double)*ammount);
    qsort(data[2], ammount, sizeof(double), rev_compareDOUBLE);

                                                    // Czwarta -> pierwsze 33% posortowane
    memcpy(data[3], data[0], sizeof(double)*ammount);
    int count33 = (ammount * 33) / 100;
    for(int i = 0; i < count33; i++){
        data[3][i] = -DBL_MAX;
    }

                                                    // Piąta -> tablica kontrolna do sprawdzenia poprawności sortowania dla 33%
    memcpy(data[4], data[3], sizeof(double)*ammount);
    qsort(data[4], ammount, sizeof(double), compareDOUBLE);

                                                    // Szósta -> pierwsze 67% posortowane
    memcpy(data[5], data[0], sizeof(double)*ammount);
    int count67 = (ammount * 67) / 100;
    for(int i = 0; i < count67; i++){
        data[5][i] = -DBL_MAX;
    }

                                                    // Siudma -> tablica kontrolna do sprawdzenia poprawności sortowania dla 67%
    memcpy(data[6], data[5], sizeof(double)*ammount);
    qsort(data[6], ammount, sizeof(double), compareDOUBLE);

    return data;
}

int sort_results(void **data, int size, int config, void (*f)(void *, int, int), double *results_array, int start_pos){
                                                    // Funkcja miężąca czas sortowania dla algorytmu podanego w parametrze
                                                    // czasy sortowań zapisuje w tablicy results_array zaczynając od pozycji start_pos

    double *res = (double*)malloc(sizeof(double) * 5);
    if(res == NULL)
        return 1;

                                                    // Lokalna kopia tablic do posortowania
    void **local_data = malloc(sizeof(void*) * 7);
    if(local_data == NULL)
        return 1;

                                                    // Zależnie od konfiguracji zapęłnia je zmiennymi int lub double
    if(config != 4){

        for(int i = 0; i < 7; i++){
            local_data[i] = (int*)malloc(sizeof(int) * size);
            if(local_data[i] == NULL)
                return 2;

            memcpy(local_data[i], data[i], sizeof(int) * size);
        }

    } else{

        for(int i = 0; i < 7; i++){
            local_data[i] = (double*)malloc(sizeof(double) * size);
            if(local_data[i] == NULL)
                return 2;

            memcpy(local_data[i], data[i], sizeof(double) * size);
        }

    }

                                                    // Sortowanie tablic i zapisanie wyników do tablicy res
    for(int i = 0; i < 3; i++)
        res[i] = sort(local_data[i], size, config, data[1], (*f));
    
    res[3] = sort(local_data[3], size, config, data[4], (*f));
    res[4] = sort(local_data[5], size, config, data[6], (*f));

                                                    // Przekopiowanie wyników z tablicy res do results_array
    memcpy(&results_array[start_pos], res, sizeof(double) * 5);

                                                    //Czyszczenie pamięci
    for(int i = 0; i < 7; i++){
        free(local_data[i]);
        local_data[i] = NULL;
    }

    free(local_data);
    local_data = NULL;

    free(res);
    res = NULL;

    return 0;

}

double** final_result(double **results, int size, int num_of_sets){
                                                    // Funckja wyznaczająca średnią, min, max oraz odchylenie standardowe dla zebranych wyników

                                                    // Tablica z wynikami końcowymi o razmiarze num_of_sets * 20 
                                                    // (num_of_sets algorytmów, po 5 (liczba tablic) * 4 (liczba oblicznych danych) wyników)
    double **final = (double**)malloc(sizeof(double*) * num_of_sets);            
    if(final == NULL)
        return NULL;

    for(int j = 0; j < num_of_sets; j++){

        final[j] = (double*)malloc(sizeof(double) * 20);
        if(final[j] == NULL)
            return NULL;

        for(int k = 0; k < 20; k++){
                                                    // Przygotowanie pod poszukiwanie min i max
            if(k % 4 == 2)
                final[j][k] = DBL_MAX;
            else
                final[j][k] = 0.0;

        }

    }

    for(int j = 0; j < num_of_sets * 5; j++){

        for(int i = 0; i < size; i++){

                                                    // Jeżeli któryś z wyników jest mniejszy od 0 -> wystąpił błąd podczas sortowania
            if(results[i][j] < 0)
                return NULL;

                                                    // Magia na indeksach napisana zbyt dawno żeby ją teraz rozkodować
            if(results[i][j] > final[j/5][(j%5)*4+3])
                final[j/5][(j%5)*4+3] = results[i][j];

            if(results[i][j] < final[j/5][(j%5)*4+2])
                final[j/5][(j%5)*4+2] = results[i][j];

            final[j/5][(j%5)*4] += results[i][j]/(double)size;

        }

                                                    // Wyznaczenie odchylenia standardowego
        for(int i = 0; i < size; i++)
            final[j/5][(j%5)*4+1] += (results[i][j] - final[j/5][(j%5)*4]) * (results[i][j] - final[j/5][(j%5)*4]);

        final[j/5][(j%5)*4+1] = sqrt(final[j/5][(j%5)*4+1] / (double)size);
    }
    
    return final;
}

int print_results_to_file(double **result, int num_algorithms, const char *filename_pref, int n, int ammount){
                                                    // Ta funkcja zapisuje otrzymane w tablicy results wyniki do pliku .csv

    char filename[256];

    struct stat st = {0};
    if(stat("data", &st) == -1) 
        mkdir("data", 0700);


    snprintf(filename, sizeof(filename), "data/%s_%d.csv", filename_pref, n);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 0;
    }

    fprintf(fp, "name, data_size, N_avg, N_std_dev, N_min, N_max, G_avg, G_std_dev, G_min, G_max, D_avg, D_std_dev, D_min, D_max, 33_avg, 33_std_dev, 33_min, 33_max, 67_avg, 67_std_dev, 67_min, 67_max\n");

    const char *algorithm_names[] = {
        "HeapSort",
        "InsertSort",
        "QuickSortNormal",
        "QuickSortFirst",
        "QuickSortLast",
        "QuickSortRandom",
        "QuickSortDouble",
        "ShellSort1",
        "ShellSort2"
    };

    for (int i = 0; i < num_algorithms; i++){

        fprintf(fp, "%s, %i, %.9f, %.9f, %.9f, %.9f, %.9f, %.9f, %.9f, %.9f, %.9f, %.9f, %.9f, %.9f, %.9f, %.9f, %.9f, %.9f, %.9f, %.9f, %.9f, %.9f\n",
                algorithm_names[i],
                ammount,
                result[i][0],
                result[i][1],
                result[i][2],
                result[i][3],
                result[i][4],
                result[i][5],
                result[i][6],
                result[i][7],
                result[i][8],
                result[i][9],
                result[i][10],
                result[i][11],
                result[i][12],
                result[i][13],
                result[i][14],
                result[i][15],
                result[i][16],
                result[i][17],
                result[i][18],
                result[i][19]); 
        
    }

    fclose(fp);
    return 1;
    
}
