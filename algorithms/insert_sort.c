void InsertSort(void *arr, int n, int conf){

    int *data = arr, temp, j;

    for(int i = 1; i < n; i++){

        temp = data[i];

        j = i - 1;

        while(j >= 0 && data[j] > temp){
            data[j+1] = data[j];
            j--;
        }

        data[j + 1] = temp;

    }

}
