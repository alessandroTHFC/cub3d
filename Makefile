# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrown <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/02 11:38:42 by jbrown            #+#    #+#              #
#    Updated: 2022/09/24 19:42:24 by jbrown           ###   ########.fr        #
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

UNAME	=	$(shell uname)

################################################################################
#								FILES										   #
################################################################################

ifeq ($(UNAME), Linux)
MLX_FLAGS = -L/usr/lib -Ilibraries/mlx -lXext -lX11 -lm -lz
MLX_MACRO =	$(HDRDIR)/linux/macros.h
else
MLX_FLAGS = -framework OpenGL -framework AppKit
MLX_MACRO =	$(HDRDIR)/macos/macros.h
endif

SOURCES	:=	$(SRCDIR)/main.c \
			$(SRCDIR)/read_map.c \
			$(SRCDIR)/exit.c \
			$(SRCDIR)/player/player_movement.c \
			$(SRCDIR)/player/player_collision.c \
			$(SRCDIR)/hooks.c \
			$(SRCDIR)/drawing/draw_line.c \
			$(SRCDIR)/drawing/draw_map.c \
			$(SRCDIR)/drawing/draw_background.c \
			$(SRCDIR)/init/init_player.c \
			$(SRCDIR)/init/mlx_init.c \
			$(SRCDIR)/error/ft_splice.c \
			$(SRCDIR)/error/map_errors.c \
			$(SRCDIR)/error/map_errors2.c \
			$(SRCDIR)/rays/raycaster.c \
			$(SRCDIR)/rays/draw_ray.c \
			$(SRCDIR)/rays/projection.c \
			$(SRCDIR)/utils/utils.c \
			$(SRCDIR)/utils/colours.c \
			
IMPHDR	:=	$(LIBDIR)/libft/headers/libft.h \
			$(LIBDIR)/mlx/mlx.h \
			$(LIBDIR)/mlx/mlx_int.h \
			$(MLX_MACRO)

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
MLX		=	$(LIBDIR)/mlx
LIB42	=	$(L42DIR)/libft.a

ifeq ($(UNAME), Linux)
LIB42	+=	$(MLX)/libmlx_Linux.a
else
LIB42	+=	$(MLX)/libmlx.a
endif

ALLLIB	=	$(LIB42)
################################################################################
#								COMMANDS									   #
################################################################################
.DELETE_ON_ERROR:

all: dirs libs $(NAME)

dirs:
	@$(MKDIR) $(TEMPDIR)
	@printf "Made directories: %s\n" $(TEMPDIR)

libs: $(MLX)
	@$(CP) $(IMPHDR) $(IDRDIR)
	@$(MAKE) -C $(L42DIR)
	@printf "Imported header: %s\n" $(IMPHDR)
	@printf "Libraries made: %s\n" $(LIB)

$(NAME): $(OBJECTS)
	@printf "$(UNAME) \n"
	$(CC) -I ./headers/imported $(OBJECTS) $(ALLLIB) $(LFLAGS) $(MLX_FLAGS) -o $@
	@printf "Built program %s successfully\n" $@

$(BUILDIR)/%.o : $(SRCDIR)/%.c
	@$(MKDIR) '$(@D)'
	@$(CC) $(CFLAGS) $(MLXFLAGS) -c $< -o $@
	@printf "Linked source: %s into object: %s\n" $< $@

$(MLX):
	@printf "mlx dependency needed. Download now? [y/N]"
	@read ans && [ $${ans:-N} = y ]
	@if [ $(UNAME) != Linux ]; then \
		git clone https://github.com/dannywillems/minilibx-mac-osx.git $(MLX); \
		cp -r $(MLX)mlx.h $(HDR_DIR); \
		cp -r $(MLX)libmlx.a $(ARCH_DIR); \
	else \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX); \
		cd $(MLX) && bash configure >/dev/null;\
		cd ../..; \
	fi

clean:
	@$(RM) $(CLNDIR)
	@printf "Cleaned: %s\n" $(CLNDIR)

fclean: clean
	@$(RM) $(FCLN)
	@printf "Cleaned: %s\n" $(FCLN)

re: fclean all
	@printf "Cleaned and remade all files!\n"

github: fclean #Pushes to Github repo
	@git remote set-url origin git@github.com:alessandroTHFC/cub3d.git
	@clear
	@git add .
	@echo "commit msg"
	@read COMMIT; \
	git commit -m "$$COMMIT"; \
	git push;

42: fclean #Pushes to vogsphere repo
	@git remote set-url origin git@github.com:alessandroTHFC/cub3d.git
	@clear
	@git add .
	@echo "commit msg"
	@read COMMIT; \
	git commit -m "$$COMMIT"; \
	git push;
	@git remote set-url origin git@vogsphere.42adel.org.au:vogsphere/intra-uuid-20be7ca0-6613-40ed-b474-88aec383747c-4368026-apangraz
	git push;