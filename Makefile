NAME = lem-in

LIBFT = ./libft/libft.a

SRC =	bfs.c\
		check.c\
		errors.c\
		form_paths.c\
		freeall.c\
		input_forks.c\
		lem_in.c\
		output_forks.c\
		read_funcs.c\
		remove_rooms_and_links.c\
		send_ants.c\
		utils.c\
		utils2.c

OBJ = $(patsubst %.c, %.o, $(SRC))

CPPFLAGS = -Wall -Werror -Wextra

HEADER = lem_in.h

all: $(NAME)

$(LIBFT):
	$(MAKE) -SC libft all

$(NAME) : $(OBJ) $(LIBFT)
	gcc $(CPPFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

%.o: %.c $(HEADER) $(LIBFT)
	gcc -I . $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) && $(MAKE) clean -C ./libft

fclean: clean
	rm -f $(OBJ) $(NAME) && $(MAKE) fclean -C ./libft

re: fclean all

.PHONY: clean fclean re all