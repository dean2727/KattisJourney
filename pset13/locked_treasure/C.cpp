#include <iostream>
#include <map>
using namespace std;

// Returns value of Binomial Coefficient C(n, k)
// https://www.geeksforgeeks.org/binomial-coefficient-dp-9/
int binomialCoeff(int n, int k)
{
    // Base Cases
    if (k > n)
        return 0;
    if (k == 1 || k == n)
        return 1;
    
    static map<pair<int, int>, int> seen;
    if (seen.count(make_pair(n, k))) {
        return seen[make_pair(n, k)];
    }
 
    // Recur
    int ret = binomialCoeff(n - 1, k - 1) + binomialCoeff(n - 1, k);
    seen[make_pair(n, k)] = ret;
    return ret;
}

int main() {
    int t, n, m, k;
    cin >> t;

    while (t--) {
        cin >> n >> m;
        cout << binomialCoeff(n+1, m) << endl;
    }
}