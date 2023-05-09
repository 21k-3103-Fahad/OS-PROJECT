#include <stdio.h>
#include <time.h>
#include <omp.h>

void parallel_insertion_sort(int arr[], int n)
{
    int i, j, key;
    /*used to parallelize the inner loop, which allows 
    multiple threads to work on different parts of the array simultaneously.*/
    for(i = 1; i < n; ++i)
    {
        key = arr[i];
        j = i - 1;

        #pragma omp parallel for
        for(j = i - 1; j >= 0; --j)
        {
            if(arr[j] > key)
            {
                arr[j+1] = arr[j];
            }
            else
            {
                break;
            }
        }
        arr[j+1] = key;
    }
}

int main()
{
    int arr[] = {5, 4, 3, 2, 87, 43, 56, 1};
    int n = sizeof(arr) / sizeof(int);
    clock_t start, end;

    start = clock();  //these are our clock variables
    parallel_insertion_sort(arr, n);
    end = clock();
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    //finding burst time
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Parallel execution time: %lf secs\n", cpu_time_used);
    printf("Parallel Burst time: %lf secs\n",cpu_time_used/n);
    return 0;
}