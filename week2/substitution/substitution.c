#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool valed_key(string key)
{
    int frq[26] = {0};
    for (int i = 0; i < strlen(key); i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
        else if (isupper(key[i]))
        {
            frq[key[i] - 'A']++;
        }
        else
        {
            frq[key[i] - 'a']++;
        }
    }
    for (int i = 0; i < 26; i++)
    {
        if (frq[i] > 1)
        {
            return false;
        }
    }
    return true;
}

int main(int argc, string argv[])
{
    string key = argv[1];
    if ((argc > 2 || argc <= 1) || strlen(key) < 26 || strlen(key) > 26)
    {
        return printf("Usage: ./substitution key\n"), 1;
    }
    if (!valed_key(key))
    {
        return printf("Usage: ./substitution key\n"), 1;
    }
    string text = get_string("plaintext:  ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            char c;
            if (isupper(text[i]))
            {
                int pos = text[i] - 'A';
                c = key[pos];
                c = toupper(c);
            }
            else
            {
                int pos = text[i] - 'a';
                c = key[pos];
                c = tolower(c);
            }
            printf("%c", c);
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    return printf("\n"), 0;
}
