from cs50 import get_float

def main():
    # Prompt user for valid input
    while True:
        try:
            dollars = get_float("Change owed: ")
            if dollars >= 0:
                break
        except ValueError:
            pass

    # Convert dollars to cents and round to avoid floating point imprecision
    cents = round(dollars * 100)

    # Count coins
    coins = 0
    for coin in [25, 10, 5, 1]:
        coins += cents // coin
        cents %= coin

    print(coins)

if __name__ == "__main__":
    main()
