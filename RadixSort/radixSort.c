#include "stdlib.h"
#include "stdio.h"
#include "time.h"

int keyIndex(int num, int exp){
    return (num / exp) % 10;
}

void SortAux(int* arr[], int n, int exp){
    int *output = (int *)malloc(n * sizeof(int));
    int count[10] = {0};

    for(int i=0; i<n; i++){
        count[keyIndex((*arr)[i], exp)]++;
    }
    for(int i=1; i<10; i++){
        count[i] += count[i-1];
    }
    for(int i=n-1; i>=0; i--){
        output[count[keyIndex((*arr)[i], exp)] - 1] = (*arr)[i];
        count[keyIndex((*arr)[i], exp)]--;
    }
    for(int i=0; i<n; i++){
        (*arr)[i] = output[i];
    }
    free(output);
}

void radixSort(int arr[], int n){
    int max = arr[0];
    for(int i=1; i<n; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    for(int exp = 1; max/exp > 0; exp *= 10){
        SortAux(&arr, n, exp);
    }
}

void main(){
    int n[11] = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000, 1024000};
    float results[11][2]; // [][0] best case, [][1] worst case

    for(int i=0; i<11; i++){
        printf("Sorting array of size %d\n", n[i]);
        clock_t t1, t2;
        int size = n[i];
        int *arr = (int *)malloc(size * sizeof(int));
        // best case
        for(int j=0; j<size; j++){
            arr[j] = j;
        }
        t1 = clock();
        radixSort(arr, size);
        t2 = clock();
        results[i][0] = ((float)(t2 - t1)) / CLOCKS_PER_SEC;
        //worst case
        printf("worst case of size %d\n", n[i]);
        for(int j=0; j<size; j++){
            arr[j] = size - j;
        }
        t1 = clock();
        radixSort(arr, size);
        t2 = clock();
        results[i][1] = ((float)(t2 - t1)) / CLOCKS_PER_SEC;
        free(arr);

    }
    printf("Size\tBest Case (s)\tWorst Case (s)\n");
    for(int i=0; i<11; i++){
        printf("%d\t%.6f\t%.6f\n", n[i], results[i][0], results[i][1]);
    }
}