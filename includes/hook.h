/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 03:41:36 by ihabiby           #+#    #+#             */
/*   Updated: 2024/05/26 03:41:37 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_H
# define HOOK_H

# include "struct.h"

int		no_event(t_data *data);
int		mouse_move_hook(int x, int y, t_data *data);
int		key_press_hook(int key, t_data *data);
int		key_release_hook(int key, t_data *data);
int		mouse_button_hook(int button, t_rendervars *render_vars, int x, int y);

void	active_pause(t_data *data);

#endif