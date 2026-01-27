with open("input.txt", "r") as f1:
    content = f1.read()

reversed_content = content[::-1]

with open("output.txt", "w") as f2:
    f2.write(reversed_content)

print("File content reversed and saved.")
