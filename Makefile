NAME = raycast

IDIR	:= ./includes/
SDIR	:= ./src/
ODIR	:= ./obj/
MLXDIR	:= ./mlx/


# ERROR_ODIR		:= $(ODIR)error/
# FREE_ODIR		:= $(ODIR)free/
# IMAGE_ODIR		:= $(ODIR)image/
INIT_ODIR		:= $(ODIR)init/
# MATH_UTILS_ODIR	:= $(ODIR)math_utils/
# MLX_UTILS_ODIR	:= $(ODIR)mlx_utils/
# OBJECTS_ODIR	:= $(ODIR)objects/
# PROJECTION_ODIR	:= $(ODIR)projection/
# RASTER_ODIR		:= $(ODIR)raster/
# VERTEX_ODIR		:= $(ODIR)vertex/
# EVENTS_ODIR		:= $(ODIR)events/
# CAMERA_ODIR		:= $(ODIR)camera/
# POST_ODIR		:= $(ODIR)post_render/
PARSER_ODIR			:= $(ODIR)parser/
MINIMAP_ODIR		:= $(ODIR)minimap/
RAYCAST_ODIR		:= $(ODIR)raycast/
HOOK_ODIR			:= $(ODIR)hook/

CC		:= cc
DEBUG	:= #-fsanitize=address
CFLAGS	:= $(DEBUG) -O3 #-g3 #-Wall -Werror -Wextra
LFLAGS	:= -L$(MLXDIR) -lmlx_Linux -lm  -lX11 -lXext
IFLAGS	:= -I$(IDIR) -I$(MLXDIR) -I./fast_obj

# draw		:= draw_object draw_triangle

# error		:= error_handler

# free		:= free_objects free_vertices

# image		:= create_image pixel_to_image

init		:= init_data init_image init_hook

# math_utils	:= mat4 vec4 rotation interpolate

# mlx_utils	:= pixel_get pixel_put xpm_to_image

# objects		:= create_cube create_plan

# projection	:= perspective_matrix project_vertex near_plan_clipping project_triangle

# raster		:= rasterization rasterization_light

# vertex		:= create_vertex

# camera		:= world_to_cam

# events		:= key_events move_event no_events rotate_event mouse_events

# post		:= post_rendering

parser		:= parser

minimap		:= draw_minimap

raycast		:= raycast

hook		:= key_hook mouse_hook no_event

main		:= main

includes	:= define.h struct.h parser.h init.h hook.h

# DRAW_O			= $(addprefix $(DRAW_ODIR), $(addsuffix .o, $(draw)))
# ERROR_O			= $(addprefix $(ERROR_ODIR), $(addsuffix .o, $(error)))
# FREE_O			= $(addprefix $(FREE_ODIR), $(addsuffix .o, $(free)))
# IMAGE_O			= $(addprefix $(IMAGE_ODIR), $(addsuffix .o, $(image)))
INIT_O			= $(addprefix $(INIT_ODIR), $(addsuffix .o, $(init)))
# MATH_UTILS_O	= $(addprefix $(MATH_UTILS_ODIR), $(addsuffix .o, $(math_utils)))
# MLX_UTILS_O		= $(addprefix $(MLX_UTILS_ODIR), $(addsuffix .o, $(mlx_utils)))
# OBJECTS_O		= $(addprefix $(OBJECTS_ODIR), $(addsuffix .o, $(objects)))
# PROJECTION_O	= $(addprefix $(PROJECTION_ODIR), $(addsuffix .o, $(projection)))
# RASTER_O		= $(addprefix $(RASTER_ODIR), $(addsuffix .o, $(raster)))
# VERTEX_O		= $(addprefix $(VERTEX_ODIR), $(addsuffix .o, $(vertex)))
# EVENTS_O		= $(addprefix $(EVENTS_ODIR), $(addsuffix .o, $(events)))
# CAMERA_O		= $(addprefix $(CAMERA_ODIR), $(addsuffix .o, $(camera)))
# POST_O			= $(addprefix $(POST_ODIR), $(addsuffix .o, $(post)))
PARSER_O		= $(addprefix $(PARSER_ODIR), $(addsuffix .o, $(parser)))
MINIMAP_O		= $(addprefix $(MINIMAP_ODIR), $(addsuffix .o, $(minimap)))
RAYCAST_O		= $(addprefix $(RAYCAST_ODIR), $(addsuffix .o, $(raycast)))
HOOK_O		= $(addprefix $(HOOK_ODIR), $(addsuffix .o, $(hook)))

MAIN_O			= $(addprefix $(ODIR), $(addsuffix .o, $(main)))

# FAST_OBJ_O		= ./fast_obj/fast_obj.o
# FAST_OBJ_H		= ./fast_obj/

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