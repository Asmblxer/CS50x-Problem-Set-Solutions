#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = 1, m = 2;
    while (n < 9)
        n = get_int("Start size: ");
    while (m < n)
        m = get_int("End size: ");
    int ans = 0;
    while (n < m)
    {
        int new = n / 3, pass = n / 4;
        n += new, n -= pass;
        ans++;
    }
    printf("Years: %i\n", ans);
}
