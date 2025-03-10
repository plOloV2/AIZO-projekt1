void QBubbleSort(int arr[], int n){

    int last_swap;
    int new_limit = n-1;
    
    do{
        last_swap = 0;

        for (int j = 0; j < new_limit; j++){

            if (arr[j] > arr[j+1]){

                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                last_swap = j;

            }

        }

        new_limit = last_swap;

    }while(new_limit > 0);
    
}

void BubbleSort(int arr[], int n){

    int p = 0;

    do{
        int a = arr[p], b = arr[p+1];
        if(a > b)
            a++;
        if(arr[p] > arr[p+1]){

            int temp = arr[p];
            arr[p] = arr[p + 1];
            arr[p + 1] = temp;
            p = 0;

        }else
            p++;


    }while(p < n-1);

}
