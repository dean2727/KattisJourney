#include <iostream>
using namespace std;

class Car {
public:
    Car(string name_, int catalogPrice_, int pickUpCost_, int driveCostPerKM_) {
        name = name_;
        catalogPrice = catalogPrice_;
        pickUpCost = pickUpCost_;
        driveCostPerKM_ = driveCostPerKM;
    }
private:
    string name;
    int catalogPrice;
    int pickUpCost;
    int driveCostPerKM;
    int KMDriven;
}

class EventList {

private:

}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int n, m;
        cin >> n >> m;

        int p, q, k;
        string N;
        vector<Car> cars;
        for (int i=0;i<n;i++) {
            cin >> N >> p >> q >> k;
            Car newCar(N, p, q, k);
            cars.push_back(newCar);
        }

        /* 
        consistent event log:
        - A spy will pick up a car before returning it.
        - A spy will always return a car they picked up.
        - A spy can use at most one car at a time.
        - Accidents can only happen when a spy is using a car.
        */

        int t, d, s;
        string S, C;
        char e;
        for (int i=0;i<m;i++) {
            cin >> t >> S >> e;
            // the name of the type of the car picked up is C
            if (e == 'p') {
                cin >> C;
            }
            // distance covered, d, in the last car picked up by spy S covered
            else if (e == 'r') {
                cin >> d;
            }
            // accident! s = severity percentage
            else {
                cin >> s;
            }
        }
    }
}