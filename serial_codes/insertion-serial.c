#include <stdio.h>
#include <time.h>
#include <omp.h>
void insertion_sort(int arr[], int n)
{
    int i, j;
    for(i = 1; i < n; ++i)
    {   //taking key as ith value of the array
        int key = arr[i];
        j = i - 1;
        //will run as long as arr[j] is greater than the key
        while(j >= 0 && arr[j] > key)
        {
            /*This is done to shift the elements of the array arr that are 
            greater than key one position to the right.*/
            arr[j+1] = arr[j];
            j = j - 1; 
        }
        //key will now be inserted into correct position at arr[j+1]
         arr[j+1] = key;
    } 
}

int main(){
    int arr[] = {5, 4, 3, 2, 87, 43, 56, 1};
    int n = sizeof(arr)/sizeof(int);  //to get the length of the array
    clock_t start, end;  //for finding clock times

    start = clock();
    insertion_sort(arr, n);
    end = clock();
    int i;
    printf("Sorted array: \n");
    //now printing the array after sorting
    for(int i = 0; i < n; i++)
    {
        printf("%d ",arr[i]);
    }

    printf("\n");
    double cpu_time_used = ((double)end - start)/CLOCKS_PER_SEC;
    printf("Execution time: %lf secs \n",cpu_time_used);
    printf("Burst time: %lf secs\n",cpu_time_used/n);
}