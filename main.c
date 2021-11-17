#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void make_bin(uint64_t n, char *box, int size, int is_negative) {
	uint64_t i = 0;
	uint64_t mask = (uint64_t)1 << (sizeof(int64_t) * CHAR_BIT - 1);
	n <<= sizeof(int64_t) * CHAR_BIT - size;
	if (is_negative) n = ~n + 1;
	while (mask && size--) {
		box[i++] = !!(n & mask) + '0';
		mask >>= 1;
	}
	box[i] = '\0';
}

int ft_getsize(uint64_t n) {
	if (n <= UINT8_MAX) {
		return (sizeof(int8_t) * CHAR_BIT);
	}
	if (n <= UINT16_MAX) {
		return (sizeof(int16_t) * CHAR_BIT);
	} else if (n <= UINT32_MAX) {
		return (sizeof(int32_t) * CHAR_BIT);
	} else {
		return (sizeof(int64_t) * CHAR_BIT);
	}
}

static void ft_putbin(uint64_t n, int is_negative) {
	char s[65];

	int size = ft_getsize(n);
	make_bin(n, s, size, is_negative);
	for (int i = 0; s[i]; ++i) {
		if (i && !(i % 8))
			printf(" | ");
		else if (i && !(i % 4))
			printf(" ");
		printf("%c", s[i]);
	}
	puts("");
}

static uint64_t ft_labs(int64_t n) {
	uint64_t u = n;
	if (u > INT64_MAX) {
		u = ~u + 1;
	}
	return (u);
}

static void run(char *arg) {
	const char *message = "invalid argument\n";
	char *error;
	errno = 0;
	int64_t res = strtoll(arg, &error, 10);
	if (errno || *error) {
		fprintf(stderr, "%s", message);
		exit(1);
	}
	uint64_t abs = ft_labs(res);
	ft_putbin(abs, res < 0);
}

static int help(char *cmd) {
	printf("Usage: %s [NUMBERS]...\n", cmd);
	return (0);
}

int main(int argc, char **argv) {
	if (sizeof(int) != 4) return 1;
	if (argc == 2 && !strcmp(argv[1], "-h")) {
		return (help(argv[0]));
	}
	if (ft_labs(LLONG_MIN) == ft_labs(LLONG_MAX)) {
		exit(2);
	}
	if (argc == 1) {
		char *line = NULL;
		size_t linecap = 0;
		ssize_t linelen;
		while ((linelen = getline(&line, &linecap, stdin)) > 0) {
			if (isspace(line[0])) {
				continue;
			}
			run(strtok(line, "\t\n\v\f\r "));
			char *tok;
			while ((tok = strtok(NULL, "\t\n\v\f\r ")) != NULL) {
				run(tok);
			}
			free(line);
			line = NULL;
		}
	} else {
		for (int i = 1; i < argc; ++i) {
			run(argv[i]);
		}
	}
}
