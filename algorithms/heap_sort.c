void swap(int *a, int *b){

    int temp = *a;
    *a = *b;
    *b = temp;

}

void heapify(int arr[], int n, int i) {

    int largest = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2;

    if(l < n && arr[l] > arr[largest]) 
        largest = l;
    

    if(r < n && arr[r] > arr[largest])
        largest = r;
    
    if(largest != i){

        swap(&arr[i], &arr[largest]);

        heapify(arr, n, largest);
    }

}

void HeapSort(void *arr, int n, int conf){

    int *data = arr;

    for(int i = n / 2 - 1; i >= 0; i--)
        heapify(data, n, i);
    
    for (int i = n - 1; i > 0; i--) {

        swap(&data[0], &data[i]);

        heapify(data, i, 0);
    }

}
