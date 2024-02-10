#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
     float letter = 0, word = 1, sentence = 0;
     string s = get_string("Text: ");
     for(int i = 0; i < strlen(s); i++)
     {
          if((s[i] >= 'A' && s[i] <='Z') || (s[i] >= 'a' && s[i] <='z'))
          {
               letter++;
          }
          else if (s[i] == ' ')
          {
               word++;
          }
          else if(s[i] == '!' || s[i] == '.' || s[i] == '?')
          {
               sentence++;
          }
     }
     float L = (letter / word) * 100, S = (sentence / word) * 100;
     int index = round(0.0588 * L - 0.296 * S - 15.8);
     if(index <= 1)
     {
          printf("Before Grade 1\n");
     }
     else if(index >= 16)
     {
          printf("Grade 16+\n");
     }
     else
     {
          printf("Grade %d\n", index);
     }
}