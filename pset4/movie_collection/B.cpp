#include <iostream>
#include <cstring>
using namespace std;

int mNums[100010];
int movies[200010];

int LSOne(int x) {
    return x & (-x);
}

int rsq(int pos) {
    int sum = 0;
    while (pos > 0) {
        sum += movies[pos];
        pos -= LSOne(pos);
    }
    return sum;
}

void incr(int i, int elem, int n) {
    while (i <= n) {
        movies[i] += elem;
        i += LSOne(i);
    }
    return;
}

int main()
{
    int T, i, m, r, movie, n;

    cin >> T;
    while (T--) {
        memset(movies, 0, sizeof(movies));
        memset(mNums, 0, sizeof(mNums));

        cin >> m >> r;
        n = m + r;

        for (i = r + 1; i <= n; i++) {
            incr(i, 1, n);
            mNums[i - r] = i;
        }

        int minPos = r;
        for (i = 0; i < r; i++) {
            cin >> movie;

            cout << rsq(mNums[movie] - 1) << " ";
            
            // remove the movie from its position, hence decrementing along the line
            incr(mNums[movie], -1, n);

            // new position of removed movie is the original min position
            mNums[movie] = minPos--;

            // now increment by 1 with the new movie position
            incr(mNums[movie], 1, n);
        }
        cout << "\n";
    }
    return 0;
}

