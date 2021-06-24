#include <iostream>

using namespace std;

int main() {
    // get num mountains and mountain heights
    int N = 0, i;
    cin >> N;

    int heights[N];
    for (i = 0; i < N; i++) {
        int height;
        cin >> height;
        heights[i] = height;
    }

    // get smallest height mountain
    int smallestHeight = 1000000000;
    for (i = 0; i < N; i++) {
        if (heights[i] < smallestHeight) {
            smallestHeight = heights[i];
        }
    }

    
}