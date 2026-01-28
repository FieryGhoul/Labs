import random

def smallest_element(arr):
    if len(arr) == 1:
        return arr[0]

    pivot = random.choice(arr)
    lows = [x for x in arr if x < pivot]
    pivots = [x for x in arr if x == pivot]

    if lows:
        return smallest_element(lows)
    else:
        return pivots[0]

n = int(input("Enter number of elements: "))
arr = list(map(int, input("Enter elements: ").split()))

print("Smallest element:", smallest_element(arr))
