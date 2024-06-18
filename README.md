# Projects

## Description of the repository:
This is a repository made for storing projects in all sorts of languages, published to show some of my projects used for (but not limited to) training, learning new stuff and creating codes that may be useful, interesting or fun.\
Below this description you can find simple explanations of the projects made here.

## Ordering 2 Words:
Ordering 2 words is a project in C that I made in order to learn how to read input of "strings" (char*) from the user dinamically (using scanf), and how I could order those same words read using only C and its aspects.

## Simple Calculator:
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