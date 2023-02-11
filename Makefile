# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 16:28:53 by bajeanno          #+#    #+#              #
#    Updated: 2022/12/18 11:58:59 by bajeanno         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Werror -Wall -Wextra -I libft/head -I .

DEBUG_FLAGS = -fsanitize=address -g3

LIBFT = libft/libft.a

SRC = minishell.c

BONUS_SRC = 

DEPENDS	:=	$(addprefix dep/,$(SRC:.c=.d)) $(addprefix dep/,${BONUS_SRC:.c=.d})

OBJ = $(addprefix obj/,$(SRC:.c=.o))

BONUS_OBJ = $(addprefix obj/,$(BONUS_SRC:.c=.o))

all : build_directories lib
	@$(MAKE) $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) $(FLAGS) -o $(NAME)

bonus : build_directories lib .bonus

.bonus : $(OBJ) $(BONUS_OBJ)
	$(CC) $(OBJ) $(BONUS_OBJ) $(LIBFT) $(STACK_LIB) $(FLAGS) -o $(NAME)

build_directories :
	@mkdir -p obj
	@mkdir -p dep

obj/%.o : src/%.c Makefile
	$(CC) -Wall -Wextra -Werror -c $< -MD -I libft/head -I head -o $@

debug : lib
	$(CC) $(OBJ) $(LIBFT) $(FLAGS) $(DEBUG_FLAGS) -o debug_$(NAME)

lib : $(LIBFT)

$(LIBFT) : libft
	$(MAKE) -C libft

libft :
	git clone git@github.com:fan2bolide/libft.git

run : all
	./a.out

clean :
	$(RM) $(OBJ) $(BONUS_OBJ) $(DEPENDS)
	$(RM) -r $(NAME).dSYM
	$(MAKE) clean -C libft
	
fclean : clean
	$(RM) $(NAME)
	$(RM) .main .bonus
	$(MAKE) fclean -C libft

re : fclean
	$(MAKE) all

.PHONY : all lib run re clean fclean bonus build_directories

-include $(DEPENDS)