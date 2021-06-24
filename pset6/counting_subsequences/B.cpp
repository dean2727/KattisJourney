#include <iostream>
#include <string>
#include <map>
using namespace std;

typedef long long ll;
typedef map<ll, int> mlli;
const int K = 47;

int main() {
    string line;
    int T, N, num;
    cin >> T;

    while (T--){
        getline(cin, line);
        cin >> N;
        int nums[N];
        int i = 0, NN = N;
        while (N--){
            cin >> num;
            nums[i] = num;
            i++;
        }

        // store previous occurences of prefix sum in map
        mlli occurences;
        occurences[0] = 1; // the empty technically has occured before
        ll ans = 0, sumToHere = 0, complement;

        for (int i=0;i<NN;i++){
            
            // update current sum
            sumToHere += nums[i];
            //cout << "sum to here: " <<  sumToHere << endl;

            // what prefix subarray do we need to remove?
            complement = sumToHere - K;

            // have we ever seen a prefix subarray that summed to this?
            if (occurences.count(complement)){
                ans += occurences[complement];
            }

            // update that we have seen the preix sum now
            occurences[sumToHere]++;
        }

        cout << ans << endl;
    }
}