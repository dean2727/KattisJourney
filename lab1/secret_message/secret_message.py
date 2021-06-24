'''
(not done)
Jack and Jill developed a special encryption method, so they can enjoy
conversations without worrrying about eavesdroppers. Here is how: let 𝐿
be the length of the original message, and 𝑀 be the smallest square number
greater than or equal to 𝐿. Add (𝑀−𝐿) asterisks to the message, giving a
padded message with length 𝑀. Use the padded message to fill a table of
size 𝐾×𝐾, where 𝐾2=𝑀. Fill the table in row-major order (top to bottom row,
left to right column in each row). Rotate the table 90 degrees clockwise.
The encrypted message comes from reading the message in row-major order from
the rotated table, omitting any asterisks.

For example, given the original message ‘iloveyouJack’, the message length
is 𝐿=12. Thus the padded message is ‘iloveyouJack****’, with length 𝑀=16.
Below are the two tables before and after rotation.

input:
The first line of input is the number of original messages, 1≤𝑁≤100.
The following 𝑁 lines each have a message to encrypt. Each message contains
only characters a–z (lower and upper case), and has length 1≤𝐿≤10000.

output:
For each original message, output the secret message.
'''

from math import sqrt, floor

# Get number of messages
N = int(input())

# Get messages
msgs = []
for i in range(N):
    msg = input()
    msgs.append(msg)

for msg in msgs:
    L = len(msg)

    # Get smallest square number greater than or equal to L
    num = 0
    M = num ** 2
    lessThanL = True
    while lessThanL:
        if num ** 2 >= L:
            M = num ** 2
            lessThanL = False
        else:
            num += 1

    msg += '*' * (M - L)
    
    k = int(sqrt(M))
    
    msgChars = [char for char in msg]
    
    # Make k x k matrix from string
    rows = []
    for i in range(k):
        thisRow = []
        for j in range(i*k, i*k + k):
            thisRow.append(msgChars[j])
        rows.append(thisRow)

    msgMatrix = list(map(list, zip(*rows)))
    
    newMsg = ""
    for row in msgMatrix:
        for char in reversed(row):
            if char != '*':
                newMsg += char

    print(newMsg)