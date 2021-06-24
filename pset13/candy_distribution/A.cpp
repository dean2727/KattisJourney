#include <iostream>
using namespace std;

// Euclids algorithm for GCD
long long GCD(long long a, long long b) {
    if (b == 0) return a;
    return GCD(b, a % b);
}

// Function for extended Euclidean Algorithm
// finds a and b for ax + by = d = gcd(a, b) (assuming a > b)
int extendedEuclids(int a, int b, int *x, int *y) {
	// Base Case (cant divide by 0)
	if (b == 0) {
		*x = 1;
		*y = 0;
		return a;
	}

	int x1, y1; // To store results of recursive call
    int gcd = extendedEuclids(b, a%b, &x1, &y1);

	// Update x and y using results of
	// recursive call
	*x = y1;
	*y = x1 - (a/b) * y1;

	return gcd;
}

// C * numBags = (K * X) + 1
// --> C * numBags - (K * X) = 1
// --> -(K * X) + C * numBags = 1
// --> ax + by = 1, where a = -K and b = C
// numBags = ((K * X) + 1) / C  <--- want this to divide evenly
int main() {
    int t;
    long K, C;
    cin >> t;
    while (t--) {
        cin >> K >> C;
        int x, y;
        int d = extendedEuclids(-K, C, &x, &y);
        if (abs(d) != 1) {
            cout << "IMPOSSIBLE" << endl;
        }
        else {
            cout << y << endl;
        }
    }
}