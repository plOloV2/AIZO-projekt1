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

    switch (pivot_pos) {
        case 0:
            swapI(&arr[(srt+end)/2], &arr[end]);
            break;

        case 1:
            swapI(&arr[srt], &arr[end]);
            break;
            
        case 3:
            swapI(&arr[(rand() % (end - srt)) + srt], &arr[end]);
            break;

        default:
            break;
    }
    
    int i = srt - 1;

    for(int j = srt; j < end; j++){

        if(arr[j] < arr[end])
            swapI(&arr[j], &arr[++i]);
        
    }

    swapI(&arr[++i], &arr[end]);

    return i;

}


int pivotD(double *arr, int srt, int end){

    int i = srt - 1;

    for(int j = srt; j < end; j++){

        if(arr[j] < arr[end])
            swapD(&arr[j], &arr[++i]);
        
    }

    swapD(&arr[++i], &arr[end]);

    return i;

}


void Isort(int *arr, int start, int end, int pivot_pos){
    
    if(end <= start)
        return;

    int pivot = pivotI(arr, start, end, pivot_pos);

    Isort(arr, start, pivot - 1, pivot_pos);
    Isort(arr, pivot + 1, end, pivot_pos);

}


void Dsort(double *arr, int start, int end){

    if(end <= start)
        return;

    int pivot = pivotD(arr, start, end);

    Dsort(arr, start, pivot - 1);
    Dsort(arr, pivot + 1, end);
    

}


void QuickSort(void *arr, int n, int conf){

    if(conf == 4){
        double *array = arr;
        Dsort(array, 0, n - 1);
    } else {
        int *array = arr;
        Isort(array, 0, n - 1, conf);
    }

}
