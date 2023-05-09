#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
typedef struct
{
    int* arr;
    int n;
    int start;
}thread_args;

void merge(int arr[], int start1, int end1, int start2, int end2) {
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

void* sort(void* arg)
{
     thread_args* args = (thread_args*) arg;
     int start = args->start;
     int n = args->n;
     int* arr = args->arr;
     BubbleSort(arr, start + n / 3, start); //to only sort the portion of the array assigned to the thread.
     return NULL;
}

void BubbleSort(int arr[], int n,int start)
{
     int i, j;
     for(i = start + 1; i < n-1; i++)
     {
         for(j = 0; j < n-i-1; j++)
         {
             if(arr[j] > arr[j+1])
             {
                 int temp = arr[j];
                 arr[j] = arr[j+1];
                 arr[j+1] = temp;
             }
         }   
     }
}
int main()
{
     int n;
     printf("Enter the number of elements: ");
     scanf("%d", &n);
     clock_t start, end;
     int arr[n];
     int i;
     pthread_t threads[3];

     thread_args* args = (thread_args*) malloc(sizeof(thread_args));

     args->n = n;
     args->arr = arr;

     printf("Enter the array elements: ");
     for(i = 0;i < n; i++)
     {
        scanf("%d", &arr[i]);
     }

     start = clock();
     for (i = 0; i < 3; i++) {
        int st = i * (n / 3);
        args->start = st;
        pthread_create(&threads[i], NULL, sort, (void*)args);
    }
    for (i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
     // Merge the sorted portions of the array (otherwise all done is useless)
     int portion_size = n / 3;
     merge(arr, 0, portion_size - 1, portion_size, 2 * portion_size - 1);
     merge(arr, 0, 2 * portion_size - 1, 2 * portion_size, n - 1);
     end = clock();

     double cpu_time_used = ((double) end - start)/CLOCKS_PER_SEC;
     printf("Sorted array: \n")
     for(i = 0;i < n; i++)
     {
         printf("%d ",arr[i]);
     }
     printf("\n");
     printf("Execution time: %lf secs\n", cpu_time_used);
     printf("Burst time: %lf secs\n", cpu_time_used / n);
}


