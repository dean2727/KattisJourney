#include <iostream>
using namespace std;

int main() {
    int T,n,i,g,s,m,x,r,a,b,p,t,i2;
    cin >> T;
    while (T--) {
        // number of locations in town
        cin >> n;
        // starting location
        cin >> i;
        // number of people in the group
        cin >> g;
        // number of time steps we have to get safety (medical facility)
        cin >> s;

        // number of medical facilities
        cin >> m;
        // locations (x-coordinates) of the medical facilities
        for (i2=0;i2<m;i2++) {
            cin >> x;
        }

        // number of roads in the town
        cin >> r;
        for (i2=0;i2<r;i2++) {
            // road from a to b
            cin >> a >> b;
            // p people can enter it at every time step
            cin >> p;
            // takes t timesteps to traverse
            cin >> t;
        }
    }
}