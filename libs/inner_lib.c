#include<omp.h>
#include<stdlib.h>
#include<float.h>
#include<math.h>
#include<limits.h>

void* gen_data(int size, size_t type_size){
                                                    // Funkcja generująca losową tablicę o podanym rozmiarze i rozmiarze zmiennych

    void *res = malloc(type_size * size);

    if(res == NULL)
        return NULL;

                                                    // Wypełnianie tablicy losowymi bajtami (0-255)
    for(int i = 0; i < size; i++){
        unsigned char *byte_ptr = (unsigned char *)res + (i * type_size);

        for(int k = 0; k < type_size; k++) 
            byte_ptr[k] = rand() % 256;

    }

    return res;
}

int compareINT(const void* a, const void* b){
                                                    // Funkcja porównująca dla qsort (rosnąco) - typ int

    int int_a = *(const int *)a;
    int int_b = *(const int *)b;

    return (int_a > int_b) - (int_a < int_b);
}

int rev_compareINT(const void* a, const void* b){

                                                    // Funkcja porównująca dla qsort (malejąco) - typ int
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;

    return (int_a < int_b) - (int_a > int_b);
}

int compare_arraysINT(int *a, int *b, int size){
                                                    // Porównywanie dwóch tablic intów (identyczność)

    for(int i = 0; i < size; i++)
        if(a[i] != b[i])
            return 0;
        
    return 1;
}

int compareDOUBLE(const void* a, const void* b){
                                                    // Funkcja porównująca dla qsort (rosnąco) - typ double

    double double_a = *(const double *)a;
    double double_b = *(const double *)b;

    return (double_a > double_b) - (double_a < double_b);
}

int rev_compareDOUBLE(const void* a, const void* b){
                                                    // Funkcja porównująca dla qsort (malejąco) - typ double

    double double_a = *(const double *)a;
    double double_b = *(const double *)b;

    return (double_a < double_b) - (double_a > double_b);
}

int compare_arraysDOUBLE(double *a, double *b, int size){
                                                    // Porównywanie dwóch tablic double'ów (identyczność)

    for(int i = 0; i < size; i++)
        if(a[i] != b[i])
            return 0;
        
    return 1;
}

double sort(void *data, int size, int config, void *ref, void (*f)(void *, int, int)){
                                                    // Pomiar czasu sortowania i weryfikacja poprawności wyniku
                                                    // Zwraca czas w sekundach lub -1 przy błędnym sortowaniu

    double t = omp_get_wtime();                     // Rozpoczęcie pomiaru czasu
    (*f)(data, size, config);                       // Wywołanie funkcji sortującej
    t = omp_get_wtime() - t;                        // Zakończenie pomiaru

                                                    // Weryfikacja zgodności z tablicą referencyjną
    if(config != 4){
        if(!compare_arraysINT(data, ref, size))    
            return -1.0;
    } else if(!compare_arraysDOUBLE(data, ref, size))
            return -1.0;

    return t;                                       // Zwrócenie zmierzonego czasu
}
