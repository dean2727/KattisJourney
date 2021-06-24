#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

int main() {
    int S,C,K;
    cin >> S >> C >> K;

    vector<int> socks;
    int sock;
    for (int i=0;i<S;i++) {
        cin >> sock;
        socks.push_back(sock);
    }

    sort(socks.begin(), socks.end());

    int tot = 1, numSocks = 1;
    int colorDifference = 0;
    for (int i=1;i<S;i++) {
        colorDifference += abs(socks[i] - socks[i-1]);
        numSocks++;
        if (colorDifference > K) {
            tot++;
            colorDifference = 0;
            numSocks = 1;
        }
        else if (numSocks > C) {
            tot++;
            numSocks = 1;
            colorDifference = 0;
        }
    }

    cout << tot;
}