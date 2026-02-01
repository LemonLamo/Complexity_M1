#include "stdlib.h"
#include "stdio.h"
#include "time.h"

int partition(int arr[], int low, int high){
    int pivot = arr[low + (high - low)/2];
    int i = low -1; 
    for(int j = low; j <= high - 1; j++){
        if(arr[j] < pivot){
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high){
    if(low >= high || low < 0) return;
        int q = partition(arr, low, high);
        quickSort(arr, low, q-1);
        quickSort(arr, q + 1, high);
    
}

int main(){
    int n[15] = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000, 1024000, 2048000, 4096000, 8192000, 16384000};
    float results[15][2]; // [][0] best case, [][1] worst case

    for(int i=0; i<15; i++){
        printf("Sorting array of size %d\n", n[i]);
        clock_t t1, t2;
        int size = n[i];
        int *arr = (int *)malloc(size * sizeof(int));
        if(!arr){
            fprintf(stderr, "malloc failed for size %d\n", size);
            return 1;
        }
        // best case
        for(int j=0; j<size; j++){
            arr[j] = j;
        }
        t1 = clock();
        quickSort(arr, 0, size-1);
        t2 = clock();
        results[i][0] = ((float)(t2 - t1)) / CLOCKS_PER_SEC;
        //worst case
        printf("worst case of size %d\n", n[i]);
        for(int j=0; j<size; j++){
            arr[j] = size - j;
        }
        t1 = clock();
        quickSort(arr, 0, size-1);
        t2 = clock();
        results[i][1] = ((float)(t2 - t1)) / CLOCKS_PER_SEC;
        free(arr);

    }
    printf("Size\tBest Case (s)\tWorst Case (s)\n");
    for(int i=0; i<15; i++){
        printf("%d\t%.6f\t%.6f\n", n[i], results[i][0], results[i][1]);
    }
}