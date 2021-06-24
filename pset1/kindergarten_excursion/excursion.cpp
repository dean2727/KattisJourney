#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// need to use merge sort (O(n log n)) because other sorts are O(n^2)
// and there are up to 1,000,000 characters

// used https://www.geeksforgeeks.org/merge-sort/ to help me
void merge(int arr[], int l, int m, int r, int& numSwaps)
{
    //cout << "in merge\n";
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
 
    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
        //cout << arr[l + i] << endl;
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
        //cout << arr[m + 1 + j] << endl;
    }
 
    int i = 0, j = 0, k = l;
 
    while (i < n1 && j < n2) {
        //cout << "Loop " << k << " for this merge. L[i], R[j] = " << L[i] << ", " << R[j] << endl;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;

            //numSwaps++;
        }
        else {
            arr[k] = R[j];
            j++;

            
            //numSwaps++;
        }
        
        k++;
    }
 
    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int array[], int l, int r, int& numSwaps) {
    if (l >= r) {
        return;
    }
    int m = (l + r - 1) / 2;
    mergeSort(array, l, m, numSwaps);
    mergeSort(array, m + 1 , r, numSwaps);
    //cout << "Calling merge on l = " << l << ", m = " << m << ", and r = " << r << endl;
    merge(array, l , m, r, numSwaps);
}


int main() {
    string nums;
    cin >> nums;

    int intNums[nums.length()];

    for (int i = 0; i < nums.length(); i++) {
        char num = nums[i];
        intNums[i] = (int)num - 48;
    }

    int numSwaps = 0;
    mergeSort(intNums, 0, nums.length() - 1, numSwaps);

    cout << numSwaps;
}