#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    // input: N and t
    int N = 0, t = 0;
    cin >> N >> t;

    // make array of N integers
    int A[N];

    // get N numbers from input
    int num = 0;
    for (int i = 0; i < N; i++) {
        cin >> num;
        A[i] = num;
    }

    // if t is 1, print 7
    if (t == 1) {
        cout << "7";
    }

    // if t is 2
    else if (t == 2) {

        // if A[0] > A[1], print "Bigger"
        if (A[0] > A[1]) {
            cout << "Bigger";
        }

        // if A[0] == A[1], print "Equal"
        else if (A[0] == A[1]) {
            cout << "Equal";
        }

        // else, print "Smaller"
        else {
            cout << "Smaller";
        }
    }
    
    // if t is 3, print the median of A[0], A[1], and A[2]
    else if (t == 3) {
        // low, middle, high or high, middle, low -> A[1] is middle number
        if ((A[0] < A[1] && A[1] < A[2]) || (A[2] < A[1] && A[1] < A[0])) {
            cout << A[1];
        }
        // middle, high, low or middle, low, high -> A[0] is median
        else if ((A[1] < A[0] && A[0] < A[2]) || (A[2] < A[0] && A[0] < A[1])) {
            cout << A[0];
        }
        // high, low, middle or low, high, middle -> A[2] is median
        else if ((A[0] < A[2] && A[2] < A[1]) || (A[1] < A[2] && A[2] < A[0])) {
            cout << A[2];
        }
        // low/middle, high, low/middle -> take highest low
        else if ((A[0] < A[1] && A[1] > A[2]) && A[0] != A[2]) {
            if (A[0] > A[2]) {
                cout << A[0];
            }
            else {
                cout << A[2];
            }
        }
        // high/middle, low, high/middle -> take lowest high
        else if ((A[0] > A[1] && A[1] < A[2]) && A[0] != A[2]) {
            if (A[0] < A[2]) {
                cout << A[0];
            }
            else {
                cout << A[2];
            }
        }
        // same, same, different or different, same, same -> A[1] is median
        else if ((A[0] == A[1] && A[1] != A[2]) || (A[1] == A[2] && A[0] != A[1])) {
            cout << A[1];
        }
        // same, different, same -> A[0]/A[2] is median
        else if (A[0] == A[2] && A[0] != A[1]) {
            cout << A[0];
        }
        // A[0] = A[1] = A[2]
        else {
            cout << A[1];
        }
    }

    // if t is 4, print the sum of all integers in A
    else if (t == 4) {
        long long total = 0;
        for (int i = 0; i < N; i++) {
            total += A[i];
        }
        cout << total;
    }

    // if t is 5, print the sum of all even integers in A
    else if (t == 5) {
        long long total = 0;
        for (int i = 0; i < N; i++) {
            if (A[i] % 2 == 0) {
                total += A[i];
            }
        }
        cout << total;
    }

    // if t is 6
    else if (t == 6) {

        // apply modulo 26 to each integer in A and build string from these ints
        string sequence = "";
        for (int i = 0; i < N; i++) {
            sequence += A[i] % 26 + 'a';
        }

        // print the sequence of characters as a string
        cout << sequence;
    }

    // else, t is 7
    else {

        // Start from index 𝑖=0;
        int i = 0;

        set<int> history;
        //history.insert(i);

        while (true) {
            // Jump to index 𝑖=𝐴[𝑖];
            i = A[i];

            // If the current index 𝑖 is outside the valid bound of [0..𝑁-1], print “Out” and stop;
            if (i < 0 || i > N - 1) {
                cout << "Out";
                break;
            }

            // Else if the current index 𝑖 is index 𝑁-1, print “Done” and stop;
            else if (i == N - 1) {
                cout << "Done";
                break;
            }

            // If set already has i, theres an infinite loop, print “Cyclic” and stop
            if (history.count(i) == 1) {
                cout << "Cyclic";
                break;
            }
            
            // Otherwise, repeat step b;
            else {
                history.insert(i);
            }
        }
    }
}