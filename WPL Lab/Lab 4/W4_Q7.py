class StringManipulation:
    def get_String(self):
        self.s = input("Enter a string: ")

    def print_String(self):
        print("Uppercase string:", self.s.upper())

obj = StringManipulation()
obj.get_String()
obj.print_String()
