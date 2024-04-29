long long currentTimestampMillis()
{
    struct timeval te;
    gettimeofday(&te, NULL);                                         // Obter o tempo atual
    long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000; // Calcular o timestamp em milissegundos
    return milliseconds;
}

int *createRandomArray()
{
    // Gerando um array aleat├│rio
    unsigned long long seed = currentTimestampMillis();
    srand((unsigned)seed);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % (n + 1);
    }

    return arr;
}

double calculateAverage(double *arr, int size)
{
    double average = 0;

    for (int i = 0; i < size; i++)
    {
        average += arr[i];
    }
    average /= size;
    return average;
}

double calculateDeviation(double *arr, double avr, int size)
{
    double deviation = 0;
    for (int i = 0; i < size; i++)
    {
        deviation += (arr[i] - avr)*(arr[i] - avr);
    }
    deviation /= size;
    deviation = sqrt(deviation);
    return deviation;
}

int* copyArray(int arr[], int size) {
    int* copy = (int*)malloc(size * sizeof(int));
    if (copy == NULL) {
        printf("Erro ao alocar memória para a cópia do array.\n");
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        copy[i] = arr[i];
    }
    return copy;
}