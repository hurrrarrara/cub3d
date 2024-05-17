NAME = raycast

IDIR	:= ./includes/
SDIR	:= ./src/
ODIR	:= ./obj/
MLXDIR	:= ./mlx/



INIT_ODIR		:= $(ODIR)init/
PARSER_ODIR			:= $(ODIR)parser/
MINIMAP_ODIR		:= $(ODIR)minimap/
RAYCAST_ODIR		:= $(ODIR)raycast/
HOOK_ODIR			:= $(ODIR)hook/

CC		:= cc
DEBUG	:= #-g3 -fsanitize=address,leak
CFLAGS	:= $(DEBUG) -Wall -Werror -Wextra
LFLAGS	:= -L$(MLXDIR) -lmlx_Linux -lm  -lX11 -lXext
IFLAGS	:= -I$(IDIR) -I$(MLXDIR) -I./fast_obj



init		:= init_data init_image init_hook

parser		:= parser

minimap		:= draw_minimap

raycast		:= raycast dda draw_line

hook		:= key_hook mouse_hook no_event pause

main		:= main quit math_utils

includes	:= define.h struct.h parser.h init.h hook.h


INIT_O			= $(addprefix $(INIT_ODIR), $(addsuffix .o, $(init)))
PARSER_O		= $(addprefix $(PARSER_ODIR), $(addsuffix .o, $(parser)))
MINIMAP_O		= $(addprefix $(MINIMAP_ODIR), $(addsuffix .o, $(minimap)))
RAYCAST_O		= $(addprefix $(RAYCAST_ODIR), $(addsuffix .o, $(raycast)))
HOOK_O		= $(addprefix $(HOOK_ODIR), $(addsuffix .o, $(hook)))

MAIN_O			= $(addprefix $(ODIR), $(addsuffix .o, $(main)))

INCL	= $(addprefix $(IDIR), $(includes))

OBJ		= $(INIT_O) $(PARSER_O) $(MAIN_O)  $(MINIMAP_O) $(RAYCAST_O) $(HOOK_O)

.PHONY: all re clean fclan MLX DIR

all: DIR MLX $(NAME)

$(NAME):  $(OBJ)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $(OBJ) $(LFLAGS)

$(ODIR)%.o: $(SDIR)%.c Makefile $(INCL)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

DIR:
	mkdir -p $(ODIR)
	mkdir -p $(INIT_ODIR)
	mkdir -p $(PARSER_ODIR)
	mkdir -p $(MINIMAP_ODIR)
	mkdir -p $(RAYCAST_ODIR)
	mkdir -p $(HOOK_ODIR)

MLX:
	cd $(MLXDIR) && ./configure

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -f $(NAME)

re:	fclean all