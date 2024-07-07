#include <stdio.h>
#include <stdlib.h>

int size = 0;
int capacity = 1;
int *primes = NULL;

int checkPrime(int number);
void append(int number);
void doubleArray();

int main(int argc, char *argv[]) {

    if (argc > 2) {
        printf("Usage: ./primes or ./primes STOP\n");
        return 1;
    }

    primes = malloc(sizeof(int));

    if (primes == NULL) {
        printf("Could not allocate space for array, aborting.\n");
        return 1;
    }

    primes[0] = 2;
    size++;

    int stop;
    if (argc == 1) {
        printf("Will find and print numbers until the stopping point.\
            \nThen, will print the whole list.\n");
        printf("Type the stopping point: ");
        scanf("%i", &stop);
    }
    else {
        stop = atoi(argv[1]);

        if (stop == 0) {
            printf("Error converting stop value, or given value is less than 2.\n");
            return 2;
        }
    }

    if (stop < 2) {
        printf("Stop value must be an integer greater than or equal 2.\n");
        return 2;
    }

    printf("2 ");
    for (int i = 3; i < stop; i+=2) {
        if (checkPrime(i)) {
            printf("%i ", i);
            append(i);
        }
    }
    printf("\n\n");

    printf("Primes Found:\n");
    for (int i = 0; i < size - 1; i++) {
        printf("%i, ", primes[i]);
    }
    printf("%i\n\n", primes[size - 1]);

    printf("Number of primes found: %i\n", size);
    printf("Capacity of final array: %i\n", capacity);

    return 0;
}

int checkPrime(int number) {
    for (int i = 0; i < size; i++) {
        if (number / 2 < primes[i]) {
            return 1;
        }

        if (number % primes[i] == 0) {
            return 0;
        }
    }
    
    return 1;
}

void append(int number) {
    if (size == capacity) {
        doubleArray();
    }

    primes[size] = number;
    size++;

    return ;
}

void doubleArray() {
    capacity *= 2;

    int *temp = malloc(sizeof(int) * size * 2);

    if (temp == NULL) {
        printf("Could not allocate space for array, aborting.\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        temp[i] = primes[i];
    }

    free(primes);
    primes = temp;

    return ;
}