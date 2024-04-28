void selectionSort(int arr[], int left, int right)
{
    int i, j, min_idx;

    // Percorre todo o array
    for (i = left; i < right; i++)
    {
        // Encontra o índice do menor elemento restante
        min_idx = i;
        for (j = i + 1; j <= right; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
            timesInFor++;
        }

        // Troca o elemento mínimo encontrado com o primeiro elemento não ordenado
        if (min_idx != i)
        {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}
