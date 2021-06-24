#include <iostream>
#include <algorithm>
using namespace std;

bool cmp(const int& a, const int& b) {
  return a > b;
}

int main() {
    // input
    int n = 0;
    cin >> n;
    int A[n];

    int cit;
    for (int i=0;i<n;i++) {
      cin >> cit;
      A[i] = cit;
    }

    sort(A, A + n, cmp);

    int i = 0;
    while (A[i] > i + 1) {
      i++;
    }
    cout << i - 1;
}
