#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

// for real problems, generating primes/prime factorization are steps along the way

const int MAXPRIME = 1000000;
vector<int> primes;
vector<bool> isprime;  // is element i prime?

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
            primes.push_back(i);
            for (int j = 2*i; j <= MAXPRIME; j += i) {
                isprime[j] = false;
            }
        }
    }
}

// may need this to get the prime factors of a number (loop up to sqrt(n))
void factorize(int x) {
    int i = 0;  // which prime im on
    while (primes[i] <= sqrt(x)) {
        if ((x % primes[i]) == 0) {
            cout << primes[i] << " ";
            x /= primes[i];
        }
        else {
            i++;
        }
    }

    // no prime factors, the number and 1 are its own factors
    if (x > 1) {
        cout << x << endl;
    }
    else {
        cout << endl;
    }
}

// in main, read in numbers and say if number is prime or not
int main() {
    generatePrimes();

    cout << "The first 20 primes are: \n";
    for (int i=0;i<20;i++) {
        cout << primes[i] << endl;
    }
    int x;
    while(1) {
        cin >> x;
        if (isprime[x]) {
            cout << "Prime!\n";
        }
        else {
            cout << "Nope, loser!\n";
        }
        cout << "Prime factors:\n";
        factorize(x);
    }
}