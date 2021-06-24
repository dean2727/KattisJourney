#include <iostream>
#include <vector>
#include <set>
#include <math.h>
using namespace std;

const int MAXPRIME = 10000;
vector<bool> isprime;

// sieve of Erastothenes method to generate primes up to MAXPRIME
void generatePrimes() {
    isprime.resize(MAXPRIME+1, true);
    isprime[0] = false;
    isprime[1] = false;

    // Repeat:
    // Pick next prime number (on first iteration, this will be 2, then 3, then 5)
    // Mark all multiples of that number as not prime (increment by that amount, marking not prime)
    for (int i = 2; i <= MAXPRIME; i++) {
        if (isprime[i]) {
            for (int j = 2*i; j <= MAXPRIME; j += i) {
                isprime[j] = false;
            }
        }
    }
}

int digitSumSquares(int num) {
    string n = to_string(num);
    int ret = 0;
    for (int i = 0; i < n.length(); i++) {
        ret += pow((int(n.at(i))-48), 2);
    }
    return ret;
}

int main() {
    int P, K, m;
    cin >> P;
    generatePrimes();

    while (P--) {
        cin >> K >> m;
        // must be prime first of all
        if (!isprime[m]) {
            cout << K << " " << m << " NO\n";
        }
        // next, iteratively take the sum of squared digits until 1 or not
        else {
            set<int> seenNums;
            seenNums.insert(m);
            bool found = true;
            int ss = digitSumSquares(m);
            while (ss != 1) {
                seenNums.insert(ss);
                ss = digitSumSquares(ss);
                if (seenNums.count(ss)) {
                    cout << K << " " << m << " NO\n";
                    found = false;
                    break;
                }
            }
            if (found) {
                cout << K << " " << m << " YES\n";
            }
        }
    }
}