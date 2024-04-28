#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <locale.h>
#include <math.h>
#include <iostream>
#include <string>

#define AMOUNT_TESTS 10
#define AMOUNT_FUNCTIONS 6

int n = 10000;
int timesInFor = 0;

#include "BubbleSortBreno.cpp"
#include "InsertionSort.cpp"
#include "QuickSortDaniel.cpp"
#include "MergeSort.cpp"
#include "SelectionSortMateus.cpp"
#include "HeapSortMateus.cpp"
#include "auxiliar.cpp"

FILE *htmlFile;
struct resultTest
{
    double time;
    int forCycles;
};

typedef void (*function)(int *, int, int);

resultTest executeTest(function algorithm, int arr[])
{
    resultTest result;

    // Medindo o tempo de execu??o
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

void presentArray(int *arr)
{
    for (int j = 0; j < n; j++)
    {
        printf("%d ", arr[j]);
    }
    printf("\n");
}

void checkIfIsOrdered(int *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            printf("ERRO: Array nao ordenado\n");
            return;
        }
    }
    printf("SUCESS: Array Ordenado corretamente\n");
    return;
}

void writeInHTML(char *line, int tag)
{
    char result[250];

    switch (tag)
    {
    case 0:
        sprintf(result, "%s%s%s", "<p>", line, "</p>");
        break;
    case 1:
        sprintf(result, "%s%s%s", "<h1>", line, "</h1>");
        break;
    }

    fprintf(htmlFile, result);
}

void execute()
{
    resultTest data;
    double times[AMOUNT_FUNCTIONS][AMOUNT_TESTS], forCycles[AMOUNT_FUNCTIONS][AMOUNT_TESTS];
    function algorithms[] = {insertionSort, selectionSort, bubbleSort, quickSort, mergeSort, heapSort};
    char *algorithmsNames[] = {
        "Insertion Sort", "Selection Sort", "Bubble Sort", "Quick Sort", "Merge Sort", "Heap Sort"};

    for (int i = 0; i < AMOUNT_TESTS; i++)
    {
        unsigned long long seed = currentTimestampMillis();
        srand((unsigned)seed);
        int arr[n];
        for (int i = 0; i < n; i++)
        {
            arr[i] = rand() % (n + 1);
        }

        for (int j = 0; j < AMOUNT_FUNCTIONS; j++)
        {
            timesInFor = 0;
            int *copiedArray = copyArray(arr, n);

            if (n < 1001)
            {
                printf("\n-----------------------------------\n");
                printf("%s\n", algorithmsNames[j]);
                printf("Original array: \n");
                presentArray(arr);
            }

            data = executeTest(algorithms[j], copiedArray);

            if (n < 1001)
            {
                printf("ordered\n");
                presentArray(copiedArray);
                printf("Original array after ordering: \n");
                presentArray(arr);
            }
            else
            {
                printf("Turn %d - %s:", i, algorithmsNames[j]);
                checkIfIsOrdered(copiedArray, n);
            }

            times[j][i] = data.time;
            forCycles[j][i] = data.forCycles;
            free(copiedArray);
        }
    }

    char line[200];
    for (int j = 0; j < AMOUNT_FUNCTIONS; j++)
    {
        double avrTimes = calculateAverage(times[j], AMOUNT_TESTS);
        double avrForCycles = calculateAverage(forCycles[j], AMOUNT_TESTS);
        double timeDeviation = calculateDeviation(times[j], avrTimes, AMOUNT_TESTS);
        double cyclesDeviation = calculateDeviation(forCycles[j], avrForCycles, AMOUNT_TESTS);

        printf("\n------------------------------------------------------\n");
        printf("%s \n\n", algorithmsNames[j]);

        printf("Tempo medio das Execucoes: %.6f\n", avrTimes);
        printf("Quantidade media de comparacoes executadas: %E\n", avrForCycles);
        printf("Desvio padrao das medidas de tempo: %.6f\n", timeDeviation);
        printf("Desvio padrao das comparacoes realizadas: %.2f\n", cyclesDeviation);

        sprintf(line, "%s - Resultados: \n\n", algorithmsNames[j]);
        writeInHTML(line, 1);
        sprintf(line, "Tempo medio das Execucoes: %.6f\n", avrTimes);
        writeInHTML(line, 0);
        sprintf(line, "Quantidade media de comparacoes executadas: %E\n", avrTimes);
        writeInHTML(line, 0);
        sprintf(line, "Desvio padrao das medidas de tempo: %.6f\n", timeDeviation);
        writeInHTML(line, 0);
        sprintf(line, "Desvio padrao das comparacoes realizadas: %.2f\n", cyclesDeviation);
        writeInHTML(line, 0);
    }
}

void createHTML()
{
    fprintf(htmlFile, "<!DOCTYPE html>\n");
    fprintf(htmlFile, "<html>\n");
    fprintf(htmlFile, "<head>\n");
    fprintf(htmlFile, "<title>Algoritmos de Ordenacao</title>\n");
    fprintf(htmlFile, "</head>\n");
    fprintf(htmlFile, "<body>\n");
    fprintf(htmlFile, "<h1>Resultado</h1>\n");
}

int main()
{
    setlocale(LC_ALL, "Portuguese_Brasil");
    htmlFile = fopen("exemplo.html", "w"); // Abre o arquivo para escrita

    if (htmlFile == NULL)
    {
        printf("Erro ao criar o arquivo HTML.");
    }
    execute();

    writeInHTML("</body>\n", 0);
    writeInHTML("</html>\n", 0);
    fclose(htmlFile);

    char lixo;
    printf("Finalizar execucao?");
    scanf(" %c", &lixo);

    return 0;
}
