class Subsets:
    def get_subsets(self, nums):
        result = [[]]
        for num in nums:
            result += [curr + [num] for curr in result]
        return result

n = int(input("Enter number of elements: "))
nums = []

print("Enter elements:")
for i in range(n):
    nums.append(int(input()))

obj = Subsets()
print("Subsets are:")
print(obj.get_subsets(nums))
