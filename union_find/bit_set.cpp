#include <iostream>
using namespace std;

const int N = 20;

void listelements(int x) {
    cout << "Set contains: ";
    for (int i=0;i<N;i++) {
        if ((1 << i) & x) cout << i << " ";
    }
    cout << endl;
}

int main() {
    // set code (more efficient than bools, less efficient than all of it in an integer)
    int a, b, c;
    a = (1<<5) | (1<<7) | (1<<12);
    b = (1<<0) | (1<<5) | (1<<7) | (1<<10) | (1<<11);

    cout << "Set A: "; listelements(a);
    cout << "Set B: "; listelements(b);
    cout << "A UNION B: "; listelements(a|b);
    cout << "A INTERSECTION B: "; listelements(a&b);
    cout << "A XOR B: "; listelements(a^b);  // in 1 or the other
    
    // all 1s below N
    cout << "All elements: "; listelements((1<<N) - 1);
    // 32-bit -> higher bits should be 0
    cout << "NOT B: "; listelements((~b) & ((1<<N) - 1));

    bitset<15> c;
    c.set(4);  // set 5th lsb
    c.set(8);
    cout << "c: " << c << endl;
    c.flip(3); c.flip(4);
    cout << "c: " << c << endl;
}