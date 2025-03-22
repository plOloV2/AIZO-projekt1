int gap1[] = {16577, 4193, 1073, 281, 77, 23, 1};                       // https://oeis.org/A036562
int gap2[] = {13776, 4592, 1968, 861, 336, 112, 48, 21, 7, 3, 1};       // https://oeis.org/A036569


void Ssort(int *data, int n, int *gap){
    
    int i = 0;

    do{

        for(int j = gap[i]; j < n; j++){

            int temp = data[j], k;

            for(k = j; k >= gap[i] && data[k - gap[i]] > temp; k -= gap[i])
                data[k] = data[k - gap[i]];

            data[k] = temp;
        }

    } while(gap[i++] > 1);

}


void Shellsort(void *arr, int n, int conf){

    int *data = arr;

    if(conf == 0){

        Ssort(data, n, gap1);

    }else{

        Ssort(data, n, gap2);

    }

}
