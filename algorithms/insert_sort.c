void InsertSort(void *arr, int n, int conf){

    int *data = arr, temp, j;

    // Główna pętla sortująca - iteruje przez elementy nieposortowane
    for(int i = 1; i < n; i++){

        temp = data[i]; // Pobieranie aktualnego elementu do wstawienia

        j = i - 1;

        // Przesuwanie elementów większych od temp w prawo
        while(j >= 0 && data[j] > temp){
            data[j+1] = data[j];
            j--;
        }

        // Wstawienie elementu na odpowiednie miejsce w posortowanej części
        data[j + 1] = temp;

    }

}
