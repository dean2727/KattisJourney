T = int(input())

d = {
    'a':'z',
    'b':'y',
    'c':'x',
    'd':'w',
    'e':'v',
    'f':'u',
    'g':'t',
    'h':'s',
    'i':'r',
    'j':'q',
    'k':'p',
    'l':'o',
    'm':'n',
    'n':'m',
    'o':'l',
    'p':'k',
    'q':'j',
    'r':'i',
    's':'h',
    't':'g',
    'u':'f',
    'v':'e',
    'w':'d',
    'x':'c',
    'y':'b',
    'z':'a',
}
seenValues = []

for i in range(T):
    n = int(input())

    nameIdxAndNames = {}
    classes = []
    for j in range(n):
        line = input()

        parts = line.split(' ')
        name = parts[0][:-1]
        nameIdxAndNames[j] = name
        personClass = parts[1].split('-')
        classes.append(personClass)

    # for each of the 3 classes at the highest level, get the minumum # of levels
    minUpper = 11
    minMiddle = 11
    minLower = 11
    for personClass in classes:
        if personClass[-1] == "upper" and len(personClass) < minUpper:
            minUpper = len(personClass)
        elif personClass[-1] == "middle" and len(personClass) < minMiddle:
            minMiddle = len(personClass)
        elif personClass[-1] == "lower" and len(personClass) < minLower:
            minLower = len(personClass)

    # only consider the minimum # of levels, assign integer values to classes, highest value gets output first
    valueAndNameIdx = {}
    j = 0
    #print("min up:", minUpper,"min mid:", minMiddle,"min low:", minLower)
    for personClass in classes:
        #print("j:", j)
        
        highestLvl = personClass[-1]
        #print("person class length =", len(personClass), "highest lvl:", highestLvl)
        if highestLvl == "upper":
            classValue = 500
            for k in range(minUpper):
                #print(personClass[k * -1 - 1])         
                if personClass[k * -1 - 1] == "upper":
                    #print("upper")
                    classValue += 3 * abs(k * -1 - 1)
                elif personClass[k * -1 -1] == "middle":
                    classValue += 2 * abs(k * -1 - 1)
                    #print("middle")
                else:
                    classValue += 1 * abs(k * -1 - 1)
                    #print("lower")
        
        elif highestLvl == "middle":
            classValue = 200
            for k in range(minMiddle):
                #print("k:",k)
                #print(personClass[k * -1 - 1])         
                if personClass[k * -1 - 1] == "upper":
                    classValue += 3 * abs(k * -1 - 1)
                elif personClass[k * -1 - 1] == "middle":
                    classValue += 2 * abs(k * -1 - 1)
                else:
                    classValue += 1 * abs(k * -1 - 1)

        else:
            classValue = 10
            for k in range(minLower):
                #print(personClass[k * -1 - 1])         
                if personClass[k * -1 - 1] == "upper":
                    classValue += 3 * abs(k * -1 - 1)
                elif personClass[k * -1 - 1] == "middle":
                    classValue += 2 * abs(k * -1 - 1)
                else:
                    classValue += 1 * abs(k * -1 - 1)

        #print("class:", j, ". value:", classValue)

        #print("class value:", classValue, "for name:", nameIdxAndNames[j])
        print(str(classValue) + d[nameIdxAndNames[j][0]]+ nameIdxAndNames[j])
        if classValue in seenValues:
            valueAndNameIdx[str(classValue) + d[nameIdxAndNames[j][0]] + nameIdxAndNames[j]] = j
        else:    
            valueAndNameIdx[str(classValue) + nameIdxAndNames[j]] = j
        j += 1
        seenValues.append(classValue)
    
    # sort values in dictionary
    sortedValueAndNameIdx = sorted(valueAndNameIdx.items(), key=lambda item: item[0])
    for pair in reversed(sortedValueAndNameIdx):            
        print(str(nameIdxAndNames[pair[1]]))

    print("==============================")