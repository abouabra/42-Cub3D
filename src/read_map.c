/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:48:26 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/03 16:40:46 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*read_map(t_vars *vars, int fd)
{
	char	*total;
	char	*line;
	int		tracker;
	int		start;

	tracker = 0;
	start = 0;
	total = "";
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		inside_map_check(vars, line, &tracker, &start);
		if (ft_isdigit(ft_strtrim(line, " \t")[0]))
			vars->map->size.y++;
		total = ft_strjoin(total, line);
	}
	close(fd);
	return (total);
}

void	init_player(t_vars *vars, t_point point, int ang, int *rep)
{
	if (ang < 4)
	{
		(*rep)++;
		vars->hud->selected_gun = 1;
		vars->hud->slots[0] = 1;
		vars->hud->slots[1] = 1;
		vars->player->pos.x = point.x * GRID_SIZE + GRID_SIZE / 2;
		vars->player->pos.y = point.y * GRID_SIZE + GRID_SIZE / 2;
		vars->player->angle = ang * M_PI_2 + 0.00069;
		vars->player->initial_pos = vars->player->pos;
		vars->player->initial_angle = vars->player->angle;
		vars->hud->hp = 100;
		vars->hud->lives = 3;
		vars->hud->ammo = 15;
		vars->hud->floor = 1;
		vars->map->map[point.y][point.x] = '0';
	}
}
