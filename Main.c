#include <stdio.h>
#include <stdlib.h>
#include "bubblesort.h"
#include "quicksort.h"
#include "selectionsort.h"
#include "heapsort.h"
#include "insertionsort.h"
#include "binaryinsertionsort.h"
#include "mergesort.h"
#include "bucketsort.h"
#include "radixsort.h"

#define MAX_NOMES 20000
#define MAX_NOMES_TAM 100

int main(){
    char *nomes_copia;
    int num_elementos = 0;
    int opcao = 0;
    int opcaoTamanho = 0;
    int opcaoCaso = 0;
    char **v = (char **)malloc(MAX_NOMES * sizeof(char *));
    while (1){
        printf ("\nQual algoritmo de ordenacao voce deseja acessar?\n");
        printf("1 - Bubble Sort\n");
        printf("2 - Quick Sort\n");
        printf("3 - Selection Sort\n");
        printf("4 - Heap Sort\n");
        printf("5 - Insertion Sort\n");
        printf("6 - Binary Insertion Sort\n");
        printf("7 - Merge Sort\n");
        printf("8 - Bucket Sort\n");
        printf("9 - Radix Sort\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                menuBubbleSort();
                break;
            case 2:
                menuQuickSort();  
                break;
            case 3:
                menuSelectionSort();  
                break;
            case 4:
                menuHeapSort();
                break;
            case 5:
                menuInsertionSort();
                break;
            case 6:
                menuBinaryInsertionSort();
                break;
            case 7:
                menuMergeSort();
                break;
            case 8:
                menuBucketSort();
                break;
            case 9:
                menuRadixSort();
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    }
    free(v);
    return 0;
}
