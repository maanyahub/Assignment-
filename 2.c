#include <stdio.h>
#include <stdlib.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for QuickSelect
int partition(int arr[], int l, int r) {
    int pivot = arr[r]; 
    int i = l;
    for (int j = l; j <= r - 1; j++) {
        if (arr[j] >= pivot) { // To find k-th largest, use >= for descending order
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}

// QuickSelect to find the k-th largest element
int kthLargest(int arr[], int l, int r, int k) {
    if (k > 0 && k <= r - l + 1) {
        int pos = partition(arr, l, r);

        // If position is the same as k
        if (pos - l == k - 1) {
            return arr[pos];
        }

        // If position is more, recurse for the left subarray
        if (pos - l > k - 1) {
            return kthLargest(arr, l, pos - 1, k);
        }

        // Otherwise, recurse for the right subarray
        return kthLargest(arr, pos + 1, r, k - pos + l - 1);
    }

    return -1; // If k is out of bounds
}

// Function to find the maximum sum of subsequence such that no two elements are adjacent
int maxNonAdjacentSum(int arr[], int n, int kLargest) {
    if (n == 0) return 0;

    // DP array to store the maximum sum at each index
    int dp[n];
    
    // Base cases
    dp[0] = (arr[0] == kLargest) ? arr[0] : 0;
    if (n > 1) {
        dp[1] = (arr[1] == kLargest) ? arr[1] : (arr[0] == kLargest ? arr[0] : (arr[0] > arr[1] ? arr[0] : arr[1]));
    }

    // Fill dp array for the rest of the elements
    for (int i = 2; i < n; i++) {
        // Include the current element if it's not adjacent
        dp[i] = (arr[i] == kLargest) ? arr[i] : dp[i-1];
        int include = arr[i] + dp[i-2];
        int exclude = dp[i-1];
        dp[i] = (include > exclude) ? include : exclude;
    }

    // We return the maximum sum at the last element
    return dp[n-1];
}

// Driver function
int main() {
    int arr[] = {5, 5, 10, 100, 10, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;

    // Step 1: Find the k-th largest element
    int kLargest = kthLargest(arr, 0, n - 1, k);
    printf("The %d-th largest element is %d\n", k, kLargest);

    // Step 2: Find the maximum sum of a subsequence that includes k-th largest element
    int maxSum = maxNonAdjacentSum(arr, n, kLargest);
    printf("The maximum sum of subsequence including %d is %d\n", kLargest, maxSum);

    return 0;
}
