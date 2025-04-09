#include<stdlib.h>

void swapI(int *a, int *b){

    int temp = *a;
    *a = *b;
    *b = temp;
    return;

}


void swapD(double *a, double *b){

    double temp = *a;
    *a = *b;
    *b = temp;
    return;

}


int pivotI(int *arr, int srt, int end, int pivot_pos){
                                        // srt -> indeks tablicy od którego należy zacząć sortowanie
                                        // end -> indeks tablicy na którym należy zakończyć sortowanie

    switch (pivot_pos){
        case 0:                         // 0 -> pivot środkowy element tablicy
            swapI(&arr[(srt+end)/2], &arr[end]);
            break;

        case 1:                         // 1 -> pivot to pierwszy element tablicy
            swapI(&arr[srt], &arr[end]);
            break;
            
        case 3:                         // 3 -> pivot to losowy element tablicy
            swapI(&arr[(rand() % (end - srt)) + srt], &arr[end]);
            break;

        default:                        // -> pivot to ostatni element tablicy
            break;
    }
    
    int i = srt - 1;

    for(int j = srt; j < end; j++){
                                        // ustawienie elementów względem pivota
        if(arr[j] < arr[end])
            swapI(&arr[j], &arr[++i]);
        
    }

    swapI(&arr[++i], &arr[end]);        // powrót pivota na prwidłowe miejsce

    return i;                           // zwraca pozycje pivota

}


int pivotD(double *arr, int srt, int end){
                                        // pivot to środkowy element
    swapD(&arr[(srt+end)/2], &arr[end]);

    int i = srt - 1;

    for(int j = srt; j < end; j++){
                                        // ustawienie elementów względem pivota
        if(arr[j] < arr[end])
            swapD(&arr[j], &arr[++i]);
        
    }

    swapD(&arr[++i], &arr[end]);        // powrót pivota na prwidłowe miejsce

    return i;                           // zwraca pozycje pivota

}


void Isort(int *arr, int start, int end, int pivot_pos){
    
    if(end <= start)                    // warunek zakończenia rekurencji
        return;

    int pivot = pivotI(arr, start, end, pivot_pos);

    Isort(arr, start, pivot - 1, pivot_pos);    // rekurencyjne wywołania 
    Isort(arr, pivot + 1, end, pivot_pos);

}


void Dsort(double *arr, int start, int end){

    if(end <= start)                    // warunek zakończenia rekurencji
        return;

    int pivot = pivotD(arr, start, end);

    Dsort(arr, start, pivot - 1);       // rekurencyjne wywołania
    Dsort(arr, pivot + 1, end);
    

}


void QuickSort(void *arr, int n, int conf){

                                        /* zmienna conf odpowiada za wybór rodzaju algorytmu qs
                                            0 - pivot środkowy element tablicy
                                            1 - pivot to pierwszy element tablicy
                                            2 - pivot to ostatni element tablicy
                                            3 - pivot to losowy element tablicy
                                            4 - sortowanie zmiennych double
                                            >4 - pivot to ostatni element tablicy
                                        */

    if(conf == 4){

        double *array = arr;
        Dsort(array, 0, n - 1);

    } else {

        int *array = arr;
        Isort(array, 0, n - 1, conf);

    }

}
