#include <iostream>
#include <queue>
#include <map>
#include <math.h>
using namespace std;
int main() {
    int N, B;
    cin >> N;
    string nl;
    while (N != -1) {
        cin >> B;
        priority_queue<pair<int, int> > boxsizes;
        map<int,int> numalloc;  // city info and number boxes to allocate (incr each time)

        int bboxesleft = B-N;
		//cout << bboxesleft << " boxes left\n";
        int a;
        while (N--){
            cin >> a;
            boxsizes.push(make_pair(a, a));
            numalloc.insert(make_pair(a, 1));
        }

        // Pull off top element of queue, recalculate average you get from adding one more box,
        // and stick back on the queue.
        pair<int,int> t;
        while (bboxesleft--) {
            t = boxsizes.top();
            //cout << "considering city " << t.second << " with " << t.first << endl;
			
			numalloc[t.second]++;
			//cout << t.second << " / " << numalloc[t.second] << endl;
            t.first = floor(t.second / numalloc[t.second]);
			if (t.first == 0) t.first = 1;
            //cout << "now " << t.first << endl;
            boxsizes.pop();
            boxsizes.push(t);
        }

		t = boxsizes.top();

		
		//cout << floor(t.second / (float)numalloc[t.second]) << " " << ceil(t.second / (float)numalloc[t.second]) << endl;
		//cout << t.second << "/" << numalloc[t.second] << endl;

		// if theres more boxes than we have people for, or if we have an even number of people going into boxes
		if (numalloc[t.second] > t.second || floor(t.second / (float)numalloc[t.second]) == ceil(t.second / (float)numalloc[t.second])) {
			cout << t.first << "\n";
		}
		// else, since we only want the max people in ONE box, add 1, since the integer division rounded down
		else {
			cout << t.first + 1 << "\n";
		}

        getline(cin, nl);
        cin >> N;
    }
    cin >> B;

    return 0;
}