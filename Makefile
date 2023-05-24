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
		builtins/builtin_cd.c \
		builtins/builtin_cd_utils.c \
		builtins/builtin_env.c \
		builtins/builtin_exit.c \
		builtins/builtin_export.c \
		builtins/builtin_unset.c \
		builtins/builtins.c \
		builtins/builtins_echo.c \
		builtins/builtins_pwd.c \
		execution/case_current_token_type_is_exec_name.c \
		execution/check_path.c \
		signals/terminal_handling.c\
		execution/cmd_utils.c \
		execution/convert_token_lst_into_cmd_lst.c \
		execution/convert_utils.c \
		env/create_env.c\
		env/env_var_utils.c \
		env/env_var_utils_getters_and_setters.c \
		error/error_handling.c\
		execution/exec_utils.c\
		execution/execute_cmd.c\
		execution/execute_cmd_utils.c \
		execution/execute_cmd_line.c\
		execution/execute_cmd_line_utils.c\
		exit_code/exit_code_handler.c\
		expands/expand_content.c\
		expands/expand_content_utils.c\
		expands/expand_tokens_from_list.c\
		expands/expand_utils.c \
		expands/expand_with_value.c\
		execution/fds.c \
		execution/get_path.c\
		execution/get_path_utils.c\
		lexer/main_token_parsing.c\
		lexer/main_token_utils.c \
		lexer/main_token_checkers.c\
		lexer/lexer.c\
		lexer/lexer_utils.c\
		heredoc/heredoc_manager.c \
		heredoc/heredoc_manager_utils.c \
		env/keyval_conversion.c \
		env/keyval_utils.c \
		signals/signal_handling.c\

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
	mkdir -p obj/builtins obj/env obj/error obj/execution obj/exit_code obj/expands obj/heredoc obj/lexer obj/signals

obj/%.o : src/%.c Makefile
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
