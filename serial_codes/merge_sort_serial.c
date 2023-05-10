#include <stdio.h>
#include <time.h>
// Function to merge two subarrays of arr[].
// First subarray is arr[left..mid], second subarray is arr[mid+1..right]
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1; //left subarray length
    int n2 = right - mid;   //right subarray length
 
    int L[n1], R[n2];  //our sub arrays
 
    //moving values into subarrays
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
 
    i = 0;
    j = 0;
    k = left;
        // Merge the two sorted subarrays
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
    //copy remanining elements of L[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
     //copy remaining elements of R[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  //finding midpoint
        mergeSort(arr, left, mid);  //sorting first half recursively
        mergeSort(arr, mid + 1, right);  //sorting second half recursively
        merge(arr, left, mid, right);   //merging the halves together
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
    start = clock();
    mergeSort(arr, 0, n - 1);
    end = clock();
    double cpu_time_used = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Execution time: %lf secs \n",cpu_time_used);
    printf("Burst time: %lf secs \n", cpu_time_used / n);
    return 0;
}
