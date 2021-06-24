#include <iostream>
#include <math.h>
using namespace std;

int main() {
    long long D;
    cin >> D;
    /*
    n2^2 - n1^2 <= 200,000
    Thus, the smallest n2 can be is 1 more than n1:
    (n1+1)^2-n1^2 <= 200,000
    -> n1^2 + 2n1 + 1 - n1^2 <= 200,000
    -> 2n1 + 1 <= 200,000
    -> n1 < 100,000
    */
    for (int n1=0;n1<=100000;n1++) {
        long long n2 = pow(n1,2) + D;
        if (n2-pow(n1,2)>D) break;
        // is n2 a square
        double n2sqrt = sqrt(n2);
        if (n2sqrt == (int)n2sqrt) {
            cout << n1 << " " << (int)n2sqrt;
            return 0;
        }
    }
    cout << "impossible";
}