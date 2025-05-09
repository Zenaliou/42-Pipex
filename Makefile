NAME		=	pipex

CFLAGS		=	-Wall -Werror -Wextra -Iincludes -g3

SRCS		=	src/pipex.c src/utils.c GNL/get_next_line.c GNL/get_next_line_utils.c

OBJS		=	$(SRCS:.c=.o)

INCLUDES	= 	-I includes -I libft -I ft_printf

LIBFT		=	libft/libft.a

FT_PRINTF	=	ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF) -o $(NAME)

$(LIBFT):
	make -C libft

$(FT_PRINTF):
	make -C ft_printf

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	make -C libft clean
	make -C ft_printf clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean
	make -C ft_printf fclean

re: fclean all

.PHONY: all clean fclean re