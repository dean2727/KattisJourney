#include <iostream>
#include <map>
#include <vector>
using namespace std;

int n, m;
vector<int> cals;
vector<int> courses;

/*
DP[a][b] = max # of calories you can get from course a at calorie level b
goal is to get DP[0][0]
base case: = 0 if a >= # of courses
DP[a][b] = max {
    // eating course a, going to course a+1 with b+1 calories leftover + min of calroies available
    in course a and calorie level im at
    DP[a+1][b+1]+min(cal[a], clevel[b]),
    // skip this round, and take previous calorie level (cant go below 0 in cals)
    DP[a+1][max(0, b-1)]
    // skip 2 rounds, so calories is reset to initial
    DP[a+2][0]
}
*/
int dp(int a, int b) {
    if (a >= n) {
        return 0;
    }

    static map<pair<int,int>, int> seen;
    if (seen.count(make_pair(a, b))) {
        return seen[make_pair(a, b)];
    }

    int ret, max1;
    max1 = max(dp(a+1, max(0, b-1)), dp(a+2, 0));
    ret = max(max1, min(courses[a], cals[b]) + dp(a+1, b+1));

    seen[make_pair(a, b)] = ret;
    return ret;
}


int main() {
    int i;
    cin >> n >> m;

    courses.resize(n);
    int co;
    for (i=0;i<n;i++) {
        cin >> co;
        courses[i] = co;
    }

    // calculate the calorie levels
    cals.resize(n);
    cals[0] = m;
    for (i=1;i<n;i++) {
        cals[i] = cals[i-1] * 2/3;
    }

    cout << dp(0, 0);
}