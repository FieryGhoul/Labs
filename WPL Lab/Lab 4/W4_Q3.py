sentence = input("Enter a sentence: ")
words = sentence.split()
words.sort()

print("Words in alphabetical order:")
for word in words:
    print(word)
