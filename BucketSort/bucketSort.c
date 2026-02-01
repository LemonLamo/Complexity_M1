#include "stdlib.h"
#include "stdio.h"
#include "time.h"

void insertionSort(int* bucket, int size) {
    for (int i = 1; i < size; ++i) {
        int key = bucket[i];
        int j = i - 1;
        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

void BucketSort(int arr[], int n){
    int bucketCount = 10;
    int** buckets = (int**)malloc(bucketCount * sizeof(int*));
    int* bucketSizes = (int*)calloc(bucketCount, sizeof(int));
    int* bucketCapacities = (int*)malloc(bucketCount * sizeof(int));

    for (int i = 0; i < bucketCount; i++) {
        bucketCapacities[i] = n / bucketCount + 1;
        buckets[i] = (int*)malloc(bucketCapacities[i] * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        int index = arr[i] * bucketCount / (n + 1);
        if (bucketSizes[index] == bucketCapacities[index]) {
            bucketCapacities[index] *= 2;
            buckets[index] = (int*)realloc(buckets[index], bucketCapacities[index] * sizeof(int));
        }
        buckets[index][bucketSizes[index]++] = arr[i];
    }

    int idx = 0;
    for (int i = 0; i < bucketCount; i++) { 
        insertionSort(buckets[i], bucketSizes[i]);
        for (int j = 0; j < bucketSizes[i]; j++) {
            arr[idx++] = buckets[i][j];
        }
        free(buckets[i]);
    }

    free(buckets);
    free(bucketSizes);
    free(bucketCapacities);

}

int main(){
    int n[11] = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000, 1024000};
    float results[11][2]; // [][0] best case, [][1] worst case

    for(int i=0; i<11; i++){
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
        BucketSort(arr, size);
        t2 = clock();
        results[i][0] = ((float)(t2 - t1)) / CLOCKS_PER_SEC;
        //worst case
        printf("worst case of size %d\n", n[i]);
        for(int j=0; j<size; j++){
            arr[j] = size - j;
        }
        t1 = clock();
        BucketSort(arr, size);
        t2 = clock();
        results[i][1] = ((float)(t2 - t1)) / CLOCKS_PER_SEC;
        free(arr);

    }
    printf("Size\tBest Case (s)\tWorst Case (s)\n");
    for(int i=0; i<11; i++){
        printf("%d\t%.6f\t%.6f\n", n[i], results[i][0], results[i][1]);
    }
}