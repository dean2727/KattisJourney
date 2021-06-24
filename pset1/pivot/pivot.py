n = int(input())
nums = input()

listNums = nums.split(' ')
numNums = len(listNums)

minCanditates = [False] * numNums
maxCandidates = [False] * numNums
minVal = 1000000000
maxVal = -1

# scan left to right, updating max value
for i in range(numNums):
    if int(listNums[i]) >= maxVal:
        minCanditates[i] = True
        maxVal = int(listNums[i])

# scan right to left, updating min value
for i in range(numNums - 1, -1, -1):
    if int(listNums[i]) < minVal:
        maxCandidates[i] = True
        minVal = int(listNums[i])

numPivots = 0
for i in range(numNums):
    if minCanditates[i] and maxCandidates[i]:
        numPivots += 1

print(numPivots)