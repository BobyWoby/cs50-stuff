# TODO
import re
import math
def double(n):
    return 2 * int(n)
while True:
    try:
        num = input("Number: ")
        if int(num):
            str(num)
            break
    except:
        print("invalid number")
sums = list(map(double, num[len(num)-2::-2]))

start = int(num[0:2])

for i in range(len(sums)):
    if sums[i] > 9:
        sums[i] = sum(int(digit) for digit in str(sums[i]))

finalSum = sum(sums)
finalSum += sum(map(int, num[len(num)-1::-2]))
#print(finalSum)

if finalSum % 10 == 0:
    #do thing
    MC = [51, 52, 53, 54, 55]
    if len(num) == 15 and (start == 37 or start == 34):
        print("AMEX")
    elif (len(num) == 16) and (start in MC):
        print("MASTERCARD")
    elif (len(num) == 13 or len(num) == 16) and (int(str(start)[0]) == 4):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")

#print(start)
#print(num[len(num)-2::-2])
#print(sums)
#Luhn's algorithm