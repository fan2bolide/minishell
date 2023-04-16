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
		builtin_cd.c \
		builtin_cd_utils.c \
		builtin_env.c \
		builtin_exit.c \
		builtin_export.c \
		builtin_unset.c \
		builtins.c \
		builtins_echo.c \
		builtins_pwd.c \
		case_current_token_type_is_exec_name.c \
		check_path.c \
		check_terminal.c\
		cmd_utils.c \
		convert_token_lst_into_cmd_lst.c \
		env_var_utils.c \
		env_var_utils_getters_and_setters.c \
		error_handling.c\
		exec_utils.c\
		execute_cmd.c\
		execute_cmd_utils.c \
		execute_cmd_line.c\
		execute_cmd_line_utils.c\
		exit_code_handler.c\
		expand_content.c\
		expand_content_utils.c\
		expand_tokens_from_list.c\
		expand_utils.c \
		expand_with_value.c\
		fds.c \
		get_path.c\
		get_path_utils.c\
		main_token_parsing.c\
		main_token_utils.c \
		main_token_checkers.c\
		lexer.c\
		lexer_utils.c\
		heredoc_manager.c \
		heredoc_manager_utils.c \
		keyval_utils.c \
		signal_handling.c\


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

.PHONY : all lib run re clean fclean bonus create_obj_folder leaks

leaks:	all
	echo "{" > valgrind_ignore_leaks.txt
	echo "    leak readline" >> valgrind_ignore_leaks.txt
	echo "    Memcheck:Leak" >> valgrind_ignore_leaks.txt
	echo "    ..." >> valgrind_ignore_leaks.txt
	echo "    fun:readline" >> valgrind_ignore_leaks.txt
	echo "}" >> valgrind_ignore_leaks.txt
	echo "{" >> valgrind_ignore_leaks.txt
	echo "    leak add_history" >> valgrind_ignore_leaks.txt
	echo "    Memcheck:Leak" >> valgrind_ignore_leaks.txt
	echo "    ..." >> valgrind_ignore_leaks.txt
	echo "    fun:add_history" >> valgrind_ignore_leaks.txt
	echo "}" >> valgrind_ignore_leaks.txt
	valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full\
	    --show-leak-kinds=all --track-origins=yes --verbose\
	    --show-mismatched-frees=yes --read-var-info=yes ./${NAME}

fds: all
	 valgrind --track-fds=yes --trace-children=yes ./${NAME}

-include $(DEPENDS)
