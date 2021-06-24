bigPrime = 1000000007

line1 = input().split(' ')
line2 = input().split(' ')
N = int(line1[0])
T = int(line1[1])
A = int(line2[0])
B = int(line2[1])
C = int(line2[2])
t0 = int(line2[3])

# We can just simply get the times for a cycle, which is of length C because by nature of mod we'll
# eventually encounter a time we've seen before
cycle = set()
thisTime = (A * t0 + B) % C + 1
while (thisTime not in cycle):
    #print(thisTime)
    cycle.add(thisTime)
    thisTime = (A * thisTime + B) % C + 1

cycle = sorted(cycle)
repeatedTimes = int(T / len(cycle))
print(repeatedTimes)

totTime = 0
penalty = 0
totSolved = 0
timeSinceStart = 0
cycleElement = 0
for e in cycle:
    # take all T / len(cycle) times for this cycle element
    for i in range(repeatedTimes):
         # do we have enough time to solve this problem?
        if totTime + e < T:
            totTime += e
            totSolved += 1
        else:
            print(str(totSolved), str(penalty % bigPrime))
            exit(1)

        # now add the time taken for this problem to time since start, add to penalty
        timeSinceStart += e
        penalty += timeSinceStart
        #print(penalty)

        # if index is at the end, we've solved all the problems, so break
        if totSolved > N:
            print(str(totSolved), str(penalty % bigPrime))
            exit(1)
