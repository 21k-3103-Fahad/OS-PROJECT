#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

struct args {  //to pass args
    int* arr;
    int start;
    int end;
};

void merge(int* arr, int start, int mid, int end) {
    //standard merging procedure
    int i, j, k;
    int n1 = mid - start + 1;
    int n2 = end - mid;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[start + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = start;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void* merge_sort(void* arg) {
    struct args* args = (struct args*) arg;
    int start = args->start;
    int end = args->end;
    if (start < end) {
        int mid = (start + end) / 2;
        //using each thread for each half of the array
        struct args left_args = {args->arr, start, mid};
        struct args right_args = {args->arr, mid + 1, end};
        pthread_t left_thread, right_thread;
        pthread_create(&left_thread, NULL, merge_sort, (void*) &left_args);
        pthread_create(&right_thread, NULL, merge_sort, (void*) &right_args);
        //waiting for threads to complete
        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);
        //now merging the thread
        merge(args->arr, start, mid, end);
    }
    pthread_exit(NULL);
}

int main() {
    int n, i;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int* arr = (int*) malloc(n * sizeof(int));
    printf("Enter the elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    struct args args = {arr, 0, n - 1};
    pthread_t main_thread;
    clock_t start, end;
    start = clock();
    pthread_create(&main_thread, NULL, merge_sort, (void*) &args);
    pthread_join(main_thread, NULL);
    end = clock();
    double cpu_time_used = ((double)end - start)/CLOCKS_PER_SEC;
    printf("Sorted array: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    printf("Execution time: %lf secs\n",cpu_time_used);
    printf("Burst time: %lf secs\n",cpu_time_used/n);
    free(arr);
    return 0;
}
