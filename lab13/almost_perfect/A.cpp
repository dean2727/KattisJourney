#include <iostream>
#include <math.h>
#include <set>
using namespace std;

int main() {
    int p;
    while (cin >> p) {
        int s = 0;
        set<int> divisors;
        for (int d=1;d<=floor(sqrt(p));d++) {
            if (p % d == 0) {
                divisors.insert(d);
                if (p / d != p)
                    divisors.insert(p / d);
            }
        }
        for (auto& it : divisors) {
            s += it;
        }

        cout << p << " ";
        if (s == p) {
        cout << "perfect ";
        }
        else if (s >= p-2 && s <= p+2) {
            cout << "almost perfect";
        }
        else {
            cout << "not perfect";
        }
        cout << "\n";
    }
}