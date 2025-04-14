void swap(int *a, int *b){

    int temp = *a;
    *a = *b;
    *b = temp;

}

void heapify(int arr[], int n, int i) {

    // Przywracanie własności kopca dla poddrzewa zakorzenionego w indeksie i
    int largest = i;

    int l = 2 * i + 1;  // Indeks lewego dziecka
    int r = 2 * i + 2;  // Indeks prawego dziecka

    if(l < n && arr[l] > arr[largest]) 
        largest = l;
    

    if(r < n && arr[r] > arr[largest])
        largest = r;
    
    if(largest != i){

        // Jeżeli któreś z dzieci jest większe zamieniamy je
        swap(&arr[i], &arr[largest]);

        // Rekurencyjna naprawa poddrzewa
        heapify(arr, n, largest);

    }

}

void HeapSort(void *arr, int n, int conf){

    int *data = arr;

    // Budowa kopca 
    for(int i = n / 2 - 1; i >= 0; i--)
        heapify(data, n, i);
    
    for(int i = n - 1; i > 0; i--){

        // Przeniesienie korzenia (maksymalna wartość) na koniec
        swap(&data[0], &data[i]);

        // Naprawa kopca
        heapify(data, i, 0);

    }

}
