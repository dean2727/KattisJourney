#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    // keep doubling printers until we can have enough for the statues
    // its better to double on this day then to do anything else if we dont have enough
    int days = 1, printers = 1;
    while (printers < n) {
        days++;
        printers *= 2;
    }
    cout << days;
}