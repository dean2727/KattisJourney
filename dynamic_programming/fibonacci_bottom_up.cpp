#include <iostream>
#include <vector>
using namespace std;

// bottom up: compute f(0), then f(1), f(2), etc...
// good to use if you have to compute everything anyways
long long Fib(int x) {
    vector<long long> f(x+1);
    f[0] = 1;
    f[1] = 1;
    for (int i=2;i<=x;i++) f[i] = f[i-1] + f[i-2];
    return f[x];
}

int main() {
    int x;
    cin >> x;
    cout << Fib(x) << endl;
}