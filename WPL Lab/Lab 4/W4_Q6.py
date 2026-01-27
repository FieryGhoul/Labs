class Power:
    def pow(self, x, n):
        if n == 0:
            return 1
        elif n < 0:
            return 1 / self.pow(x, -n)
        else:
            return x * self.pow(x, n - 1)

x = float(input("Enter value of x: "))
n = int(input("Enter value of n: "))

obj = Power()
print("Result:", obj.pow(x, n))
