void bubbleSort(int arr[], int low, int high) {
    int i, j, aux;
    for (i = 0; i < high; i++){
        for (j = 0; j < n - i - 1; j++){
            if (arr[j] > arr[j+1]){
                aux = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = aux;
            }
            timesInFor++;
        }
    }
}