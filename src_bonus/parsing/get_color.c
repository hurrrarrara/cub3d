/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:25:15 by rjacq             #+#    #+#             */
/*   Updated: 2024/05/26 03:33:34 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

char	ft_atouc(char *str)
{
	size_t			i;
	unsigned char	res;

	i = 0;
	res = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res);
}

size_t	ft_nblen(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		i++;
		count++;
	}
	return (count);
}

int	fill_color(char *line, unsigned char *color, size_t *count, size_t *i)
{
	size_t	s;
	char	*o;

	while (line[*i] && line[*i] == ' ')
		(*i)++;
	s = *i;
	while (line[*i] >= '0' && line[*i] <= '9')
		(*i)++;
	while (line[*i] && line[*i] == ' ' && *i != s)
		(*i)++;
	if (*count == 2 && line[*i] == ',')
		return (0);
	else if ((line[*i] == ',' || line[*i] == '\n') && *i != s)
		(*i)++;
	else
		return (0);
	if (*count < 3)
	{
		color[*count] = ft_atouc(&line[s]);
		o = ft_itoa(color[*count]);
		if (ft_strncmp(o, &line[s], ft_nblen(&line[s])) != 0)
			return (0);
		free(o);
	}
	return (1);
}

void	*get_color(char *line)
{
	size_t			i;
	size_t			count;
	unsigned char	*color;

	color = malloc(sizeof (char) * 3);
	if (!color)
		return (NULL);
	i = 0;
	count = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!fill_color(line, color, &count, &i))
		{
			count = 0;
			break ;
		}
		count++;
	}
	if (count != 3)
	{
		free(color);
		color = NULL;
	}
	return (color);
}
