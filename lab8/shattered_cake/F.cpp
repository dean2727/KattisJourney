#include <iostream>
using namespace std;

int main() {
    int W, N, w, l, totalArea = 0;
    cin >> W;
    cin >> N;
    while (N--) {
        cin >> w >> l;
        totalArea += w * l;
    }
    cout << totalArea / W;
}