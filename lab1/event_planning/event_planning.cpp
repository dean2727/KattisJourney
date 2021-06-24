/*
As you didn’t show up to the yearly general meeting of the Nordic
Club of Pin Collectors, you were unanimously elected to organize
this years excursion to Pin City. You are free to choose from a number
of weekends this autumn, and have to find a suitable hotel to stay at,
preferably as cheap as possible.

You have some constraints: The total cost of the trip must be within
budget, of course. All participants must stay at the same hotel, to
avoid last years catastrophe, where some members got lost in the city,
never being seen again.

input:
The first line of input consists of four integers: 1≤𝑁≤200, the number of
participants, 1≤𝐵≤500000, the budget, 1≤𝐻≤18, the number of hotels to consider,
and 1≤𝑊≤13, the number of weeks you can choose between. Then follow two lines
for each of the 𝐻 hotels. The first gives 1≤𝑝≤10000, the price for one person 
staying the weekend at the hotel. The second contains 𝑊 integers, 0≤𝑎≤1000,
giving the number of available beds for each weekend at the hotel.

output:
Output the minimum cost of the stay for your group, or “stay home” if
nothing can be found within the budget.
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int N, B, H, W;
    cin >> N >> B >> H >> W;
    
    vector<int> prices;
    vector<int>  availBeds;
    
    for (int i = 0; i < H; i++) {
        int price;
        cin >> price;
        prices.push_back(price);
        for (int j = 0; j < W; j++) {
            int beds;
            cin >> beds;
            availBeds.push_back(beds);
        }
    }
    
    bool foundInBudget = false;
    int bestPrice = 1000000000;
    int thisPrice = 0;
    for (int i = 0; i < prices.size(); i++) {
        for (int j = i * W; j < i * W + W; j++) {
            if (availBeds.at(j) >= N) {
                thisPrice = N * prices.at(i);
                if (thisPrice < bestPrice && thisPrice <= B) {
                    bestPrice = thisPrice;
                    foundInBudget = true;
                }
            }
        }
    }
    if (!foundInBudget) {
        cout << "stay home";
    }
    else {
        cout << bestPrice;
    }

    return 0;
}
