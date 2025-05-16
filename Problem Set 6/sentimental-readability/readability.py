from cs50 import get_string
import re

def main():
    # Prompt user for input
    text = get_string("Text: ")

    # Count letters (alphabetic characters)
    letters = sum(1 for c in text if c.isalpha())

    # Count words (split by whitespace)
    words = len(text.split())

    # Count sentences (., !, ?)
    sentences = sum(1 for c in text if c in ['.', '!', '?'])

    # Coleman-Liau index calculation
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    grade = round(index)

    # Output result
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")

if __name__ == "__main__":
    main()
