#include "stdlib.h"
#include "stdio.h"
#include "time.h"

void gnomeSort(int arr[], int n){
    int index = 0;
    while(index < n){
        if(index == -1)
            index++;
        if(arr[index +1 ] >= arr[index])
            index++;
        else{   
            int temp = arr[index];
            arr[index] = arr[index + 1];
            arr[index + 1] = temp;
            index--;
        }
    }
}

void main(){
    int n[9] = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000};
    float results[9][2]; // [][0] best case, [][1] worst case

    for(int i=0; i<9; i++){
        printf("Sorting array of size %d\n", n[i]);
        clock_t t1, t2;
        int size = n[i];
        int *arr = (int *)malloc(size * sizeof(int));
        // best case
        for(int j=0; j<size; j++){
            arr[j] = j;
        }
        t1 = clock();
        gnomeSort(arr, size);
        t2 = clock();
        results[i][0] = ((float)(t2 - t1)) / CLOCKS_PER_SEC;
        //worst case
        printf("worst case of size %d\n", n[i]);
        for(int j=0; j<size; j++){
            arr[j] = size - j;
        }
        t1 = clock();
        gnomeSort(arr, size);
        t2 = clock();
        results[i][1] = ((float)(t2 - t1)) / CLOCKS_PER_SEC;
        free(arr);
    }
    printf("Size\tBest Case (s)\tWorst Case (s)\n");
    for(int i=0; i<9; i++){
        printf("%d\t%.6f\t%.6f\n", n[i], results[i][0], results[i][1]);
    }
}