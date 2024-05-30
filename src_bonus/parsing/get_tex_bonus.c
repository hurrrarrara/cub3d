/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq <rjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:30:07 by rjacq             #+#    #+#             */
/*   Updated: 2024/05/30 14:31:10 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

int	print_error(char *str, int error)
{
	ft_fprintf(2, "Error\n%s\n", str);
	return (error);
}

char	*get_path(char *line)
{
	size_t	i;
	size_t	start;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	start = i;
	while (line[i] && line[i] != '\n' && line[i] != ' ')
		i++;
	while (line[i] == ' ' || line[i] == '\n')
	{
		line[i] = '\0';
		i++;
	}
	if (start == i || (line[i] && line[i] != ' ' && line[i] != '\n'))
	{
		ft_fprintf(2, "Error\nBad argument after identifier\n");
		return (NULL);
	}
	return (ft_strdup(&line[start]));
}

int	get_info(char *id, char *line, t_map *map, size_t i)
{
	if ((ft_strncmp(id, "NO", 3) == 0 && map->no) || \
		(ft_strncmp(id, "SO", 3) == 0 && map->so) || \
		(ft_strncmp(id, "WE", 3) == 0 && map->we) || \
		(ft_strncmp(id, "EA", 3) == 0 && map->ea) || \
		(ft_strncmp(id, "F", 2) == 0 && map->f) || \
		(ft_strncmp(id, "C", 2) == 0 && map->c))
		return (print_error("Duplicate identifier", 0));
	if (ft_strncmp(id, "NO", 3) == 0)
		map->no = get_path(&line[i + 2]);
	else if (ft_strncmp(id, "SO", 3) == 0)
		map->so = get_path(&line[i + 2]);
	else if (ft_strncmp(id, "WE", 3) == 0)
		map->we = get_path(&line[i + 2]);
	else if (ft_strncmp(id, "EA", 3) == 0)
		map->ea = get_path(&line[i + 2]);
	else if (ft_strncmp(id, "F", 2) == 0)
		map->f = get_color(&line[i + 1]);
	else if (ft_strncmp(id, "C", 2) == 0)
		map->c = get_color(&line[i + 1]);
	else if (!line_empty(line))
		return (print_error("Missing or bad identifier", 0));
	if ((ft_strncmp(id, "C", 2) == 0 && !map->c) || \
		(ft_strncmp(id, "F", 2) == 0 && !map->f))
		return (print_error("Invalid color", 0));
	return (1);
}

int	get_tex(int fd, t_map *map)
{
	size_t	i;
	char	*line;
	char	**split;

	line = get_next_line(fd);
	while (line && check_err_tex(map))
	{
		split = ft_split(line, ' ');
		i = 0;
		while (line[i] == ' ')
			i++;
		if (!get_info(split[0], line, map, i))
		{
			free(line);
			free_tab(split);
			return (0);
		}
		free(line);
		free_tab(split);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (1);
}
