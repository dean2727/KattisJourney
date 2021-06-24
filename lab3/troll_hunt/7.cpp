#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // input
    int b = 0, k = 0, g = 0;
    cin >> b >> k >> g;

    // take the floor of # knights / # needed per group
    // divide # bridges by this
    int numGroups = k / g;

    // output
    cout << ceil((double)(b - 1) / numGroups);
}