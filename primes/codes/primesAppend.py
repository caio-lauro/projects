import gc, sys

primes: list[int] = []
size: int = 0
capacity: int = 1

def main(argc: int, argv: list[str]) -> int:
    if argc > 2:
        print("Usage: python3 primesAppend.py or python3 primesAppend.py STOP\n")
        return 1

    global primes, size, capacity

    primes = [2]
    size += 1

    if argc == 1:
        print("Will find and print numbers until the stopping point.\
            \nThen, will print the whole list.\n")
        stop: int = int(input("Type the stopping point: "))
    else:
        try:
            stop: int = int(argv[1])
        except:
            print("Error converting stop value.")
            return 2
        
    if stop < 2:
        print("Stop value must be an integer greater than or equal 2.")
        return 2

    print("2", end=" ")
    for i in range(3, stop, 2):
        if checkPrime(i):
            print(f"{i}", end=" ")
            cAppend(i)
    print("\n")

    print("Primes Found:")
    for i in primes[:size - 1]:
        print(f"{i},", end=" ")
    print(f"{primes[size - 1]}\n")

    print(f"Number of primes found: {size}")
    print(f"Capacity of final list: {capacity}")

    return 0


def checkPrime(number: int) -> bool:
    for i in primes:
        if number / 2 < i:
            return True

        if number % i == 0:
            return False
    return True


def cAppend(number: int) -> None:
    global primes, size, capacity

    if size == capacity:
        doubleList()
    
    primes[size] = number
    size += 1

    return


def doubleList() -> None:
    global primes, size, capacity

    capacity *= 2

    temp: list[int] = [0] * size * 2

    for i in range(size):
        temp[i] = primes[i]

    del primes
    gc.collect()
    primes = temp

    return


if __name__ == "__main__":
    argv: list[str] = sys.argv
    argc: int = len(argv)

    main(argc, argv)

