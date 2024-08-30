# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/08 18:05:22 by samunyan          #+#    #+#              #
#    Updated: 2022/06/08 18:05:23 by samunyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
NAME_BONUS	=	pipex_bonus

#Libs
LIBDIR			=	../libft
LIBFT			=	libft.a

#Directories
OBJDIR			= 	./objs
SRCDIR			=	./srcs
HEADDIRS		=	./include $(LIBDIR)/include

#Files
FILES	=	main.c \
			ft_getenv.c \
			ft_get_bin_path.c \
			parse.c \
			parse_utils.c \
			execute.c \
			execute_utils.c \
			redirect.c \
			redirect_utils.c \
			utils.c

B_FILES	=	main_bonus.c \
			ft_getenv.c \
			ft_get_bin_path.c \
			parse.c \
			parse_utils.c \
			execute.c \
			execute_utils.c \
			redirect.c \
			redirect_utils.c \
			utils.c
SRCS	= 	$(addprefix $(SRCDIR)/, $(FILES))
B_SRCS	=  	$(addprefix $(SRCDIR)/, $(B_FILES))
OBJS	=	$(addprefix $(OBJDIR)/, $(FILES:.c=.o))
B_OBJS	= 	$(addprefix $(OBJDIR)/, $(B_FILES:.c=.o))

#Compiler
SYSTEM		 := $(shell uname)
ifeq ($(SYSTEM),Linux)
CC			=	clang
else
CC			= 	gcc
endif
CFLAGS	=	-Wall -Werror -Wextra $(HEADDIRS:%=-I %)
LDFLAGS	=	-L $(LIBDIR) -lft
ifeq ($(SANITIZER), 1)
		CFLAGS	+=	-g -fsanitize=address
		LDFLAGS	+=	-g -fsanitize=address
endif
ifeq ($(DEBUG), 1)
		CFLAGS	+=	-g
		LDFLAGS	+=	-g
endif

.PHONY:		all bonus FORCE clean fclean re sanitizer debug bonus_sanitizer bonus_debug

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $(NAME)
			@test -z '$(filter %.o,$?)' || (echo ✅ $(BBlue) [$(NAME)]"\t"$(BGreen)Compilation done. \
				Usage: ./$(NAME) [file1] [cmd1] [cmd2] [file2]  && \
				echo "\t\t\t\t\t(behaves like \" < file1 cmd1 | cmd2 > file2 \")" && \
				echo $(White)"\t\t\t"Compiler flags: $(CFLAGS)$(Color_Off))

$(NAME_BONUS): $(LIBFT) $(B_OBJS)
			@$(CC) $(CFLAGS) $(B_SRCS) $(LDFLAGS) -o $(NAME_BONUS)
			@test -z '$(filter %.o,$?)' || (echo ✅ $(BBlue) [$(NAME)]"\t"$(BGreen)Compilation done. \
				Usage: ./$(NAME) [file1] [cmd1] [cmd2] [...] [file2]  && \
				echo "\t\t\t\t\t(behaves like \" < file1 cmd1 | cmd2 | [...] > file2 \")" && \
				echo $(White)"\t\t\t"Compiler flags: $(CFLAGS)$(Color_Off))

bonus:		$(NAME_BONUS)
			@cp $(NAME_BONUS) $(NAME)
			@rm $(NAME_BONUS)

$(OBJDIR)/%.o:  $(SRCDIR)/%.c
			@mkdir -p $(dir $@)
			@echo ⌛ $(BBlue)[$(NAME)]"\t"$(Yellow)Compiling $<$(Color_Off)
			@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): FORCE
			@make -C $(LIBDIR)

FORCE:

clean:
			@if [ -d $(OBJDIR) ]; then \
  					rm -rf $(OBJDIR); \
  					echo 🗑$(BBlue)[$(NAME)]"\t"$(BGreen)Object files removed.$(Color_Off); \
  			fi
			@make -C $(LIBDIR) clean

fclean:		clean
			@if [ -f $(NAME) ]; then \
					rm -rf $(NAME); \
					rm -rf *.dSYM; \
					echo 🗑$(BBlue)[$(NAME)]"\t"$(BGreen)Executable removed.$(Color_Off); \
			fi
			@make -C $(LIBDIR) fclean

re:			fclean all

sanitizer:
			@SANITIZER=1 make re

debug:
			@DEBUG=1 make re


bonus_sanitizer: fclean
			@SANITIZER=1 make bonus

bonus_debug: fclean
			@DEBUG=1 make bonus

# Colors
## Reset
Color_Off='\033[0m'       # Text Reset
## Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White
## Bold
BBlack='\033[1;30m'       # Black
BRed='\033[1;31m'         # Red
BGreen='\033[1;32m'       # Green
BYellow='\033[1;33m'      # Yellow
BBlue='\033[1;34m'        # Blue
BPurple='\033[1;35m'      # Purple
BCyan='\033[1;36m'        # Cyan
BWhite='\033[1;37m'       # White
## Underline
UBlack='\033[4;30m'       # Black
URed='\033[4;31m'         # Red
UGreen='\033[4;32m'       # Green
UYellow='\033[4;33m'      # Yellow
UBlue='\033[4;34m'        # Blue
UPurple='\033[4;35m'      # Purple
UCyan='\033[4;36m'        # Cyan
UWhite='\033[4;37m'       # White
## Background
On_Black='\033[40m'       # Black
On_Red='\033[41m'         # Red
On_Green='\033[42m'       # Green
On_Yellow='\033[43m'      # Yellow
On_Blue='\033[44m'        # Blue
On_Purple='\033[45m'      # Purple
On_Cyan='\033[46m'        # Cyan
On_White='\033[47m'       # White
## Bold High Intensity
BIBlack='\033[1;90m'      # Black
BIRed='\033[1;91m'        # Red
BIGreen='\033[1;92m'      # Green
BIYellow='\033[1;93m'     # Yellow
BIBlue='\033[1;94m'       # Blue
