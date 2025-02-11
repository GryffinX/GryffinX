#include <stdio.h>


void bubbleSort(int *arr, int n) {
    if (n<=1) return;
    for (int i=0; i<n-1; ++i) {
        for (int j=0; j<n-i-1;++j) {
            if (arr[j]>arr[i]) {
                int temp = arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
}

void insertionSort(int *arr, int n) {
    if (n<=1) return;
    for (int i = 1; i < n; ++i) {
        int key=arr[i];
        int j=i-1;
        while (j>=0 && key<arr[j]) {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}

void selectionSort(int *arr, int n) {
    if (n<=1) return;
    for (int i = 0; i<n-1; ++i) {
        int key=i;
        for (int j=i+1; j<n; ++j) {
            if (arr[j]<arr[key]) {
                key=j;
            }
        }
        if (key!=i) {
            int temp=arr[key];
            arr[key]=arr[i];
            arr[i]=temp;
        }
    }
}


void quickSort(int *arr, int n) {
    if (n<=1) return;
    void swap(int *a, int *b) {
        int temp=*a;
        *a=*b;
        *b=temp;
    }

    int partition(int *arr, int low, int high) {
        int pivot=arr[high];                          // choosing the largest element as the pivot
        int i=low-1;                                 // index of the last sorted element in the array
        for (int j=low; j<high; ++j) {              // loops runs till the element before the pivot(present at index "high") 
            if (arr[j]<=pivot) {                   // if the current element is smaller than or equal to the pivot
                i++;                              // increment the index of the last sorted element
                swap(&arr[j], &arr[i]);          // swap both elements
            }
        }
        swap(&arr[i+1], &arr[high]);          // swaps the element after the last sorted element with the pivot, this ensures that the pivot is placed at its correct place in the array after current iteration
        return i+1;                          // return index of the pivot 
    }

    void sort(int *arr, int low, int high) {
        if (low < high) {                // checks and runs only when the current array or subarray has more that one element
            int pi=partition(arr, low, high); // pi receievs the index of the pivot after the partion function is called and returns a value, this can be though of as: pi receives the index of the element in the middle, elements at indices lesser than pi belong to a subarray which has elements lesser that the chosen pivot and elements at indices greater than pi belong to a subarray which has elements greater than the chosen pivot 
            // recursively call the sorting function to sort the subarrays around the returned pivot index
            sort(arr, low, pi-1);
            sort(arr, pi+1, high);
        }                 
    }
}