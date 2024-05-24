/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:00:14 by ihabiby           #+#    #+#             */
/*   Updated: 2024/05/24 17:00:15 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "struct.h"

t_bool	init_data(t_data *data);
void	init_hook(t_data *data);

t_bool	xpm_to_image(t_data *data, t_img *img, const char *texture_path);
t_bool	init_image(\
	const t_data *data, \
	t_img *img, \
	const uint32_t width, \
	const uint32_t height);

t_bool	reverse_img(t_img *img);

#endif