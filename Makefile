CC = cc
CFLAGS = -Wall -Wextra -g #-Werror
INC = -I./includes
LIB = -lreadline
SRC = $(wildcard src/*/*.c)
NAME = minishell

.PHONY: all clean fclean re bonus
.SECONDARY:

all: $(NAME)

$(NAME): $(SRC:.c=.o)
	$(CC) $^ $(LIB) -o $(NAME)

%.o: %.c
	$(info test: $(patsubst src/%/*.c,obj/*.o,$(SRC)))
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(SRC:.c=.o) $(BONUS:.c=.o)

fclean: clean
	rm -rf $(NAME) $(BNAME)

re: fclean all