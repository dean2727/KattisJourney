//#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
int maxSubArraySum(int a[], int size, int cost)
{
    int max_so_far = INT_MIN, max_ending_here = 0;
    int num_elem = 0;
 
    for (int i = 0; i < size; i++)
    {
        max_ending_here = max_ending_here + a[i];
        //cout << max_ending_here << endl;
        if (max_so_far < max_ending_here)
            max_so_far = max_ending_here;
 
        if (max_ending_here < 0)
            max_ending_here = 0;
    }
    return max_so_far;
}

int main() {
    int N, P, num;
    cin >> N >> P;
    
    int arr[N];
    for (int i=0;i<N;i++) {
        cin >> num;
        arr[i] = num - P;
    }

    cout << maxSubArraySum(arr, N, P);

}