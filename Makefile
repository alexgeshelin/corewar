#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/07 09:05:41 by vtymchen          #+#    #+#              #
#    Updated: 2017/06/07 09:05:43 by vtymchen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME_ASM = asm

NAME_VM = corewar

GCC = gcc -c -Wall -Wextra -Werror

SRC_ASM	=	assembler/main.c \
			assembler/helper.c \
			assembler/make_coding_byte.c \
			assembler/write_args.c \
			assembler/write_header.c \
			assembler/fill_struct.c \
			assembler/valid_add_func.c \
			assembler/valid_add_lable.c \
			assembler/valid_arr_func.c \
			assembler/valid_instruct.c \
			assembler/valid_instruct2.c \
			assembler/valid_lable.c \
			assembler/valid_name_com.c \
			assembler/valid_add_ins_func.c \
			assembler/main_validate.c \
			assembler/trash_func.c

SRC_VM	=	VM/corewar.c \
			VM/init1.c \
			VM/init2.c \
			VM/ops1.c \
			VM/ops2.c \
			VM/ops3.c \
			VM/ops4.c \
			VM/ops5.c \
			VM/util.c \
			VM/visualisation.c \
			VM/war.c

OBJ_ASM	=	$(SRC_ASM:.c=.o)

OBJ_VM	=	$(SRC_VM:.c=.o)

HEADER = headers/op.h

NO_COLOR = \033[0m
OK_COLOR = \033[32;01m
DEL_COLOR = \033[31;01m

all: $(NAME_ASM) $(NAME_VM)

$(NAME_ASM): $(OBJ_ASM)  libft_ ft_printf_
	@gcc -o $(NAME_ASM) $(OBJ_ASM) libft/libft.a ft_printf/libftprintf.a
	@echo $(NAME_ASM) "\033[36;01m[COMPILED] $(NO_COLOR)"

$(NAME_VM):$(OBJ_VM) libft_ ft_printf_
	@gcc -o $(NAME_VM) $(OBJ_VM) libft/libft.a ft_printf/libftprintf.a -lncurses
	@echo $(NAME_VM) "\033[36;01m[COMPILED] $(NO_COLOR)"

%.o : %.c $(HEADER)
	@$(GCC) -o  $@ $<
	@echo $@ "$(OK_COLOR)[OK]$(NO_COLOR)"

libft_:
	@make -C libft

ft_printf_:
	@make -C ft_printf

clean:
	@rm -f $(OBJ_ASM)
	@rm -f $(OBJ_VM)
	@make clean -C libft
	@make clean -C ft_printf
	@echo $(OBJ_ASM) "$(DEL_COLOR)[DELETED] $(NO_COLOR)"
	@echo $(OBJ_VM) "$(DEL_COLOR)[DELETED] $(NO_COLOR)"

fclean: clean
	@rm -f $(NAME_ASM)
	@rm -f $(NAME_VM)
	@make fclean -C libft
	@make fclean -C ft_printf
	@echo $(NAME_ASM) "$(DEL_COLOR)[DELETED] $(NO_COLOR)"
	@echo $(NAME_VM) "$(DEL_COLOR)[DELETED] $(NO_COLOR)"

re: fclean all
