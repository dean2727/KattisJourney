#include <iostream>
#include <math.h>
using namespace std;

int main() {
    long long n, m, from, to;
    cin >> n >> m;
    for(int i=0;i<m;i++) {
        cin >> from >> to;
    }
    //cout << n*(n-1)/2-m << endl;
    long long div = 1000000007;
    long long ans = 1 + n + pow(2, n*(n-1)/2-m);
    ans = ans % div;
    cout << ans;
}