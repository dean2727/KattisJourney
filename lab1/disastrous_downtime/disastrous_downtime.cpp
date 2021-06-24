/*
You’re investigating what happened when one of your computer systems recently
broke down. So far you’ve concluded that the system was overloaded; it looks
like it couldn’t handle the hailstorm of incoming requests. Since the incident,
you have had ample opportunity to add more servers to your system, which would
make it capable of handling more concurrent requests. However, you’ve simply been
too lazy to do it—until now. Indeed, you shall add all the necessary servers very
soon!

To predict future requests to your system, you’ve reached out to the customers of
your service, asking them for details on how they will use it in the near future.
The response has been pretty impressive; your customers have sent you a list of
the exact timestamp of every request they will ever make!

You have produced a list of all the 𝑛 upcoming requests specified in milliseconds.
Whenever a request comes in, it will immediately be sent to one of your servers.
A request will take exactly 1000 milliseconds to process, and it must be processed
right away.

Each server can work on at most 𝑘 requests simultaneously. Given this limitation,
can you calculate the minimum number of servers needed to prevent another system
breakdown?

input:
The first line contains two integers 1≤𝑛≤100 000 and 1≤𝑘≤100 000, the number
of upcoming requests and the maximum number of requests per second that each
server can handle.

output:
Then follow 𝑛 lines with one integer 0≤𝑡𝑖≤100 000 each, specifying that the 𝑖th
request will happen 𝑡𝑖 milliseconds from the exact moment you notified your
customers. The timestamps are sorted in chronological order. It is possible that
several requests come in at the same time.
*/

#include <iostream>
#include <cmath>
#include <queue>
using namespace std;


int main() {
    int n, processTime = 1000, k;
    queue<int> times;
    cin >> n >> k;

    int prevTime;
    cin >> prevTime;
    times.push(prevTime);
    int thisTime, maxNumServers = 1, timeDifference = 0;

    // get timestamps from user
    for (int i = 1; i < n; i++) {
        cin >> thisTime;

        // first check if the time difference exceeds 1000, and if so, empty the queue
        timeDifference += thisTime - prevTime;
        if (timeDifference >= 1000) {
            while (!times.empty()) {
                times.pop();
            }
            
            timeDifference = timeDifference - 1000;
            //cout << "time difference: " << timeDifference << endl;
        }

        //cout << "pushing " << thisTime << endl;
        times.push(thisTime);

        // if we are seeing a max number of jobs in this batch of 1000 milliseconds, update max 
        if (times.size() > maxNumServers) {
            maxNumServers++;
        }

        prevTime = thisTime;
    }

    // print min number of servers needed
    cout << ceil((double)maxNumServers / k);
}