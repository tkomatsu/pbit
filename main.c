#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

static void	make_bin(uint64_t n, char *box, int size, int is_negative)
{
	uint64_t	i;
	uint64_t	mask;

	i = 0;
	mask = (uint64_t)1 << (sizeof(int64_t) * CHAR_BIT - 1);
	n <<= sizeof(int64_t) * CHAR_BIT - size;
	while (mask && size--)
	{
		box[i++] = !!(n & mask) + '0';
		mask >>= 1;
	}
	if (is_negative)
		box[0] = '1';
	box[i] = '\0';
}

int	ft_getsize(uint64_t n)
{
	if (n <= UINT8_MAX)
		return (sizeof(int8_t) * CHAR_BIT);
	if (n <= UINT16_MAX)
		return (sizeof(int16_t) * CHAR_BIT);
	else if (n <= UINT32_MAX)
		return (sizeof(int32_t)* CHAR_BIT);
	else
		return (sizeof(int64_t)* CHAR_BIT);
}

static void	ft_putbin(uint64_t n, int is_negative)
{
	int		i;
	int		size;
	char	s[65];

	size = ft_getsize(n);
	make_bin(n, s, size, is_negative);
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

static uint64_t	ft_labs(int64_t n)
{
	uint64_t	u;

	u = n;
	if (u > INT64_MAX)
		u = ~u + 1;
	return (u);
}

int main(int argc, char **argv)
{
	int64_t		res;
	uint64_t	abs;
	char		*error;
	const char	*message = "invalid argument\n";

	if (ft_labs(LLONG_MIN) == ft_labs(LLONG_MAX))
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
	abs = ft_labs(res);
	ft_putbin(abs, res < 0);
}
