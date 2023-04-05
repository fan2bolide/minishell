NAME = libft.a

SRC			=	ft_atoi.c			\
				ft_bzero.c			\
				ft_calloc.c			\
				ft_isalnum.c		\
				ft_isalpha.c		\
				ft_isascii.c		\
				ft_isdigit.c		\
				ft_isprint.c		\
				ft_isset.c			\
				ft_isspace.c		\
				ft_itoa.c			\
				ft_memalloc.c		\
				ft_memccpy.c		\
				ft_memchr.c			\
				ft_memcmp.c			\
				ft_memcpy.c			\
				ft_memdel.c			\
				ft_memmove.c		\
				ft_memset.c			\
				ft_putchar.c		\
				ft_putchar_fd.c		\
				ft_putendl.c		\
				ft_putendl_fd.c		\
				ft_putnbr.c			\
				ft_putnbr_fd.c		\
				ft_putstr.c			\
				ft_putstr_fd.c		\
				ft_split_destroy.c	\
				ft_old_split.c		\
				ft_split.c			\
				ft_strcat.c			\
				ft_strchr.c			\
				ft_strclr.c			\
				ft_strcmp.c			\
				ft_strcpy.c			\
				ft_strdel.c			\
				ft_strdup.c			\
				ft_strequ.c			\
				ft_striter.c		\
				ft_striteri.c		\
				ft_strjoin.c		\
				ft_strlcat.c		\
				ft_strlcpy.c		\
				ft_strlen.c			\
				ft_strmap.c			\
				ft_strmapi.c		\
				ft_strncat.c		\
				ft_strncmp.c		\
				ft_strncpy.c		\
				ft_strndup.c		\
				ft_strnequ.c		\
				ft_strnew.c			\
				ft_strnstr.c		\
				ft_strrchr.c		\
				ft_strstr.c			\
				ft_strtrim.c		\
				ft_substr.c			\
				ft_tolower.c		\
				ft_toupper.c		\
				ft_lstnew.c			\
				ft_lstadd_front.c	\
				ft_lstadd_back.c	\
				ft_lstsize.c		\
				ft_lstlast.c		\
				ft_lstdelone.c		\
				ft_lstclear.c		\
				ft_lstiter.c		\
				ft_lstmap.c			\
				ft_lstpop_back.c	\
				ft_lstpop_front.c	\
				get_next_line.c		\
				get_next_line_utils.c\
				ft_print_hexa.c		\
				ft_printf.c			\
				ft_print_int.c		\
				ft_putnbr_base_unsigned.c\
				ft_max.c			\
				ft_realloc.c		\
				ft_dup_arr.c		\
				ft_lst_to_arr.c		\
				str_starts_with.c	\
				str_contains_digits_only.c \
				can_be_converted_to_long.c \
				ft_free_arr.c \

OBJ = $(addprefix obj/,$(SRC:.c=.o))

all	: create_obj_folder $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

obj/%.o : src/%.c Makefile head/libft.h
	cc -Wall -Wextra -Werror -c $< -o $@ -I head -g

create_obj_folder :
	mkdir -p obj

clean:
	$(RM) $(OBJ)
	$(RM) $(BONUS_OBJ)
	$(RM) -r obj

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

.PHONY : all bonus clean fclean re

