// Função para trocar dois elementos de um array
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para dividir o array e pegar o pivô
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // pivô
    int i = (low - 1); // índice do menor elemento

    for (int j = low; j <= high - 1; j++) {
        timesInFor++;

        // Se o elemento atual for menor ou igual ao pivô
        if (arr[j] <= pivot) {
            i++; // incrementa o índice do menor elemento
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Função principal que implementa o algoritmo Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pi é o índice de divisão, arr[p] é agora
        // no local correto
        int pi = partition(arr, low, high);

        // Ordena os elementos separadamente antes
        // e depois da partição
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}