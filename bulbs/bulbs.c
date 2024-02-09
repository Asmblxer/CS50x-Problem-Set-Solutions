#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
const int BITS_IN_BYTE = 8;

int BinPow(int b, int e){
    int power = 1;
    while(e) {
        if(e & 1) power *= b;
        e >>= 1, b *= b;
    }   return power;
}

void decimal_Binary(int decimal, char Bin_string[]){
    for (int i = 0; i <= BITS_IN_BYTE; i++) {
        int bit = BinPow(2, BITS_IN_BYTE - i);
        if (decimal >= bit) {
            Bin_string[i] = '1';
            decimal -= bit;
        }
    }
}

void print_bulb(char bit) {
    if (bit == '0') printf("\U000026AB");
    else if (bit == '1') printf("\U0001F7E1");
}

int main(void)
{

    string sentence = get_string("Message: ");
    for (int i = 0; i < strlen(sentence); i++) {
        int letter_value = (int)sentence[i];
        char Bin_string[9] = "000000000";
        decimal_Binary(letter_value, Bin_string);
        for (int j = 1; j <= BITS_IN_BYTE; j++)
            print_bulb(Bin_string[j]);
        printf("\n");
    }
}