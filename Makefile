# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/02 11:38:42 by jbrown            #+#    #+#              #
#    Updated: 2022/09/05 12:06:57 by jbrown           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	cub3d

################################################################################
#								DIRECTORIES									   #
################################################################################
BUILDIR	=	./build
HDRDIR	=	./headers
LIBDIR	=	./libraries
SRCDIR	=	./sources
IDRDIR	=	./headers/imported

TEMPDIR =	$(BUILDIR) $(IDRDIR)

################################################################################
#								FILES										   #
################################################################################
SOURCES	:=	$(SRCDIR)/main.c \
			$(SRCDIR)/read_map.c \
			$(SRCDIR)/exit.c \
			$(SRCDIR)/draw_map.c \
			$(SRCDIR)/draw_line.c \
			$(SRCDIR)/map_errors.c \

IMPHDR	:=	$(LIBDIR)/libft/headers/libft.h \
			$(LIBDIR)/mlx/mlx.h

LIB		:=	$(shell find $(LIBDIR) -depth 1 -type d)
OBJECTS	:=	$(SOURCES:$(SRCDIR)/%.c=$(BUILDIR)/%.o)

CLNDIR	:=	$(IDRDIR) $(NAME)
FCLN	:=	$(BUILDIR)

################################################################################
#								COMPILER/FLAGS								   #
################################################################################
CC		=	gcc
COMFLAG	=	-Wall -Wextra -Werror -std=c99 -D_POSIX_C_SOURCE -I $(HDRDIR)

CFLAGS		=	$(COMFLAG) -g
LFLAGS		=	$(COMFLAG)
RLFLAGS 	=	-I/usr/local/opt/readline/include
RLLIB		=	-L/usr/local/opt/readline/lib
MLXFLAGS	=	-framework OpenGL -framework AppKit

################################################################################
#								EXTERNAL UTILITIES							   #
################################################################################
RM		=	rm -rf
MKDIR	=	mkdir -p
CP		=	cp

################################################################################
#								LIBRARIES									   #
################################################################################
L42DIR	=	$(LIBDIR)/libft
GRAPDIR	=	$(LIBDIR)/mlx
LIB42	=	$(L42DIR)/libft.a $(GRAPDIR)/libmlx.a
READLN	=	-lreadline

ALLLIB	=	$(LIB42) $(READLN)

################################################################################
#								COMMANDS									   #
################################################################################
.DELETE_ON_ERROR:

all: dirs libs $(NAME)

dirs:
	@$(MKDIR) $(TEMPDIR)
	@printf "Made directories: %s\n" $(TEMPDIR)

libs:
	@$(CP) $(IMPHDR) $(IDRDIR)
	@$(MAKE) -C $(L42DIR)
	@$(MAKE) -C $(GRAPDIR)
	@printf "Imported header: %s\n" $(IMPHDR)
	@printf "Libraries made: %s\n" $(LIB)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(LFLAGS) $(RLFLAGS) $(RLLIB) $(MLXFLAGS) -o $@ $(ALLLIB)
	@printf "Built program %s successfully\n" $@

$(BUILDIR)/%.o : $(SRCDIR)/%.c
	@$(MKDIR) '$(@D)'
	@$(CC) $(CFLAGS) $(RLFLAGS) -c $< -o $@
	@printf "Linked source: %s into object: %s\n" $< $@

clean:
	@$(RM) $(CLNDIR)
	@printf "Cleaned: %s\n" $(CLNDIR)

fclean: clean
	@$(RM) $(FCLN)
	@printf "Cleaned: %s\n" $(FCLN)

re: fclean all
	@printf "Cleaned and remade all files!\n"

github: #Pushes to Github repo
	@git remote set-url origin git@github.com:alessandroTHFC/cub3d.git
	@clear
	@git add .
	@echo "commit msg"
	@read COMMIT; \
	git commit -m "$$COMMIT"; \
	git push;

42: #Pushes to vogsphere repo
	@git remote set-url origin git@github.com:alessandroTHFC/cub3d.git
	@clear
	@git add .
	@echo "commit msg"
	@read COMMIT; \
	git commit -m "$$COMMIT"; \
	git push;
	@git remote set-url origin git@vogsphere.42adel.org.au:vogsphere/intra-uuid-20be7ca0-6613-40ed-b474-88aec383747c-4368026-apangraz
	git push;