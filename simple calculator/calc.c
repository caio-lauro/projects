#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
EXIT CODES

1 - Expression must contain only numbers and/ or operators.
    Expression has forbidden characters.

2 - Expression must start with number.
    Expression started with operator (missing number to the left).

3 - Expression must end with number.
    Expression ended with operator (missing number to the right).

4 - Expression must not have two or more consecutive operators.
    Expression has two or more consecutive operators (must have number between them).

*/

// Array of numbers and operators on expression
int *numbers = NULL;
char *operators = NULL;

// Number of operators
int operators_count = 0;

char *readExpression();
void checkExpression(char *expression);
void printPartial();
void solvePartial();

int main() {

    printf("\nSimple Calculator\n");
    printf("Allowed Operators:\n");
    printf("+ - * / \n\n");

    // Read expression

    char *expression = readExpression();

    // Check for valid expression

    checkExpression(expression);

    // Solve expression partially while printing the result, until every calculation is done
    
    while (operators_count > 0) {
        solvePartial();
        printPartial();

        operators_count--;
    }

    // Free memory

    free(expression);
    free(operators);
    free(numbers);

    return 0;
}

int checkChar(char c) {

    // Check if character is a number
    if ((int) c > 47 && (int) c < 58) {
        return 0;
    }

    // Checking for valid operators and returning their "priority level"
    switch (c) {
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        default:
            return -1;
    }

}

void solvePartial() {

    char operator;
    int operator_value = -1;
    int operator_index = -1;

    // Check for operator with biggest "priority level"
    for (int i = 0; i < strlen(operators); i++) {
        
        if (checkChar(operators[i]) > operator_value) {
            operator_index = i;
            operator_value = checkChar(operators[i]);
            operator = operators[i];
        }

    }

    // Remove used operator

    char *new_operators = malloc((operators_count - 1) * sizeof(char));

    for (int i = 0; i < strlen(operators); i++) {

        if (i == operator_index) {
            continue;
        }
        else if (i > operator_index) {
            new_operators[i - 1] = operators[i];
        }
        else {
            new_operators[i] = operators[i];
        }

    }

    new_operators[operators_count - 1] = '\0';

    free(operators);
    operators = new_operators;

    // Calculate using the operator and the two numbers "adjacent" to it

    int answer = 0;

    switch(operator) {

        case '+':
            answer = numbers[operator_index] + numbers[operator_index + 1];
            break;

        case '-':
            answer = numbers[operator_index] - numbers[operator_index + 1];
            break;

        case '*':
            answer = numbers[operator_index] * numbers[operator_index + 1];
            break;

        case '/':
            answer = numbers[operator_index] / numbers[operator_index + 1];
            break;

    }

    // Remove previous two numbers and add the answer to their calculation

    int *new_numbers = malloc(operators_count * sizeof(int));

    for (int i = 0; i < operators_count + 1; i++) {

        if (i == operator_index) {
            new_numbers[i] = answer;
        }
        else if (i == operator_index + 1) {
            continue;
        }
        else if (i > operator_index + 1) {
            new_numbers[i - 1] = numbers[i];
        }
        else {
            new_numbers[i] = numbers[i];
        }

    }

    free(numbers);
    numbers = new_numbers;

    return ;

}

void printPartial() {

    for (int i = 0; i < operators_count; i++) {

        printf("%i", numbers[i]);
        printf("%c", operators[i]);

    }
    
    printf("\n");

    return ;

}

void getNumbers(char *expression, int *operator_indexes) {

    // Array of numbers, the amount of numbers is always operator_count + 1, 
    // since for every operator there must be two adjacent numbers to it
    numbers = malloc((operators_count + 1) * sizeof(int));

    char *number = NULL;
    int size;

    int number_index = 0;

    for (int i = 0; i < strlen(expression) + 1; i++) {
        
        // Get new number
        if (number == NULL) {
            number = malloc(2 * sizeof(char));
            size = 2;
            number[0] = expression[i];
            number[1] = '\0';
        }
        
        // Increase number until a operator is found
        else if (checkChar(expression[i]) == 0) {
            size++;

            char *temp = malloc(size);
            strcpy(temp, number);

            temp[size - 2] = expression[i];
            temp[size - 1] = '\0';

            strcpy(number, temp);
            free(temp);
        }

        // When the operator is found, end the number and add it to the array
        else {
            numbers[number_index] = atoi(number);
            number_index++;
            free(number);
            number = NULL;
        }

    }

    return ;
}

void getOperators(char *expression) {

    // Need operators_count + 1 space for array, since we need '\0' at the end
    operators = malloc((operators_count + 1) * sizeof(char));
    int *operator_indexes = malloc(operators_count * sizeof(int));
    
    // "Append" every operator to the array
    for (int i = 0, j = 0; i < strlen(expression); i++) {
        if (checkChar(expression[i]) > 0) {
            operators[j] = expression[i];
            operator_indexes[j] = i;
            j++;
        }
    }

    // End the array
    operators[operators_count] = '\0';
    
    // Call getNumbers
    getNumbers(expression, operator_indexes);
    free(operator_indexes);

    return ;
}

char *readExpression() {
    
    printf("Enter an expression.\n");

    // Declare initial size as 2 (buffer + '\0')
    int size = 2;
    char *expression = malloc(size * sizeof(char));
    char buffer;

    // Read first char to see if it is valid
    scanf(" %c", &buffer);

    if (checkChar(buffer) == -1) {
        printf("Expression must contain only numbers and/ or operators.\n");

        free(expression);
        exit(1);
    }

    // Attributte first char to expression
    expression[0] = buffer;
    expression[1] = '\0';

    while (1) {
        // Read new char to buffer
        scanf("%c", &buffer);

        // Escape if char is \n (Enter)
        if (buffer == '\n') {
            break;
        }
        // Quit if checkChar returns -1 (invalid character)
        else if (checkChar(buffer) == -1) {
            printf("Expression must contain only numbers and/ or operators.\n");

            free(expression);
            exit(1);
        }

        // Copy expression to temporary variable
        char *temp = malloc(size * sizeof(char));
        strcpy(temp, expression);

        // Allocate space for extra char
        size++;
        expression = malloc(size * sizeof(char));

        // Copy temp to expression
        strcpy(expression, temp);

        // Add extra char
        expression[size - 2] = buffer;
        expression[size - 1] = '\0';
        
        // Free temporary variable
        free(temp);
    }

    return expression;
}

void checkExpression(char *expression) {
    int len = strlen(expression);

    // Check if first char is number
    if (checkChar(expression[0]) > 0) {
        printf("Expression must start with number.\n");
        exit(2);
    }

    // Check if last char is number
    if (checkChar(expression[len - 1]) > 0) {
        printf("Expression must end with number.\n");
        exit(3);
    }

    // Count number of operators in expression (quit if two consecutive operators are found)
    int operator_count = 0;

    for (int i = 1; i < len - 1; i++) {
        if ((checkChar(expression[i]) > 0) && (checkChar(expression[i+1]) > 0)) {
            printf("Expression must not have two or more consecutive operators.\n");
            exit(4);
        }

        if (checkChar(expression[i]) > 0) {
            operator_count++;
        }
    }

    // Attribute operator_count to global variable operators_count
    operators_count = operator_count;

    // Call getOperators
    getOperators(expression);

    return ;
}