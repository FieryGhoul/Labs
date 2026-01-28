class StringReverser:
    def reverse_words(self, s):
        words = s.split()
        return " ".join(reversed(words))

s = input("Enter a string: ")
rev = StringReverser()
print("Reversed string:", rev.reverse_words(s))
