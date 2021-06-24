#include <iostream>
#include <vector>
using namespace std;

int main() {
    int T = 0;
    cin >> T;

    vector<int> csStudents;
    int numCs = 0, numEcon = 0, thisCs = 0, thisEcon = 0, numFunnyEvent = 0;
    long long totalCs = 0, totalEcon = 0;  // 200,000 max in each college, and 100,000 max iq -> long long
    double csAvg = 0.0, econAvg = 0.0, totalAvg = 0.0;
    string newLine;
    for (int i = 0; i < T; i++) {
        getline(cin, newLine);
        cin >> numCs >> numEcon;

        // obtain the average of the cs, econ, and total iqs
        for (int j = 0; j < numCs; j++) {
            cin >> thisCs;
            totalCs += thisCs;
            csStudents.push_back(thisCs);
        }
        csAvg = totalCs / (double)numCs;

        for (int j = 0; j < numEcon; j++) {
            cin >> thisEcon;
            totalEcon += thisEcon;
        }
        econAvg = totalEcon / (double)numEcon;

        totalAvg = (double)(totalCs + totalEcon) / (numCs + numEcon);

        // for every student in the cs vector
        for (int j = 0; j < numCs; j++) {
            // if removing this student causes the cs average to go up (x < csAvg), 
            // and if removing him causes the econ average to go up (x > econAvg), then funny event happens
            int iq = csStudents[j];
            if (iq < csAvg && econAvg < iq) {
                numFunnyEvent++;
            }
        }

        cout << numFunnyEvent << endl;

        totalCs = 0;
        totalEcon = 0;
        csAvg = 0.0;
        econAvg = 0.0;
        totalAvg = 0.0;
        numFunnyEvent = 0;
        csStudents.clear();
    }
}