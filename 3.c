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
// and the sum is divisible by d
int maxNonAdjacentSumDivisibleByD(int arr[], int n, int kLargest, int d) {
    if (n == 0) return 0;

    // dp[i][0] = Maximum sum divisible by d up to index i
    // dp[i][1] = Maximum sum not divisible by d up to index i
    int dp[n][2];

    // Base cases
    dp[0][0] = (arr[0] == kLargest && arr[0] % d == 0) ? arr[0] : 0;
    dp[0][1] = (arr[0] == kLargest && arr[0] % d != 0) ? arr[0] : 0;

    if (n > 1) {
        dp[1][0] = dp[0][0];
        dp[1][1] = dp[0][1];
        if (arr[1] == kLargest) {
            dp[1][0] = (arr[1] % d == 0) ? arr[1] : dp[1][0];
            dp[1][1] = (arr[1] % d != 0) ? arr[1] : dp[1][1];
        } else {
            if (arr[1] % d == 0) {
                dp[1][0] = (dp[0][0] > arr[1]) ? dp[0][0] : arr[1];
            } else {
                dp[1][1] = (dp[0][1] > arr[1]) ? dp[0][1] : arr[1];
            }
        }
    }

    // Fill the dp table for the rest of the elements
    for (int i = 2; i < n; i++) {
        dp[i][0] = dp[i-1][0];  // Carry over previous max sum divisible by d
        dp[i][1] = dp[i-1][1];  // Carry over previous max sum not divisible by d

        if (arr[i] == kLargest) {
            if (arr[i] % d == 0) {
                dp[i][0] = (arr[i] + dp[i-2][0] > dp[i][0]) ? arr[i] + dp[i-2][0] : dp[i][0];
            } else {
                dp[i][1] = (arr[i] + dp[i-2][1] > dp[i][1]) ? arr[i] + dp[i-2][1] : dp[i][1];
            }
        } else {
            if (arr[i] % d == 0) {
                dp[i][0] = (arr[i] + dp[i-2][0] > dp[i][0]) ? arr[i] + dp[i-2][0] : dp[i][0];
            } else {
                dp[i][1] = (arr[i] + dp[i-2][1] > dp[i][1]) ? arr[i] + dp[i-2][1] : dp[i][1];
            }
        }
    }

    // Return the maximum sum divisible by d
    return dp[n-1][0];
}

// Driver function
int main() {
    int arr[] = {5, 5, 10, 100, 10, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    int d = 10;

    // Step 1: Find the k-th largest element
    int kLargest = kthLargest(arr, 0, n - 1, k);
    printf("The %d-th largest element is %d\n", k, kLargest);

    // Step 2: Find the maximum sum of a subsequence that includes k-th largest element and is divisible by d
    int maxSum = maxNonAdjacentSumDivisibleByD(arr, n, kLargest, d);
    printf("The maximum sum of subsequence including %d and divisible by %d is %d\n", kLargest, d, maxSum);

    return 0;
}
