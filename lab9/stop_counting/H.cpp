#include <iostream>
#include <iomanip>
using namespace std;
const int N = 1e6 + 10 ;
double avgs[N][2];
double nums[N];

int main() {
	int n; 
	cin >> n;

	for(int i = 1; i <= n; i++)
	    cin >> nums[i];

	for(int i = 1; i <= n; i++) {
        avgs[i][0] = avgs[i - 1][0] + nums[i];
        avgs[n - i + 1][1] = avgs[n - i + 2][1] + nums[n - i + 1] ;
    }

	for(int i = 1; i <= n; i++) {
        avgs[i][0] = avgs[i][0] / i;
        avgs[n - i + 1][1] = avgs[n - i + 1][1] / i ;
    }

    double ans = 0.0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, max(avgs[i][0], avgs[n - i + 1][1]));
    }

    cout << fixed << setprecision(9) << ans;
	return 0 ;
}