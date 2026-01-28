class ParenthesesValidator:
    def is_valid(self, s):
        stack = []
        pairs = {')': '(', '}': '{', ']': '['}

        for char in s:
            if char in pairs.values():
                stack.append(char)
            elif char in pairs:
                if not stack or stack.pop() != pairs[char]:
                    return False
        return not stack

s = input("Enter the string of parentheses: ")
validator = ParenthesesValidator()

if validator.is_valid(s):
    print("Valid string")
else:
    print("Invalid string")
