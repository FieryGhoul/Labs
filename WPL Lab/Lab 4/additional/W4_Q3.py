r1 = int(input("Enter number of rows of matrix A: "))
c1 = int(input("Enter number of columns of matrix A: "))

A = []
print("Enter matrix A:")
for i in range(r1):
    A.append(list(map(int, input().split())))

r2 = int(input("Enter number of rows of matrix B: "))
c2 = int(input("Enter number of columns of matrix B: "))

B = []
print("Enter matrix B:")
for i in range(r2):
    B.append(list(map(int, input().split())))

if c1 != r2:
    print("Matrix multiplication not possible")
else:
    result = [[0 for _ in range(c2)] for _ in range(r1)]

    for i in range(r1):
        for j in range(c2):
            for k in range(c1):
                result[i][j] += A[i][k] * B[k][j]

    print("Resultant Matrix:")
    for row in result:
        print(row)
