/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjacq <rjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:21:42 by rjacq             #+#    #+#             */
/*   Updated: 2024/05/30 13:58:42 by rjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include "struct.h"
# include "unistd.h"

int		line_empty(char *line);
int		line_ismap(char *line);
int		check_err_end_file(char *line, int fd);
int		check_err_tex(t_map *map);
int		check_err_extension(char *file);
int		check_err_sides(t_map *map, size_t i, size_t row, size_t col);
int		check_err_map(t_map *map);
int		get_map(int fd, t_map *map);
int		get_tex(int fd, t_map *map);
int		print_error(char *str, int error);
void	*get_color(char *line);
void	free_map(t_map *map);
void	free_tab(char **str);

int		parsing(t_map *map, char **argv);

#endif