#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
/* the program initializes an array of integers and spawns four threads to sort different portions of the array using the insertion sort algorithm. 
Each thread receives an argument that specifies the start index of the portion of the array it is responsible for sorting. 
The threads then call the insertion_sort() function,
passing in the start index as an argument.

After all the threads have finished sorting their portions of the array, 
the main thread waits for them to join, and then prints out the sorted array.*/

typedef struct
{
    int st;
    int n;
    int* arr;
}thread_args;

void merge(int arr[], int start1, int end1, int start2, int end2) {
    //to merge arrays once the thread sorting is done
    int i = start1;
    int j = start2;
    int k = 0;
    int temp[end2 - start1 + 1];

    while (i <= end1 && j <= end2) {
        if (arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= end1) {
        temp[k++] = arr[i++];
    }

    while (j <= end2) {
        temp[k++] = arr[j++];
    }

    for (i = start1; i <= end2; i++) {
        arr[i] = temp[i - start1];
    }
}

void insertion_sort(int arr[], int n, int start)
{   //main insertion sort algorithm
    int i, key, j;
    for (i = start + 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= start && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void* sort(void* arg)
{   //dividing the array, then solving it parallel
    thread_args* args = (thread_args*) arg;
    int start = args->st;
    int* arr = args->arr;
    int n = args->n;
    insertion_sort(arr, n, start);
    return NULL;
}

int main()
{
    pthread_t threads[4];  //using 4 threads 
    int i;

   int arr[] = {5, 4, 3, 2, 87, 43, 56};
   int n = sizeof(arr) / sizeof(int);
   //creating the thread arguments, by size of the structure of the parameters
   thread_args* args = (thread_args*) malloc(sizeof(thread_args));
   args->n = n;
   args->arr = arr;
   
   clock_t start, end;
   start = clock();
    for (i = 0; i < 4; i++) {
        int st = i * (n / 4);   //st is our start index
        args->st = st;
        pthread_create(&threads[i], NULL, sort, (void*)args);
    }

    for (i = 0; i < 4; i++) {  //waiting for all threads to finish
        pthread_join(threads[i], NULL);
    }
    // Merge the sorted portions of the array (otherwise all done is useless)
    int portion_size = n / 4;
    //merge the divided arrays together
    merge(arr, 0, portion_size - 1, portion_size, 2 * portion_size - 1);
    merge(arr, 0, 2 * portion_size - 1, 2 * portion_size, n - 1);
    end = clock();
     double cpu_time_used = ((double)end - start)/CLOCKS_PER_SEC;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("Thread execution time: %lf secs\n", cpu_time_used);
    printf("Thread Burst time: %lf secs\n",cpu_time_used/n);
    return 0;
}
