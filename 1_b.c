#include <stdio.h>
#include <stdlib.h>

// Swap function to exchange elements in the array
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function to partition the array around a pivot element
int partition(int arr[], int l, int r, int x) {
    int i;
    for (i = l; i < r; i++) {
        if (arr[i] == x) {
            break;
        }
    }
    // Move pivot element to the end
    swap(&arr[i], &arr[r]);

    i = l;
    for (int j = l; j <= r - 1; j++) {
        if (arr[j] <= x) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    // Move pivot element to its correct position
    swap(&arr[i], &arr[r]);
    return i;
}

// A simple function to find the median of a small array (up to 5 elements)
int findMedian(int arr[], int n) {
    qsort(arr, n, sizeof(int), (int (*)(const void*, const void*))compare);
    return arr[n / 2];
}

// Compare function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Recursive function to find the k-th smallest element using the Median of Medians approach
int kthSmallest(int arr[], int l, int r, int k) {
    // If k is within the range
    if (k > 0 && k <= r - l + 1) {
        int n = r - l + 1; // Number of elements in the array

        // Divide arr[] into groups of 5 elements, find the median of each group
        int i, median[(n + 4) / 5]; // There are ceil(n / 5) groups
        for (i = 0; i < n / 5; i++) {
            median[i] = findMedian(arr + l + i * 5, 5);
        }

        // For the last group with less than 5 elements
        if (i * 5 < n) {
            median[i] = findMedian(arr + l + i * 5, n % 5);
            i++;
        }

        // Find the median of medians recursively
        int medOfMed = (i == 1) ? median[0] : kthSmallest(median, 0, i - 1, i / 2);

        // Partition the array around the median of medians
        int pos = partition(arr, l, r, medOfMed);

        // If pos is the k-th element, return the element at pos
        if (pos - l == k - 1) {
            return arr[pos];
        }

        // If pos is greater, recurse for the left subarray
        if (pos - l > k - 1) {
            return kthSmallest(arr, l, pos - 1, k);
        }

        // Otherwise, recurse for the right subarray
        return kthSmallest(arr, pos + 1, r, k - pos + l - 1);
    }

    // If k is out of bounds
    return -1;
}

// Function to find the median of the array
int findMedianOfArray(int arr[], int n) {
    // For odd-sized arrays, the median is the middle element
    if (n % 2 == 1) {
        return kthSmallest(arr, 0, n - 1, n / 2 + 1);
    } else {
        // For even-sized arrays, the median is the average of the two middle elements
        int med1 = kthSmallest(arr, 0, n - 1, n / 2);
        int med2 = kthSmallest(arr, 0, n - 1, n / 2 + 1);
        return (med1 + med2) / 2;
    }
}

// Driver code to test the function
int main() {
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Find the 4th smallest element (example)
    int k = 4;
    printf("K-th smallest element is %d\n", kthSmallest(arr, 0, n - 1, k));

    // Find the median of the array
    int median = findMedianOfArray(arr, n);
    printf("The median of the array is %d\n", median);

    return 0;
}
