/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:00:19 by ihabiby           #+#    #+#             */
/*   Updated: 2024/05/26 03:42:35 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_BONUS_H
# define DEFINE_BONUS_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define MINIMAP_WIDTH 400
# define MINIMAP_HEIGHT 300
# define MINIMAP_CUB_WIDTH 20
# define PLAYER_WIDTH 5
# define MINIMAP_PLAYER_POS (MINIMAP_WIDTH / 2) + ((MINIMAP_HEIGHT / 2) - (PLAYER_WIDTH / 2)) * MINIMAP_WIDTH

# define MOVE_SPEED 0.1
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
# define PLAYER_COLOR 0xff0000

# define CUB_HEIGHT 2048
# define CUB_SCAL 80.0f
# define ANIM_OFFSET 549

# define DOOR_NOTIF "./textures/door.xpm"
# define PAUSE_SCREEN "./textures/pause.xpm"
# define DOOR_TEXT "./textures/animated.xpm"

# define ERROR_MLX_MSG "MLX"

#endif