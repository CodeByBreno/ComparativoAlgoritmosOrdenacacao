#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <locale.h>
#include <math.h>

#define AMOUNT_TESTS 10

int n = 10000;
int timesInFor = 0;

#include "BubbleSortBreno.cpp"
#include "InsertionSort.cpp"
#include "QuickSortDaniel.cpp"
#include "MergeSort.cpp"
#include "SelectionSortMateus.cpp"
#include "HeapSortMateus.cpp"

struct resultTest
{
    double time;
    int forCycles;
};

typedef void (*function)(int *, int, int);

long long currentTimestampMillis()
{
    struct timeval te;
    gettimeofday(&te, NULL);                                         // Obter o tempo atual
    long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000; // Calcular o timestamp em milissegundos
    return milliseconds;
}

resultTest executeTest(function algorithm)
{
    resultTest result;

    // Gerando um array aleat√≥rio
    unsigned long long seed = currentTimestampMillis();
    srand((unsigned)seed);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % (n + 1);
    }

    // Medindo o tempo de execuá∆o
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    algorithm(arr, 0, n - 1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    result.time = cpu_time_used;
    result.forCycles = timesInFor;

    return result;
}

void execute(function algorithm, char *text)
{
    int turn;
    resultTest aux;

    double averagaTime = 0, averageForCycles = 0;
    double times[AMOUNT_TESTS], forCycles[AMOUNT_TESTS];
    double deviationTime = 0, deviationForCycles = 0;

    for (turn = 0; turn < AMOUNT_TESTS; turn++)
    {
        timesInFor = 0;
        aux = executeTest(algorithm);
        times[turn] = aux.time;
        forCycles[turn] = aux.forCycles;
    }

    // C†lculo do valor mÇdio
    for (int i = 0; i < AMOUNT_TESTS; i++)
    {
        averagaTime += times[i];
        averageForCycles += forCycles[i];
    }
    averagaTime /= AMOUNT_TESTS;
    averageForCycles /= AMOUNT_TESTS;

    // Calculo do desvio padr∆o
    for (int i =0; i < AMOUNT_TESTS; i++){
        deviationTime += pow(times[i] - averagaTime, 2);
        deviationForCycles += pow(forCycles[i] - averageForCycles, 2);
    }
    deviationTime /= AMOUNT_TESTS;
    deviationForCycles /= AMOUNT_TESTS;
    deviationTime = sqrt(deviationTime);
    deviationForCycles = sqrt(deviationForCycles);

    printf("\n------------------------------------------------------------------");
    printf("\n%s", text);
    printf("\nTempo mÇdio de execuá∆o do c¢digo: %.10f\n", averagaTime);
    printf("Quantidade mÇdia de instruá‰es executadas para concluir o algoritmo: %E\n\n", averageForCycles);
    printf("Desvio padr∆o das medidas de tempo: %.10f\n", deviationTime);
    printf("Desvio padr∆o das medidas de quantidade de instruá‰es: %.10f\n", deviationForCycles);
}

int main()
{
    setlocale(LC_ALL, "Portuguese_Brasil");

    execute(insertionSort, "Insertion Sort");
    execute(selectionSort, "Selection Sort");
    execute(bubbleSort, "Bubble Sort");
    execute(quickSort, "Quick Sort");
    execute(mergesort, "Merge Sort");
    execute(heapSort, "Heap Sort");

    char lixo;
    printf("Finalizar execucao?");
    scanf(" %c", &lixo);

    return 0;
}