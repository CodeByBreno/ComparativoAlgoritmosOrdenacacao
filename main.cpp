#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <locale.h>
#include <math.h>
#include <iostream>
#include <string>
#include <string.h>

#define AMOUNT_TESTS 10
#define AMOUNT_FUNCTIONS 6
#define DEBUG false

int n = 10000;
int timesInFor = 0;

FILE *htmlFile;

double times[AMOUNT_FUNCTIONS][AMOUNT_TESTS], forCycles[AMOUNT_FUNCTIONS][AMOUNT_TESTS];
char *algorithmsNames[] = { "Insertion Sort", "Selection Sort", "Bubble Sort", "Quick Sort", "Merge Sort", "Heap Sort"};

#include "BubbleSortBreno.cpp"
#include "InsertionSort.cpp"
#include "QuickSortDaniel.cpp"
#include "MergeSort.cpp"
#include "SelectionSortMateus.cpp"
#include "HeapSortMateus.cpp"
#include "auxiliar.cpp"
#include "Visual.cpp"

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

void execute()
{
    resultTest data;
    function algorithms[] = {insertionSort, selectionSort, bubbleSort, quickSort, mergeSort, heapSort};

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

            if (n < 1001 || DEBUG)
            {
                printf("\n-----------------------------------\n");
                printf("%s\n", algorithmsNames[j]);
                printf("Original array: \n");
                presentArray(arr);
                getchar();
            }

            data = executeTest(algorithms[j], copiedArray);

            if (n < 1001 || DEBUG)
            {
                printf("ordered\n");
                presentArray(copiedArray);
                printf("Original array after ordering: \n");
                presentArray(arr);
                getchar();
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

    writeInHTML("\n\t\t<table class=\"main_table\">\n"
                    "\t\t<tr class=\"table_header\">\n"
                        "\t\t\t<th>Algoritmo</th>\n"
                        "\t\t\t<th>Tempo de Execucao</th>\n"
                        "\t\t\t<th>Quantidade de Instrucoes</th>\n"
                        "\t\t\t<th>Desvio Padrao do Tempo de Execucoes</th>\n"
                        "\t\t\t<th>Desvio Padrao da Quantidade de Instrucoes</th>\n"
                    "\t\t</tr>\n", 50);
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
        printf("Quantidade media de comparacoes executadas: %.3E\n", avrForCycles);
        printf("Desvio padrao das medidas de tempo: %.6f\n", timeDeviation);
        printf("Desvio padrao das comparacoes realizadas: %.2f\n", cyclesDeviation);

        writeInHTML("\t\t<tr>\n", 50);
        sprintf(line, "%s", algorithmsNames[j]);
        writeInHTML(line, 0);
        sprintf(line, "%.4fms", avrTimes);
        writeInHTML(line, 0);
        sprintf(line, "%.2E", avrForCycles);
        writeInHTML(line, 0);
        sprintf(line, "%.4f", timeDeviation);
        writeInHTML(line, 0);
        sprintf(line, "%.2f", cyclesDeviation);
        writeInHTML(line, 0);
        writeInHTML("\t\t\t</tr>\n", 50);
    }

    writeInHTML("\t</table>\n", 50);
}

int main()
{
    setlocale(LC_ALL, "Portuguese_Brasil");
    htmlFile = fopen("analise.html", "w"); // Abre o arquivo para escrita

    if (htmlFile == NULL)
    {
        printf("Erro ao criar o arquivo HTML.");
    }

    createHTML();
    execute();
    buildCaption();
    buildDetailedTables();

    writeInHTML("\t</body>\n", 50);
    writeInHTML("</html>\n", 50);
    fclose(htmlFile);

    return 0;
}
