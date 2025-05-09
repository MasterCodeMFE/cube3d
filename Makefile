# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manufern <manufern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/24 10:30:44 by igcastil          #+#    #+#              #
#    Updated: 2025/04/03 15:10:04 by manufern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d
CC = gcc
CCFLAGS = -Wall -Wextra -Werror
SRCDIR = src
OBJDIR = obj
SRC =	main.c \
		check_map_surroundings.c \
		drawing.c \
		free_resources.c \
		get_next_line_utils.c \
		get_next_line.c \
		handlers.c \
		init.c \
		parse_ceiling_floor.c \
		parse_map_file_bis.c \
		parse_map_file_elements.c \
		parse_map_file.c \
		parse_texture_elements.c \
		ray_calculations.c \
		ray_initialization.c \
		ray_processing.c \
		rotate.c \
		texture_selection.c \
		textures.c \
		move.c \
		rotate_aux.c \
		musica.c
		
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

INCLUDE = minilibx-linux/mlx.h inc/get_next_line.h libft/libft.h inc/cub3d.h

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	make -C ./libft
	make -C ./minilibx-linux
	$(CC) $(CCFLAGS) -g3 -o $(NAME) $(OBJS) -Llibft -Lminilibx-linux -lft -lmlx_Linux -lX11 -lXext -lm -lasound



$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CCFLAGS) -g -c -o $@ $<


$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	make fclean -C ./libft
	rm -f $(OBJS)
	make clean -C ./minilibx-linux
	rm -f *SYMDEF*
	rm -f *S_Stor*

fclean: clean
	rm -rf $(NAME) $(OBJDIR)

re: fclean all

.PHONY: all bonus clean fclean re