#include <iostream>
#include <math.h>
#include <set>
#include <vector>
using namespace std;

const int MAXPRIME = 32000;
set<int> primes;
vector<bool> isprime;  // is element i prime?

#define trav(a, x) for(auto& a : x)

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
            primes.insert(i);
            for (int j = 2*i; j <= MAXPRIME; j += i) {
                isprime[j] = false;
            }
        }
    }
}

int main() {
    int n, x, i;
    cin >> n;
    generatePrimes();
    for (i=0;i<n;i++) {
        cin >> x;
        cout << x << " has ";
        set<pair<int,int> > seen;
        set<int>::iterator it;
        int numRep = 0;
        trav(it, primes) {
            int first = it;
            if (primes.count(x - first) && !seen.count(make_pair(x-first, first))) {
                numRep++;
                seen.insert(make_pair(it, x-first));
            }   
        }
        cout << numRep << " representation(s)\n";
        set<pair<int,int> >::iterator it2;
        trav(it2, seen) {
            cout << it2.first << "+" << it2.second << "\n";
        }
        cout << endl;
    }
}