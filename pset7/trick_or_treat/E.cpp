#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;

#define loop(i, a, b) for(i = (a); i < (b); i++)
int i;
const double ERR = 1e-10;

// Because we are looking to minimize the time the last child arrives in some range
// we can use ternary search!

// We need an evaluation function, which will calculate the time needed for the last child to arrive, given x
double maxTime(double x, const vector<pair<double, double> >& houses) {
    double maximum = 0.0, curr;

    // loop through all houses, obtaining the max distance
    loop(i, 0, houses.size()) {
        double hx = houses[i].first, hy = houses[i].second;
        curr = pow(x - hx, 2) + pow(hy, 2);
        if (curr > maximum) maximum = curr;
    }

    return sqrt(maximum);
}

int main() {
    double x, y;
    int n;
    string line;

    scanf("%d", &n);
    while (n != 0) {
        double a = 1000000.0, b = -1000000.0;

        // get test case input
        vector<pair<double, double> > houses;
        loop(i, 0, n) {
            scanf("%lf %lf", &x, &y);
            houses.push_back(make_pair(x, y));

            // update a (left bound of search) or b (right bound of search)
            if (x < a) a = x;
            if (x > b) b = x;
        }

        // run ternary search, evaluating the function until a and b are sufficiently close
        double P, Q, fa, fP = 0.0, fQ = 0.0, prevDiff = 0.0;
        while (abs(b - a) > ERR) {        

            // form new points P and Q which are 1/3 passed a and 2/3 passed a, respectively
            P = a + (b - a) / 3;
            Q = b - (b - a) / 3;

            // evaluate function at all 4 points
            fP = maxTime(P, houses);
            fQ = maxTime(Q, houses);

            // if F(P) < F(Q), the min cant be between Q and b
            if (fP <= fQ) b = Q;

            // if F(Q) < F(P), the min cant be between a and P
            if(fQ < fP) a = P;
        }
        
        fa = maxTime(a, houses);
        printf("%.9lf %.9lf\n", a, fa);

        getline(cin, line);
        scanf("%d", &n);
    }
}