#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Take the user name
    string name = get_string("What's your name?\n");

    // print hello to user
    printf("hello, %s\n", name);
}
