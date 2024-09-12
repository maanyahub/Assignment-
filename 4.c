#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function used in QuickSelect
int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int i = left;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[right]);
    return i;
}

// QuickSelect function to find k-th smallest element
int quickselect(int arr[], int left, int right, int k) {
    if (left == right) {
        return arr[left];
    }
    
    int pivotIndex = partition(arr, left, right);
    
    if (k == pivotIndex) {
        return arr[k];
    } else if (k < pivotIndex) {
        return quickselect(arr, left, pivotIndex - 1, k);
    } else {
        return quickselect(arr, pivotIndex + 1, right, k);
    }
}

// Function to find the median
int find_median(int arr[], int n) {
    return quickselect(arr, 0, n - 1, n / 2);
}

// Structure to hold an element and its absolute difference from the median
typedef struct {
    int value;
    int diff;
} Element;

// Partition function for sorting elements based on their differences
int partition_elements(Element arr[], int left, int right) {
    int pivot = arr[right].diff;
    int i = left;
    for (int j = left; j < right; j++) {
        if (arr[j].diff <= pivot) {
            Element temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }
    Element temp = arr[i];
    arr[i] = arr[right];
    arr[right] = temp;
    return i;
}

// QuickSelect for Element array based on differences
void quickselect_elements(Element arr[], int left, int right, int k) {
    if (left >= right) return;
    
    int pivotIndex = partition_elements(arr, left, right);
    
    if (k < pivotIndex) {
        quickselect_elements(arr, left, pivotIndex - 1, k);
    } else if (k > pivotIndex) {
        quickselect_elements(arr, pivotIndex + 1, right, k);
    }
}

// Function to find k elements closest to the median
void find_k_closest_to_median(int S[], int n, int k) {
    // Step 1: Find the median
    int median = find_median(S, n);
    
    // Step 2: Calculate absolute differences
    Element diff[n];
    for (int i = 0; i < n; i++) {
        diff[i].value = S[i];
        diff[i].diff = abs(S[i] - median);
    }
    
    // Step 3: Use QuickSelect to find k smallest differences
    quickselect_elements(diff, 0, n - 1, k - 1);
    
    // Step 4: Output the k closest numbers to the median
    printf("The %d numbers closest to the median are:\n", k);
    for (int i = 0; i < k; i++) {
        printf("%d ", diff[i].value);
    }
    printf("\n");
}

// Main function to test the code
int main() {
    int S[] = {12, 3, 5, 7, 19, 26};
    int n = sizeof(S) / sizeof(S[0]);
    int k = 3;
    
    find_k_closest_to_median(S, n, k);
    
    return 0;
}
