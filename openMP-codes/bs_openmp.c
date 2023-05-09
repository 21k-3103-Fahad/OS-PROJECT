#include <stdio.h>
#include <omp.h>
#include <time.h>

void BubbleSort(int arr[], int n)
{
    int i, j;
#pragma omp parallel
    {
        for (i = 0; i < n - 1; i++)
        {
            for (j = 0; j < n - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        } }
}

int main()
{
     int n;
     printf("Enter the number of elements: ");
     scanf("%d", &n);
     clock_t start, end;
     int arr[n];
     int i;
     
     printf("Enter the array elements: ");
     for(i = 0;i < n; i++)
     {
         scanf("%d", &arr[i]);
     }
     //solving the standard bubbleSort, with multiple threads
     start = clock();
     #pragma omp parallel
     {
        #pragma omp single
             BubbleSort(arr, n);
     }
     end = clock();
     double cpu_time_used = ((double)end - start)/CLOCKS_PER_SEC;
     for(i = 0;i < n; i++)
     {
         printf("%d ",arr[i]);
     }
     printf("\n");
     printf("Execution time: %lf secs\n",cpu_time_used);
     printf("Burst time: %lf secs\n",cpu_time_used/n);
}


