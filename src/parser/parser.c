#include "struct.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

t_bool	get_map_width_height(t_map *map, const char *file)
{
	const int	fd = open(file, O_RDONLY);
	char		c;
	uint16_t	cur_width;

	if (fd < 0)
		return (FALSE);
	cur_width = 0;
	read(fd, &c, 1);
	while (c)
	{
		map->height += (c == '\n' && cur_width != 0);
		map->width = map->width * (map->width >= cur_width) + cur_width * (cur_width > map->width);
		cur_width = (cur_width + 1 );
		cur_width = cur_width * (c != '\n');
		if (read(fd, &c, 1) <= 0)
			break ;
	}
	map->height++;
	close(fd);
	return (TRUE);
}

t_bool	parser(t_map *map, const char *file)
{
	const int	fd = open(file, O_RDONLY);
	char		c;
	uint32_t	i;

	if (fd < 0 || !get_map_width_height(map, file))
		return (FALSE);
	map->map = calloc(map->width * map->height, sizeof(uint8_t));
	if (!map->map)
		return (FALSE);
	map->allocated = map->width * map->height;
	read(fd, &c, 1);
	i = 0;
	while (c && i < map->allocated)
	{
		if (c != ' ' && c != '\n')
			map->map[i] = c - '0' + 1;
		i += (c != '\n') + ((map->width - ((i - 1) % map->width) -1) * (c == '\n'));
		if (read(fd, &c, 1) <= 0)
			break ;
	}
	close(fd);
	return (TRUE);
}
