class TwoSum:
    def find_indices(self, numbers, target):
        for i in range(len(numbers)):
            for j in range(i + 1, len(numbers)):
                if numbers[i] + numbers[j] == target:
                    return i, j
        return None

n = int(input("Enter number of elements: "))
numbers = []

print("Enter elements:")
for i in range(n):
    numbers.append(int(input()))

target = int(input("Enter target sum: "))

obj = TwoSum()
result = obj.find_indices(numbers, target)
print("Indices:", result)
