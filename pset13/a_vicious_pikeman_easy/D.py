bigPrime = 1000000007

line1 = input().split(' ')
line2 = input().split(' ')
N = int(line1[0])
T = int(line1[1])
A = int(line2[0])
B = int(line2[1])
C = int(line2[2])
t0 = int(line2[3])

times = []
times.append(t0)

for i in range(1, N):
    thisTime = (A * times[i-1] + B) % C + 1
    times.append(thisTime)

# sort times so that we are finishing the easy-to-solve problems first (minimizing our penalty)
times = sorted(times)

totTime = 0
penalty = 0
totSolved = 0
timeSinceStart = 0
i = 0
while totTime < T:
    # do we have enough time to solve this problem?
    if totTime + times[i] < T:
        totTime += times[i]
        totSolved += 1
    else:
        break

    # now add the time taken for this problem to time since start, add to penalty
    timeSinceStart += times[i]
    penalty += timeSinceStart

    # if index is at the end, we've solved all the problems, so break
    i += 1
    if i >= N:
        break

print(str(totSolved), str(penalty % bigPrime))