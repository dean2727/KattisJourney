// C++ program to demonstrate working of
// extended Euclidean Algorithm
#include <iostream>
using namespace std;

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

// Driver Code
int main()
{
    int a, b, x, y;
    cin >> a >> b;
	int g = extendedEuclids(a, b, &x, &y);
	cout << "GCD(" << a << ", " << b
		<< ") = " << g << endl;
	return 0;
}

