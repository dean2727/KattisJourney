#include <iostream>
using namespace std;

int R,S,N,E;

void afterweek(int& M,int& P,int& L) {
    // get # mosq, then pupa, larva, then eggs
    int orig = M;
    M = P / S;
    P = L / R;
    L = orig * E;
}

int main() {
    int M,P,L;
    while (cin>>M) {
        cin>>P>>L>>E>>R>>S>>N;
        for (int i=0;i<N;i++) {
            afterweek(M,P,L);
        }
        cout << M << "\n";
    }
}