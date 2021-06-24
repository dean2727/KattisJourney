string = input()

digits = [0] * 3

ranges = [range(i + 1, 3) for i in range(3)]

swaps = 0
for digit in map(int, string):
    #print("This digit is", digit)

    # if the digit is 0, no
    for i in ranges[digit]:
        #print(digits[i])
        swaps += digits[i]

    digits[digit] += 1
    #print("Digits[" + str(digit) + "] =", digits[digit])

print(swaps)