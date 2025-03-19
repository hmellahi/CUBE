/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validiting_infos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 02:35:16 by marvin            #+#    #+#             */
/*   Updated: 2021/01/23 15:58:37 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void		validate_args(t_string **args, int nargs, int signal)
{
	int i;

	i = 0;
	while ((*args)[i])
	{
		(*args)[i] = trim((*args)[i], " ");
		if (!isnumber((*args)[i]))
			return (handle_error(signal, FAIL));
		i++;
	}
	if (nargs != i)
		return (handle_error(signal, FAIL));
}

void		check_for_info(t_string line)
{
	char		str[100];

	if (*line == 'R')
		read_resolution(line);
	else if (line[0] == 'N')
		read_image(line, north_texture);
	else if (ft_strlen(line) >= 2 && line[0] == 'S' && line[1] == 'O')
		read_image(line, south_texture);
	else if (line[0] == 'W')
		read_image(line, east_texture);
	else if (line[0] == 'E')
		read_image(line, west_texture);
	else if (line[0] == 'S' && line[1] != 'O')
		read_image(line, sprite_texture);
	else if (line[0] == 'F')
		read_color(line, floor_color, ground);
	else if (line[0] == 'C')
		read_color(line, ceil_color, skybox);
	else if (!ft_strchr("\n", line[0]))
	{
		sprintf(str, "Invalid identifier |%c|", line[0]);
		return (handle_error2(str, FAIL));
	}
}

t_string	is_info_full(int n)
{
	int i;

	i = -1;
	while (++i <= n)
		if (g_infos[i] == 0)
			return (g_infos_names[i]);
	return (NULL);
}

void		update_col_name(t_string line)
{
	g_world.cols = max((int)ft_strlen(line), g_world.cols);
	g_infos[map] = 1;
}
