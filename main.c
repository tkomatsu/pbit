#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

static void    make_bin(size_t n, char *box)
{
    size_t    i;
    size_t    mask;

    i = 0;
    mask = (size_t)1 << (sizeof(size_t) * CHAR_BIT - 1);
    while (mask)
    {
        box[i++] = !!(n & mask) + '0';
        mask >>= 1;
    }
    box[i] = '\0';
}

static void    ft_putbin(size_t n)
{
    int        i;
    char    s[65];

    make_bin(n, s);
    i = 0;
    while (s[i])
    {
        if (i && !(i % 8))
            printf(" | ");
        else if (i && !(i % 4))
            printf(" ");
        printf("%c", s[i]);
        i++;
    }
    puts("");
}

int main(int argc, char **argv)
{
    long long    res;
    char        *error;
    char        *message = "invalid argument\n";

    if ((unsigned long long)LLONG_MIN - 1 != (unsigned long long)LLONG_MAX)
        exit(2);
    errno = 0;
    if (argc != 2)
    {
        fprintf(stderr, "%s", message);
        return (1);
    }
    res = strtoll(argv[1], &error, 10);
    if (errno || *error)
    {
        fprintf(stderr, "%s", message);
        exit(1);
    }
    ft_putbin(res);
}
