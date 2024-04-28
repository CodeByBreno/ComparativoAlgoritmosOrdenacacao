void heapify(int arr[], int n, int i)
{
    int largest = i;   // Inicializa o maior como raiz
    int l = 2 * i + 1; // Esquerda = 2*i + 1
    int r = 2 * i + 2; // Direita = 2*i + 2

    // Se o filho esquerdo for maior que a raiz
    if (l < n && arr[l] > arr[largest])
    {
        largest = l;
    }

    // Se o filho direito for maior que o maior até agora
    if (r < n && arr[r] > arr[largest])
    {
        largest = r;
    }

    // Se o maior não for a raiz
    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        // Recursivamente heapify a subárvore afetada
        heapify(arr, n, largest);
        timesInFor+=2;
    }
}

void heapSort(int arr[], int left, int right)
{
    // Constrói a heap (rearranja o array)
    for (int i = right / 2 - 1; i >= left; i--)
    {
        heapify(arr, right, i);
        timesInFor+=2;
    }

    // Extrai elementos um por um da heap
    for (int i = right; i >= left; i--)
    {
        // Move a raiz atual para o final
        int temp = arr[i];
        arr[i] = arr[left];
        arr[left] = temp;
        // Chama heapify na heap reduzida
        heapify(arr, i, left);
        timesInFor+=2;
    }
}
