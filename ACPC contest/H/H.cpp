#include <iostream>
#include <map>
#include <vector>
#include <math.h>
using namespace std;

int n, k, p_int;
double p;
vector<int> weights;

/*
DP[a][b] = max # of donuts you can eat on day a with weight b
goal is to get DP[0][0]
base case:
1. = 0 if b + weights[a] > max weight k (if eating the donut on this day makes us too fat)
2. = 0 if a >= weight.size() (index out of bounds)
DP[a][b] = max {
    // eating donut a, going to day a+1 with b+weight[a] weight now
    1 + DP[a+1][b+weight[a]]
    // dont eat it, and lose p% of the weight
    DP[a+1][b-b*p]
}
*/
int dp(int a, int b) {
    //cout << a << ", " << b << endl;
    static map<pair<int,int>, int> seen;
    if (seen.count(make_pair(a, b))) {
        return seen[make_pair(a, b)];
    }

    if (a >= weights.size() || b > k) {
        return 0;
    }

    if (b + weights[a] > k) {
        return dp(a+1, b - floor(b * p));
    }

    int ret;
    ret = max(1 + dp(a+1, b + weights[a]), dp(a+1, b - floor(b * p)));
    seen[make_pair(a, b)] = ret;
    return ret;
}

int main() {
    // n = # of days the special lasts, k = max weight that can be obtained, p = % gained
    int i;
    cin >> n >> k >> p_int;
    p = p_int * .01;
    //cout << p << endl;
    weights.resize(n);
    int cal;
    for (i=0;i<n;i++) {
        cin >> cal;
        weights[i] = cal;
    }

    cout << dp(0, 0);
}