#include <iostream>
#include <string>
using namespace std;
int main() {
	string s;
	int p1 = 0, p2 = 0, p3 = 0;

	cin >> s;

	if (s[0]!=s[1]){
		p1 += 1;
		p2 += 1;
		p3 += 1;
	}
	if (s[1] == 'U') p2++;
	if (s[1] == 'D') p1++;

	for (int i=2;i<s.length();i++){
		if (s[i] == 'D') p1 += 2;
		if (s[i] == 'U') p2 += 2;
		if (s[i-1] != s[i]) p3 += 1;
	}

	cout << p1<<"\n"<<p2<<"\n"<<p3;
	return 0;
}