NAME = minishell
SRCS = tokenize.c microshell.c
OBJS = $(SRCS:.c=.o)
LIBFT = ./Libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C ./Libft

$(NAME): $(OBJS)
	cc -o $(NAME) $(OBJS) -L./Libft -lft -lreadline

.c.o:
	cc -c $< -o $@

clean:
	rm -rf $(OBJS)
	make clean -C ./Libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./Libft

re: fclean all

.PHONY: all clean fclean re

