#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char rotate(char c, int n)
{
    int tmp;
    if (isupper(c))
    {
        tmp = c - 'A';
        tmp = (tmp + n) % 26;
        tmp += 'A';
    }
    else
    {
        tmp = c - 'a';
        tmp = (tmp + n) % 26;
        tmp += 'a';
    }
    return (char) tmp;
}

int main(int argc, string argv[])
{
    if (argc > 2 || argc <= 1)
    {
        return printf("Usage: ./caesar key\n"), 1;
    }
    else if (argv[1][0] < '0' || argv[1][0] > '9')
    {
        return printf("Usage: ./caesar key\n"), 1;
    }
    else
    {
        string ss = argv[1];
        for (int i = 0; i < strlen(ss); i++)
        {
            if (!isdigit(ss[i]))
            {
                return printf("Usage: ./caesar key\n"), 1;
            }
        }
        int key = atoi(argv[1]);
        string text = get_string("plaintext:  ");
        printf("ciphertext: ");
        for (int i = 0; i < strlen(text); i++)
        {
            if (isalpha(text[i]))
            {
                printf("%c", rotate(text[i], key));
            }
            else
            {
                printf("%c", text[i]);
            }
        }
        printf("\n");
    }
    return 0;
}
