#include <iostream>

using namespace std;

long long Fib(int x) {
    if (x<2) return 1;
    return Fib(x-1) + Fib(x-2);
}

int main() {
    int x;
    cin >> x;
    cout << Fib(x) << endl;
}