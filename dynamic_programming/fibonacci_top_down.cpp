#include <iostream>
#include <unordered_map>
using namespace std;

// top down: remember stuff computed before

// assumes we have a recursive version of it working fine
// works better than bottom up if theres recursive version
long long Fib(int x) {
    static unordered_map<int, long long> f;
    if (f.count(x) > 0) return f[x];  // if something was computed before, return it

    long long retval;
    if (x<2) retval = 1;
    else retval = Fib(x-1) + Fib(x-2);
    f[x] = retval;
    return retval;
}

int main() {
    int x;
    cin >> x;
    cout << Fib(x) << endl;
}