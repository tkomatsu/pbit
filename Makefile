NAME = pbit
CC = gcc
CFLAGS = -Wall -Werror -Wextra -O2
RM = rm -fr

SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(NAME) $(OBJS)

install: $(NAME)
	mv $< /usr/local/bin
	sudo chmod 755 /usr/local/bin/$(NAME)

uninstall:
	sudo $(RM) /usr/local/bin/$(NAME)
	make clean

.PHONY: all clean install uninstall
