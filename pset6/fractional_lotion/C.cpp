#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#define endl '\n'

/*
1/X + 1/Y = 1/n
1/X = 1/n - 1/Y
1/X = (Y-n)/nY
X = ny/(Y-n)
X = n + n^2/(Y-n)

- n^2 % (Y-n) needs to be 0 for X to be a positive integer
- for Y, the minimum value can be n+1, since the denominator must be > 0.
the max value can be n^2+n
*/
int main() {
    string frac;
    int n;
    while (cin>>frac){
        n = stoi(frac.substr(2, frac.length()-2));
        int count = 0;

        // iterate from min y to max y. add to the count if the remainder is 0
        for (int y=n+1;y<=n*n+n;y++){
            if ((n*n) % (y-n) == 0) {
                count++;

                // if x = y, quit so that we dont count different orders
                if (n+(n*n)/(y-n) == y) break;
            }
        }

        cout << count << endl;
    }
}