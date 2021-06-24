#include <iostream>
using namespace std;
int main() {
    int n, h, v;
    int p1, p2, p3, p4;
    cin >> n>>h>>v;

    p1 = h * v * 4;
    p2 = h * (n-v) * 4;
    p3 = (n-h) * v * 4;
    p4 = (n-h) * (n-v) * 4;
    
    int m1 = max(p1, p2);
    int m2 = max(p3, p4);

    cout << max(m1, m2);

	return 0;
}