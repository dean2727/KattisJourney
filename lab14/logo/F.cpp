#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

#define pi 3.14159265

int main() {
    int t, numc, i;
    cin >> t;
    
    while(t--){
        cin >> numc;
        string cmd;
        int deg;
        int angle = 0;
        vector<double> vcos;
        vector<double> vsin;
        for (i=0;i<numc;i++) {
            cin >> cmd >> deg;
            if (cmd == "lt") {
                angle += deg;
            }
            else if (cmd == "rt") {
                angle -= deg;
            }
            else if (cmd == "fd") {
                vcos.push_back(deg * cos(angle * pi / 180));
                vsin.push_back(deg * sin(angle * pi / 180));
            }
            else {
                // backwards -> add 180 degrees to the angle
                vcos.push_back(deg * cos((angle+180) * pi / 180));
                vsin.push_back(deg * sin((angle+180) * pi / 180));
            }
        }

        // vector addition
        double finalcos = 0.0, finalsin = 0.0;
        for (i=0;i<vcos.size();i++) {
            finalcos += vcos[i];
            finalsin += vsin[i];
        }

        cout << int(round(sqrt(finalcos*finalcos + finalsin*finalsin))) << "\n";
    }
}