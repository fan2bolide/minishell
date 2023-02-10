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

NAME = 

FLAGS = -Werror -Wall -Wextra -I stack_lib -I libft -I .

DEBUG_FLAGS = -fsanitize=address -g3

LIBFT = libft/libft.a

SRC = 

BONUS_SRC = 

DEPENDS	:=	$(addprefix obj/,$(SRC:.c=.d)) $(addprefix obj/,${BONUS_SRC:.c=.d})

OBJ = $(addprefix obj/,$(SRC:.c=.o))

BONUS_OBJ = $(addprefix obj/,$(BONUS_SRC:.c=.o))

all : lib .main
	$(MAKE) $(NAME)

.main :
	touch .main
	$(RM) .bonus

$(NAME) : $(OBJ) .main
	$(CC) $(OBJ) $(LIBFT) $(STACK_LIB) $(FLAGS) -o $(NAME)

bonus : create_obj_folder lib .bonus

.bonus : $(OBJ) $(BONUS_OBJ)
	$(CC) $(OBJ) $(BONUS_OBJ) $(LIBFT) $(STACK_LIB) $(FLAGS) -o $(NAME)
	touch .bonus
	$(RM) .mandatory

create_obj_folder :
	mkdir -p obj

obj/%.o : src/%.c Makefile
	cc -Wall -Wextra -Werror -c $< -MD -I libft/headers -I head -o $@

debug : lib
	$(CC) $(OBJ) $(LIBFT) $(FLAGS) $(DEBUG_FLAGS) -o debug$(NAME)

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

rm_lib :
	$(RM) -r libft

re : fclean
	$(MAKE) all

.PHONY : all lib run re clean fclean bonus rm_lib

-include $(DEPENDS)