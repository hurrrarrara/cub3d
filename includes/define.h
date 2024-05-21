#ifndef DEFINE_H
# define DEFINE_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define RENDER_WIDTH 1080
# define RENDER_HEIGHT 1920

# define CAM_WIDTH 1920
# define CAM_HEIGHT 1080
# define CAM_NEAR 0.001

# define MINIMAP_WIDTH 400
# define MINIMAP_HEIGHT 300

# define FLOOR 0xafafaf
# define BLOCK_R 0x0f0000
# define BLOCK_G 0x0000
# define BLOCK_B 0xa2
# define VOID 0

# define TOP 0b1
# define NORTH 0b10
# define EAST 0b100
# define SOUTH 0b1000
# define WEST 0b10000

# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.0005
# define HIT_BOX_SIZE 0.05

# define KEY_FRWD 'w'
# define KEY_BCKWRD 's'
# define KEY_LEFT 'a'
# define KEY_RIGHT 'd'

# define DOOR_OPEN_COLOR 0x00f0ff
# define DOOR_CLOSE_COLOR 0x0faf00
# define WALL_COLOR 0xa000ff
# define FLOOR_COLOR 0xafafaf

# define CUB_HEIGHT 4096
# define ANIM_OFFSET 549

# define NORTH_TEXT "./textures/brick.xpm"
# define SOUTH_TEXT "./textures/brick.xpm"
# define EAST_TEXT "./textures/brick.xpm"
# define WEST_TEXT "./textures/brick.xpm"

# define DOOR_NOTIF "./textures/door.xpm"
# define PAUSE_SCREEN "./textures/pause.xpm"
# define DOOR_TEXT "./textures/animated.xpm"

#endif