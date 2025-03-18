void BubbleSort(void *arr, int n, int conf){

    int* data = arr;
    int last_swap;
    int new_limit = n-1;
    
    do{
        last_swap = 0;

        for (int j = 0; j < new_limit; j++){

            if (data[j] > data[j+1]){

                int temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
                last_swap = j;

            }

        }

        new_limit = last_swap;

    }while(new_limit > 0);
    
}
