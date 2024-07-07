# Projects

## Description of the repository:
This is a repository made for storing projects in all sorts of languages, published to show some of my projects used for (but not limited to) training, learning new stuff and creating codes that may be useful, interesting or fun.\
Below this description you can find simple explanations of the projects made here.

### Ordering 2 Words:
Ordering 2 words is a project in C that I made in order to learn how to read input of "strings" (char*) from the user dinamically (using scanf), and how I could order those same words read using only C and its aspects.

### Simple Calculator:
Simple Calculator is a project in C, that evaluates expressions entered by the user. It uses the same idea of reading "strings" from the user that I used in "Ordering 2 Words", but instead, it reads simple math expressions, that are evaluated by the code. It accepts the following operators:

* '+' for addition - PRIORITY 1;
* '-' for subtraction - PRIORITY 1;
* '*' for multiplication - PRIORITY 2;
* '/' for division (often rounded down to the nearest integer) - PRIORITY 2;

Then, after the expression is entered by the user, the program evaluates which operator should be done first, and execute the calculations accordingly. For instance, entering "123+456*7" will output the final result as "3315".
> 123+456*7 \
> 123+3192 \
> 3315

As stated, it is a simple calculator, so division will round down to the nearest integer, and the calculator won't accept any other operators than the ones previous mentioned, using a check system, that also checks if the expression is valid. Besides the operators, of course, the calculator only accepts numbers. The calculator evaluates the expression from left to right, executing the operator with the biggest "priority level" found. \
Finally, my motivation to make this project was to see how far I could get using C, and whether or not I could build such an application.

### Primes
Primes is a project in C and in python, that calculates prime numbers in a range selected by the user, either via input (C's `scanf()` or Python's `input()`) or via command-line arguments. The range must be greater than or equal to 2 (because I honestly think there's no point in using it for any number less than that, since no primes exist in that range), and if it is, each code is able to find all the primes within that provided stopping point.\
For sake of comparison, I decided to add `benchmark.py` to measure the execution times of `primes.c`, `primes.py` and `primesAppend.py`. It uses the `subprocess` python module to execute `primes` and the python codes, using a stopping point provided by the user (via `input()`) in the command-line argument. Then, after execution, the files have their time measured using the `default_timer()` function from the `timeit` module to get the variation of time (time before and after the execution).\
I also implemented all codes in the most similar way possible, in order to make the comparison the most accurate and trustworthy. Python has two variants: `primes.py` and `primesAppend.py`, in which the latter would be the closest to the code in C.
#### Differentiating `primes.py` and `primesAppend.py`:
While `primes.py` uses python's default implementation of "append", the `append` method of the `list` class, `primesAppend.py` uses my own implementation of "append", closer to what I implemented in `primes.c`. I went for this approach to measure which one would take more space, which one would take more time, etc., and if it would make any difference at all. It turns out that my implementation of append makes the code slightly faster than python's, but it also takes more space.
#### Explaining my "append" function (C and `primesAppend.py`):
The append function was originally intended to work in a similar fashion to python's `append` method, although I made it different from the start.\
My first code for `append()`, in C, only increased the array to hold one more integer, therefore, whenever there was a new number to be appended to the array, it needed to increase in size. This approach was certainly the one that occupied the lesser amount of space, but took much more time in order to properly append new numbers.\
However, in my second code for `append()`, still in C, I decided to create a new function `doubleArray()`, that would do exactly as it says, doubling the capacity of the array, in order to minimize the amount of times the array must be increased in size to fit more numbers. In doing so, the program became much faster, decreasing almost by half the time it took to calculate primes until the 1,000,000 mark, but also took way more space, specially when being given large amounts of numbers to operate with.\
Finally, I decided to stick with the last approach, simply because it was faster, so it was used both in `primes.c` and in `primesAppend.py`.\
The way the `append()` function works is: if `size` is equal to `capacity`, it calls `doubleArray()`, which also doubles `capacity`. `size` and `capacity` are global variables, in which `size` represents the actual size of the array (or, at least, the amount of integers in the array), whereas `capacity` represents the total capacity of the array, its total size (the amount of numbers it can hold). If `size` is less than `capacity`, or if the array has been doubled, then, it changes the item at the `size`th index, and then increases `size`, just to make things simpler.
