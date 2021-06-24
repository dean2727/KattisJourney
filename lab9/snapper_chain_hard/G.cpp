#include <iostream>
#include <math.h>
using namespace std;

int main() {
    int T, N, K;

    cin >> T;
    for (int i=1;i<=T;i++) {
        cin >> N >> K;

        cout << "Case #" << i << ": ";
        if (N == 1) {
            if (K % 2 == 0) cout << "OFF\n";
            else cout << "ON\n";
        }
        else {
            // firstly, we must have 2^N-1 snaps  
            if (K < pow(2, N)-1) cout << "OFF\n";
            else {                
                if (K % (int)(pow(2, N)) == (int)(pow(2, N))-1) cout << "ON\n";
                else cout << "OFF\n";
            }
        }
    }
}