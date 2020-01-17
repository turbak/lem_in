NAME		= libftprintf.a

FILES 		= 	ft_printf.c\
				base_transfer.c\
				ft_putchar.c\
				ft_atoi.c\
				ft_putnbr_unsigned.c\
				ft_putnbr.c\
				ft_putstr.c\
				ft_strnew.c\
				ft_strrev.c\
				ft_strlen_p.c\
				ft_strjoin.c\
				ft_swapfree.c\
				put_int_unsigned.c\
				struct_init.c\
				put_int.c\
				ft_itoa.c\
				ft_memalloc.c\
				ft_bzero.c\
				putst.c\
				ft_strcmp.c\
				put_char.c\
				ft_dtoa.c\
				ft_putchar_unicode.c\
				put_16x.c\
				get_conversions.c\
				parcer.c
				
OBJ			= $(patsubst %.c, %.o, $(FILES))
FLAGS		=  -Wall -Werror -Wextra
HEADER		= ft_printf.h

all: $(NAME)

.PHONY: clean fclean re

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	gcc -I . $(FLAGS) $< -c -o $@

clean:
	rm -f $(OBJ)

fclean:clean
	rm -f $(NAME)

re: fclean all
