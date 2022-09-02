# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 16:30:35 by Nathanael         #+#    #+#              #
#    Updated: 2022/09/02 11:32:56 by jbrown           ###   ########.fr        #
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
SOURCES	:=	\

IMPHDR	:=	$(LIBDIR)/libft/headers/libft.h

LIB		:=	$(shell find $(LIBDIR) -depth 1 -type d)
OBJECTS	:=	$(SOURCES:$(SRCDIR)/%.c=$(BUILDIR)/%.o)

CLNDIR	:=	$(IDRDIR) $(NAME)
FCLN	:=	$(BUILDIR)

################################################################################
#								COMPILER/FLAGS								   #
################################################################################
CC		=	gcc
COMFLAG	=	-Wall -Wextra -Werror -std=c99 -D_POSIX_C_SOURCE -I $(HDRDIR)

CFLAGS	=	$(COMFLAG) -g
LFLAGS	=	$(COMFLAG)
RLFLAGS =	-I/usr/local/opt/readline/include
RLLIB	=	-L/usr/local/opt/readline/lib

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
LIB42	=	$(L42DIR)/libft.a
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
	@printf "Imported header: %s\n" $(IMPHDR)
	@printf "Libraries made: %s\n" $(LIB)

$(NAME): $(OBJECTS)
	@$(CC) $(OBJECTS) $(LFLAGS) $(RLFLAGS) $(RLLIB) -o $@ $(ALLLIB)
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
	@git remote set-url origin https://github.com/alessandroTHFC/cub3d.git
	@clear
	@git add .
	@echo "commit msg"
	@read COMMIT; \
	git commit -m "$$COMMIT"; \
	git push;

42: #Pushes to vogsphere repo
	@git remote set-url origin https://github.com/alessandroTHFC/cub3d.git
	@clear
	@git add .
	@echo "commit msg"
	@read COMMIT; \
	git commit -m "$$COMMIT"; \
	git push;
	@git remote set-url origin git@vogsphere.42adel.org.au:vogsphere/intra-uuid-20be7ca0-6613-40ed-b474-88aec383747c-4368026-apangraz
	git push;