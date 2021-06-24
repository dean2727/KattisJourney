// given n numbers, what is the biggest (a_1^2 + ... + a_k^2) * (a_k+1 + ... + a_n)
// uses the prefix sum idea: the array stores the sums of the elements up to the indexes

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, i;
    cin >> n;
    vector<long long> a(n);
    vector<long long> sumsq(n+1);
    vector<long long> sumtoend(n+1);

    for (i=0;i<n;i++) cin >> a[i];
    sumsq[0] = a[0] * a[0];
    for (i=0;i<n;i++) {
        sumsq[i] = sumsq[i-1] + a[i] * a[i];
    }
    sumtoend[n] = 0;
    for (i=n-1;i>=0;i--) {
        sumtoend[i] = sumtoend[i+1] + a[i];
    }
    long long maxval = 0;
    for (i=0;i<n;i++) {
        maxval = max(maxval, sumsq[i] * sumtoend[i+1]);
    }
    cout << maxval << endl;
}