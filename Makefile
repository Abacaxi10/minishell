# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 19:02:17 by nbonnet           #+#    #+#              #
#    Updated: 2025/02/27 16:53:51 by rabatist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

PATH_LIBFT = ./libft
LIBFT = $(PATH_LIBFT)/libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

SRCS = 	builtins/pwd.c \
		builtins/env.c \
		builtins/echo.c \
		builtins/cd.c \
		builtins/cd2.c \
		builtins/export1.c \
		builtins/export2.c \
		builtins/unset.c \
		builtins/exit.c \
		main.c \
		utils.c \
		exec_utils.c \
		exec.c \
		command_path.c \
		init.c \
		builtins_utils.c \
		redirect.c \
		make_env_exp.c \
		make_env_exp2.c \
		update_shlvl.c \
		expand.c \
		expand2.c \
		signals.c \
		redirect_utils.c \
		parsing.c \
		parsing2.c \
		free.c \
		free2.c \
		parsing_sub_token.c \
		parsing_sub_token2.c \
		parsing_command.c \
		expand_utils.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -lhistory -o $(NAME)

$(LIBFT):
	make -C $(PATH_LIBFT)

clean:
	rm -rf $(OBJS)
	make clean -C $(PATH_LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(PATH_LIBFT)

norm :
	@norminette $(SRCS) minishell.h

re: fclean all

.PHONY: all clean fclean re norm
