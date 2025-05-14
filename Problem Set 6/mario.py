from cs50 import get_int

# Prompt user until valid input is given
while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

# Print the pyramid
for i in range(1, height + 1):
    spaces = height - i
    hashes = i
    print(" " * spaces + "#" * hashes)
