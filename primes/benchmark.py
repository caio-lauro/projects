import subprocess, timeit, gc

times: list[str] = []

def main() -> int:
    number: str = input("Type stopping point for the benchmark: ")

    try:
        if int(number) < 2:
            print("Invalid stopping point, stop must be greater than or equal to 2.")
            return 1
    except:
        print("Stop must be an integer.")
        return 2

    writeBenchmark: str = input("Write info to benchmark.txt? (Y/n) ")
    info: bool = False

    if writeBenchmark.lower() == "y":
        info = True
    elif writeBenchmark.lower() != "n":
        print("Invalid choice. Proceding with 'n'.")

    print()

    print("C Benchmark:")
    command: list[str] = ["codes/primes", number]
    c_output: str = runCode(command)
    print()

    print("Python Benchmark:")
    command: list[str] = ["python3", "codes/primes.py", number]
    python_output: str = runCode(command)
    print()

    print("Python (Append) Benchmark:")
    command: list[str] = ["python3", "codes/primesAppend.py", number]
    pythonAppend_output: str = runCode(command)
    print()

    if info:
        c_output: list[str] = c_output.split("\n")
        python_output: list[str] = python_output.split("\n")
        pythonAppend_output: list[str] = pythonAppend_output.split("\n")

        with open(file="benchmark.txt", mode="w") as fp:
            lines: list[str] = [f"Text with stop: {number}\n\n",
                    f"C\n", 
                    f"    {c_output[-3]}\n", 
                    f"    {c_output[-2]}\n\n", 
                    f"    {times[0]}\n\n\n",
                    f"Python (default append)\n", 
                    f"    {python_output[-3]}\n", 
                    f"    {python_output[-2]}\n\n", 
                    f"    {times[1]}\n\n\n",
                    f"Python (implemented append)\n", 
                    f"    {pythonAppend_output[-3]}\n", 
                    f"    {pythonAppend_output[-2]}\n\n", 
                    f"    {times[2]}\n"
                    ]
            
            fp.writelines(lines)

        print("More info on benchmark.txt")
    else:
        del c_output, python_output, pythonAppend_output
        gc.collect()

    return 0


def runCode(command: list[str]) -> str:
    start: float = timeit.default_timer()

    program: subprocess.CompletedProcess[str] = subprocess.run(
        command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
    
    stop: float = timeit.default_timer()

    time: float = stop - start
    printTime(time)

    return program.stdout


def printTime(time: float) -> None:
    global times

    minutes: int = int(time // 60)
    seconds: float = round(time % 60, 3)

    formatted_time: str = f"Time: {minutes}m{seconds}s"
    times.append(formatted_time)

    print(formatted_time)

    return

if __name__ == "__main__":
    main()