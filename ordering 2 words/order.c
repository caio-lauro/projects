#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_word(void);
int printWordsInOrder(char *word_1, char *word_2);

int main(void)
{
    char *word_1;
    word_1 = get_word();

    char *word_2;
    word_2 = get_word();

    if (word_1 == NULL || word_2 == NULL)
    {
        printf("Program failed, aborting.\n");
        return 1;
    }

    printWordsInOrder(word_1, word_2);

    return 0;
}

char *get_word(void)
{
    printf("Type a word: ");
    
    char c;
    char *word = NULL;
    int size = 1;

    while (1)
    {
        scanf("%c", &c);
        if (isalpha(c) == 0)
        {
            break;
        }

        size++;

        if (size == 2)
        {
            word = malloc(sizeof(char) * size);
            word[0] = c;
            word[1] = '\0';
        }
        else
        {
            char *s = malloc(sizeof(char) * size);
            strcpy(s, word);
            s[size - 2] = c;
            s[size - 1] = '\0';

            free(word);

            word = malloc(sizeof(char) * size);
            strcpy(word, s);

            free(s);
        }
    }

    return word;
}

int printWordsInOrder(char *word_1, char *word_2)
{
    int i = 0;
    while (word_1[i] != '\0' || word_2[i] != '\0')
    {
        if (( (int) tolower(word_1[i]) - (int) tolower(word_2[i])) < 0)
        {
            printf("%s, %s\n", word_1, word_2);
            return 0;
        }
        else if (( (int) tolower(word_1[i]) - (int) tolower(word_2[i])) > 0)
        {
            printf("%s, %s\n", word_2, word_1);
            return 0;
        }

        i++;
    }

    if (word_1[i] == '\0')
    {
        printf("%s, %s\n", word_1, word_2);
        return 0;
    }
    else
    {
        printf("%s, %s\n", word_2, word_1);
        return 0;
    }
}