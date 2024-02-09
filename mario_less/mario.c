#include <cs50.h>
#include <stdio.h>

int main(void)
{
    while (true)
    {
        int tmp = get_int("Height: ");
        if (tmp < 1 || tmp > 8)
        {
            continue;
        }
        else
        {
            for (int i = 1; i <= tmp; i++)
            {
                for (int x = 1; x <= tmp - i; x++)
                    printf(" ");
                for (int j = 1; j <= i; j++)
                {
                    printf("#");
                }
                printf("\n");
            }
            break;
        }
    }
}
