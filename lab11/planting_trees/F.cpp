#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(const int& a, const int& b) {
    return a > b;
}

int main() {
    int n, t;
    vector<int> days;
    cin >> n;
    for (int i=0;i<n;i++) {
        cin >> t;
        days.push_back(t);
    }
    sort(days.begin(),days.end(),cmp);

    //cout << days[0];
    int ans = days[0]+1;
    int d = 1;
    for (int i=1;i<n;i++) {
        d++;
        //cout << d << " " << days[i] << endl;
        //cout << d+days[i] << endl;
        if (d+days[i]>ans) ans = d+days[i];
    }
    cout << ans+1;
}