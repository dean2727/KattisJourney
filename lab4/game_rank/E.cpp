#include <iostream>
#include <string>
using namespace std;

int main() {
	string history;
	cin >> history;
	int rank = 25, numStars = 0, numInRow = 0, numNeeded = 2;
	bool legend = false;

	for (int i=0;i<history.length();i++) {
		char h = history.at(i);

		if (!legend) {
			if (h == 'W') {
				numInRow++;
				numStars++;
				// If before the game the player was on rank 6-25, and this was the
				// third or more consecutive win, she gains an additional bonus star
				// for that win
				if (numInRow >= 3 && rank >= 6 && rank <= 25) {
					numStars++;
				}

				if (rank > 20) {
					numNeeded = 2;
				}
				else if (rank >= 16 && rank <= 20) {
					numNeeded = 3;
				}
				else if (rank >= 11 && rank <= 15) {
					numNeeded = 4;
				}
				else {
					numNeeded = 5;
				}

				if (numStars > numNeeded) {
					rank--;
					numStars -= numNeeded;
				}

				// legend rank, no need to keep iterating
				if (rank == 0) {
					legend = true;
				}
			}

			// loss
			else {
				numInRow = 0;
				if (rank >= 1 && rank <= 20) {
					numStars--;
					// If a player has zero stars on a rank and loses a star,
					//she will lose a rank and have all stars minus one on the rank below
					if (numStars == -1) {
						
						// one cannot drop below 20
						if (rank == 20) {
							numStars = 0;
							continue;
						}

						rank++;
						if (rank >= 21) {
							numStars = 1;
						}
						else if (rank >= 16 && rank <= 20) {
							numStars = 2;
						}
						else if (rank >= 11 && rank <= 15) {
							numStars = 3;
						}
						else {
							numStars = 4;
						}
					}
				}
			}
		}
	}
	if (legend) cout << "Legend";
	else cout << rank;
	return 0;
}
