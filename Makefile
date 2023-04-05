# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alevra <alevra@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 16:28:53 by bajeanno          #+#    #+#              #
#    Updated: 2023/03/01 18:39:18 by alevra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -I libft/head -I head -I . -lreadline

DEBUG_FLAGS = -g3 #-fsanitize=address

LIBFT = libft/libft.a

SRC =	minishell.c\
		builtins.c \
		builtins_cd_pwd.c \
		builtins_echo.c \
		cmd_utils.c \
		convert_token_lst_into_cmd_lst.c \
		debug_utils.c \
		execute_cmd.c\
		execute_cmd_line.c\
		get_path.c\
		main_token_parsing.c\
		main_token_utils.c \
		utils.c\
		main_tokenizer.c\
		expand_content.c\
		expand_tokens_from_list.c\
		expand_content_utils.c\
		expand_utils.c \
		heredoc_manager.c \
		keyval_utils.c \
		error_handling.c\


BONUS_SRC =

DEPENDS	:=	$(addprefix obj/,$(SRC:.c=.d)) $(addprefix obj/,${BONUS_SRC:.c=.d})

OBJ = $(addprefix obj/,$(SRC:.c=.o))

BONUS_OBJ = $(addprefix obj/,$(BONUS_SRC:.c=.o))

all : create_obj_folder lib
	$(MAKE) $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) $(FLAGS) -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include $(DEBUG_FLAGS) -o $(NAME)

bonus : create_obj_folder lib .bonus

.bonus : $(OBJ) $(BONUS_OBJ)
	$(CC) $(OBJ) $(BONUS_OBJ) $(LIBFT) $(FLAGS) -o $(NAME)

create_obj_folder :
	mkdir -p obj

obj/%.o : src/%.c Makefile $(LIBFT)
	cc $(DEBUG_FLAGS) -Werror -Wall -Wextra -c $< -MD -I /opt/homebrew/opt/readline/include -I libft/head -I head -o $@

debug : lib
	$(CC) $(OBJ) $(LIBFT) $(FLAGS) $(DEBUG_FLAGS) -o debug$(NAME)

$(LIBFT): lib

lib : libft
	@$(MAKE) -C libft

libft :
	git clone git@github.com:fan2bolide/libft.git

run : all
	./a.out

clean :
	$(RM) $(OBJ) $(BONUS_OBJ) $(DEPENDS)
	$(RM) -r $(NAME).dSYM
	$(MAKE) clean -C libft

fclean : clean
	@$(RM) $(NAME)
	@$(RM) .main .bonus
	@$(MAKE) fclean -C libft

re : fclean
	@$(MAKE) all

.PHONY : all lib run re clean fclean bonus create_obj_folder

-include $(DEPENDS)
