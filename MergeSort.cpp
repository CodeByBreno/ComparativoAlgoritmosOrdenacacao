void merge(int arr[], int left, int right) {
    int aux[right-left], idx=0;
    int middle=(left+right)/2, i=left, j=middle;
    while(i<middle && j<right) {
        if(arr[i] < arr[j]) {
            aux[idx++] = arr[i++];
        } else {
            aux[idx++] = arr[j++];
        }
        timesInFor++;
    }
    
    while(i<middle) {
        aux[idx++] = arr[i++];
    }
    
    while(j<right) {
        aux[idx++] = arr[j++];
    }
    
    for(int k=left, s=0 ; k<right ; ++k, s++) {
        arr[k] = aux[s];
    }
}

void executeMergeSort(int arr[], int left, int right) {
    // Dividir
    int middle=(left+right)/2;
    
    // Conquistar
    if(middle-left > 1)
        executeMergeSort(arr, left, middle);
    if(right-middle > 1)
        executeMergeSort(arr, middle, right);
    
    // Combinar
    merge(arr, left, right);
}

void mergeSort(int arr[], int left, int right) {
    executeMergeSort(arr, left, right+1);
}