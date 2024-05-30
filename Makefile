NAME = cub3d
NAME_BONUS = cub3d_bonus

IDIR	:= ./includes/
SDIR	:= ./src/
ODIR	:= ./obj/

IDIR_BONUS	:= ./includes_bonus/
SDIR_BONUS	:= ./src_bonus/
ODIR_BONUS	:= ./obj_bonus/

MLXDIR		:= ./mlx/
LIBFT_DIR	:= ./libft/


INIT_ODIR			:= init/
PARSER_ODIR			:= parsing/
MINIMAP_ODIR		:= minimap/
RAYCAST_ODIR		:= raycast/
HOOK_ODIR			:= hook/

CC		:= cc
DEBUG	:= -g3 #-fsanitize=address,leak
CFLAGS	:= $(DEBUG) -Wall -Werror -Wextra
LFLAGS	:= -L$(MLXDIR) -L$(LIBFT_DIR) -lmlx_Linux -lm -lft -lX11 -lXext
IFLAGS	:= -I$(IDIR) -I$(MLXDIR) -I$(LIBFT_DIR)

IFLAGS_BONUS := -I$(IDIR_BONUS) -I$(MLXDIR) -I$(LIBFT_DIR)



init		:= init_data init_image init_hook

parser		:= parsing check_file check_line get_tex get_map get_color

minimap		:= draw_minimap

raycast		:= raycast dda draw_line

hook		:= key_hook mouse_hook no_event pause

main		:= main quit math_utils

includes	:= define hook init math_utils minimap quit raycast struct parsing


INIT_O			= $(addprefix $(INIT_ODIR), $(init))
PARSER_O		= $(addprefix $(PARSER_ODIR), $(parser))
MINIMAP_O		= $(addprefix $(MINIMAP_ODIR), $(minimap))
RAYCAST_O		= $(addprefix $(RAYCAST_ODIR), $(raycast))
HOOK_O			= $(addprefix $(HOOK_ODIR), $(hook))

MAIN_O			= $(main)

LIBFT_A	= $(LIBFT_DIR)libft.a
LIBFT_H = $(LIBFT_DIR)libft.h

INCL		= $(addprefix $(IDIR), $(addsuffix .h, $(includes)))
INCL_BONUS	= $(addprefix $(IDIR_BONUS), $(addsuffix _bonus.h, $(includes)))

obj		= $(INIT_O) $(PARSER_O) $(MAIN_O)  $(MINIMAP_O) $(RAYCAST_O) $(HOOK_O)

OBJ		= $(addprefix $(ODIR), $(addsuffix .o, $(obj)))

OBJ_BONUS	= $(addprefix $(ODIR_BONUS), $(addsuffix _bonus.o, $(obj)))

.PHONY: all re clean fclan MLX DIR bonus

all: LIBFT DIR MLX $(NAME)


$(NAME):  $(LIBFT_A) $(LIBFT_H) $(OBJ)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $(OBJ) $(LFLAGS)

$(ODIR)%.o: $(SDIR)%.c Makefile $(INCL)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

DIR:
	mkdir -p $(ODIR)
	mkdir -p $(ODIR)$(INIT_ODIR)
	mkdir -p $(ODIR)$(PARSER_ODIR)
	mkdir -p $(ODIR)$(MINIMAP_ODIR)
	mkdir -p $(ODIR)$(RAYCAST_ODIR)
	mkdir -p $(ODIR)$(HOOK_ODIR)

bonus: LIBFT DIR_BONUS MLX $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT_A) $(LIBFT_H) $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(IFLAGS_BONUS) -o $@ $(OBJ_BONUS) $(LFLAGS)

$(ODIR_BONUS)%.o: $(SDIR_BONUS)%.c Makefile $(INCL_BONUS)
	$(CC) $(CFLAGS) $(IFLAGS_BONUS) -o $@ -c $<

DIR_BONUS:
	echo $(OBJ_BONUS)
	mkdir -p $(ODIR_BONUS)
	mkdir -p $(ODIR_BONUS)$(INIT_ODIR)
	mkdir -p $(ODIR_BONUS)$(PARSER_ODIR)
	mkdir -p $(ODIR_BONUS)$(MINIMAP_ODIR)
	mkdir -p $(ODIR_BONUS)$(RAYCAST_ODIR)
	mkdir -p $(ODIR_BONUS)$(HOOK_ODIR)

MLX:
	cd $(MLXDIR) && ./configure

LIBFT:
	@make -C $(LIBFT_DIR)

clean:
	rm -rf $(ODIR)
	rm -rf $(ODIR_BONUS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	@make -C $(LIBFT_DIR) fclean

re:	fclean all