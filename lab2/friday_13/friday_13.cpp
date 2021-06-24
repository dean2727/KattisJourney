#include <iostream>
#include <vector>
using namespace std;

int main() {
    int currDayInYear = 0, numFriday13 = 0;

    int T = 0;
    cin >> T;

    for (int i = 0; i < T; i++) {

        // get D (days in year) and M (months in year)
        int D = 0, M = 0;
        cin >> D >> M;
        

        // for each month
        int numDaysInMonth = 0;
        for (int j = 0; j < M; j++) {
            cin >> numDaysInMonth;

            // it is a friday the 13th if the month starts on a Sunday (% 7 = 0) and theres at least 13 days in the month
            if (currDayInYear % 7 == 0 && numDaysInMonth >= 13) {
                numFriday13++;
            }

            currDayInYear += numDaysInMonth;
        }

        cout << numFriday13 << endl;
        numFriday13 = 0;
        currDayInYear = 0;
    }
}