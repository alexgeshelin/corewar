#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/20 11:12:58 by vtymchen          #+#    #+#              #
#    Updated: 2017/02/20 16:01:25 by vtymchen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a

GCC = gcc -c -Wall -Werror -Wextra

SRC =	ft_printf.c \
		parse.c \
		print.c \
		ft_bzero.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_strlen.c \
		ft_atoi.c \
		ft_isdigit.c \
		print_s.c \
		print_d.c \
		ft_putnbr.c \
		print_d2.c \
		print_unsigned.c \
		unsigned_helper.c

OBJ =	$(SRC:.c=.o)

all: $(NAME)

NO_COLOR=\033[0m
OK_COLOR=\033[32;01m
DEL_COLOR=\033[31;01m

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	@echo $(NAME) "$(OK_COLOR)[MADE] $(NO_COLOR)"

%.o : %.c $(HEADER)
	@$(GCC) -o  $@ $<
	@echo $@ "$(OK_COLOR)[OK] $(NO_COLOR)"

clean:
	@rm -f $(OBJ)
	@echo $(OBJ) "$(DEL_COLOR)[DELETED] $(NO_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo $(NAME) "$(DEL_COLOR)[DELETED] $(NO_COLOR)"

re: fclean all