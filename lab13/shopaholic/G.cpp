#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, p, d;
    cin >> n;

    if (n < 3) {
        cout << "0";
        return 0;
    }

    vector<int> doll;
    for (int i=0;i<n;i++) {
        cin >> d;
        doll.push_back(d);
    }

    sort(doll.begin(), doll.end());
    int start = n % 3;
    long long discount = 0;
    int numDone = 0;
    for (int i=start; i<n;i++) {
        if (numDone % 3 == 0) {
            discount += doll[i];
        }
        numDone++;
    }
    cout << discount;
}