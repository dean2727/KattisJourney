#include <iostream>
using namespace std;
int main() {
	int d;
	cin >> d;
	int days[d];

	long long shares = 0;
	int p;
	long long money = 100, invested = 0;
 
	for (int i=0;i<d;i++) {
		cin >> p;
		days[i] = p;
	}

	bool inv = false;
	for (int i=0;i<d-1;i++) {
		// if the price is increasing tomorrow, we want to buy (invest in shares), if we can afford any
		if (days[i+1] > days[i]) {
			if (inv == false) {
				shares = money / days[i];  // how many shares can our money buy?
				// remember, a cap of 100k shares
				if (shares > 100000) {
					shares = 100000;
				}
				invested = shares * days[i];
				money -= invested;
				inv = true;
			}
		}
		
		// if the price is decreasing tomorrow we want to sell our stocks (add stock value * num stocks to money)
		else if (days[i+1] < days[i]) {
			money += days[i] * shares;
			shares = 0;
			inv = false;
		}
	}

	cout << money + days[d-1] * shares;
 	return 0;
}