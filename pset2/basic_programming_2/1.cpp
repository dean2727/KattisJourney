#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <vector>
using namespace std;

int main() {
    int N = 0, t = 0, i, j;
    cin >> N >> t;

    int A[N];
    int n;
    for (i=0;i<N;i++) {
        cin>>n;
        A[i]=n; 
    }

    if (t == 1) {
        vector<int> numLess7777;
        for(i=0;i<N;i++){
            //cout<<A[i]<<endl;
            //cut out some numbers for good runtime
            if (A[i]<=7777){
                numLess7777.push_back(A[i]);
            }
        }
        bool yes = false;
        for(i=0;i<numLess7777.size()-1;i++) {
            if(yes){
                break;
            }
            for(j=i+1;j<numLess7777.size();j++){
                //cout <<"i:"<<i<<"j:"<<j<<endl;
                if(numLess7777[i]+numLess7777[j]==7777&&numLess7777[i]!=numLess7777[j]){
                    yes = true;
                    break;
                }
            }
        }
        if(yes){
            cout << "Yes";
        }
        else{
            cout << "No";
        }
    }

    else if (t == 2) {
        set<int> s;
        for (i=0;i<N;i++){
            s.insert(A[i]);
        }
        if(s.size()==N){
            cout << "Unique";
        }
        else{
            cout << "Contains duplicate";
        }
    }

    else if (t == 3) {
        unordered_map<int, int> numFreq;
        for (int i = 0; i < N; i++) {
            numFreq[A[i]]++;
        }
        int x = N / 2;
        bool found = false;
        for (unordered_map<int, int>::iterator it = numFreq.begin(); it != numFreq.end(); it++) {
            if (it -> second > x) {
                cout << it -> first;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "-1";
        }
    }

    else if (t == 4) {
        sort(A, A + N);
        if (N % 2 != 0) {
            int midIdx = N / 2;
            cout << A[midIdx];
        }
        else {
            int mid1 = N / 2 - 1, mid2 = N / 2;
            cout << A[mid1] << " " << A[mid2];
        }
    }

    else {
        vector<int> v;
        for (int i = 0; i < N; i++) {
            if (A[i] >= 100 and A[i] <= 999) {
                //cout << A[i] << " ";
                v.push_back(A[i]);
            }
        }
        sort(v.begin(),v.end());
        for (i=0;i<v.size()-1;i++) {
            cout << v[i] << " ";
        }
        cout << v[v.size()-1];
    }
}