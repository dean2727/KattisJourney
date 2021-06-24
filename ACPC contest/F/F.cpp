#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    long long k, num;
    cin >> n >> k;
    vector<long long> nums;
    for (int i=0;i<n;i++) {
        cin >> num;
        nums.push_back(num);
    }

    long long div;

    vector<vector<long long> > numeratorOptions;
    vector<vector<long long> > denominatorOptions;
    for (int i=0;i<n;i++) {
        vector<long long> numerator;
        vector<long long> denom;
        for (int j=0;j<n;j++) {
            numerator.push_back(nums[j]);
            denom.push_back(nums[j]);
        }
        numeratorOptions.push_back(numerator);
        denominatorOptions.push_back(denom);
    }
    // add the option to just divide by 1
    vector<long long> denom;
    denom.push_back(1);
    denominatorOptions.push_back(denom);

    for (int i=0;i<numeratorOptions.size();i++) {
        for (int j=0;j<denominatorOptions.size();j++) {
            long long numer = numeratorOptions[i][0], deno = denominatorOptions[j][0];
            for (int k=1;k<numeratorOptions[i].size();k++) {
                numer *= numeratorOptions[i][k];
            }
            for (int l=1;l<denominatorOptions[j].size();l++) {
                deno *= denominatorOptions[j][l];
            }
            cout << "numer = " << numer << ". deno = " << deno << endl;
            if (numer / deno == k) {
                cout << "YES\n";
                cout << numeratorOptions[i].size() << " ";
                for (int k=0;k<numeratorOptions[i].size();k++) {
                    cout << numeratorOptions[i][k] << " ";
                }
                cout << "\n";
                if (denominatorOptions[j].size() == 1 && denominatorOptions[j][0] == 1) {
                    cout << "0";
                }
                else {
                    cout << denominatorOptions[j].size() << "\n";
                    for (int l=0;l<denominatorOptions[j].size();l++) {
                        cout << denominatorOptions[j][l] << " ";
                    }
                }
                return 0;
            }
        }
    }
    cout << "NO";
}