#include <stdio.h>
#include <time.h>
#include <omp.h>
//this function will merge the split array
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
 
    int L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    /*The for loops fill the temporary arrays with elements from the sub-arrays.*/
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
     /*This while loop compares the elements in the two sub-arrays 
     and copies them into the main array in sorted order.*/
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
 //recursively calls itself to divide itself as much as possible

void mergeSort(int arr[], int left, int right) 
{

    if (left < right) 
    {
        int mid = left + (right - left) / 2;
        /*parallelizing the function calls, so we carry on them parallel*/
        #pragma omp parallel sections 
        {
           #pragma omp section 
           {
              mergeSort(arr, left, mid); 
           }
           #pragma omp section 
           {
              mergeSort(arr, mid + 1, right); 
           } 
        }
        /* #pragma omp parallel sections directive creates two parallel 
        sections for the left and right halves, 
        and the #pragma omp section directive assigns each section to a thread. 
        The #pragma omp task directive creates a task for merging the two halves.
        #pragma omp task */
        {
              merge(arr, left, mid, right); 
        }
    }
} 
 
int main() {
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);
 
    printf("Original array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
     clock_t start, end;
     double cpu_time_used;
      start = clock();
     #pragma omp parallel
     { 
       #pragma omp single 
       {
           mergeSort(arr, 0, n - 1);
       }
    }
     
     end = clock();
     
     cpu_time_used = ((double)end - start)/ CLOCKS_PER_SEC;
     
    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    printf("Execution time: %lf secs\n",cpu_time_used);
    printf("Burst time: %lf secs\n",cpu_time_used/n);
    return 0;
}
