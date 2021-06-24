#include <iostream>
#include <cmath>
using namespace std;
int main() {
    long long edgedots;
    int iter;
    cin >> iter;

    edgedots = pow(2, iter) + 1;
    cout << edgedots * edgedots;

	return 0;
}
