/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:48:26 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/02 11:16:46 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	calc_dist(t_point start, t_point end)
{
	double	a;
	double	b;
	double	c;

	a = end.x - start.x;
	b = end.y - start.y;
	c = sqrt((a * a) + (b * b));
	return (c);
}

int	rgba(int r, int g, int b, int a)
{
	int	hex_color;

	hex_color = (b << 24 | g << 16 | r << 8 | a);
	return (hex_color);
}

int	round_down(int num)
{
	int	rem;

	rem = num % GRID_SIZE;
	return (num - rem);
}

int	has_hit_a_wall(t_map *map, t_point point)
{
	if (point.x >= 0 && point.x < map->size.x && point.y >= 0
		&& point.y < map->size.y)
	{
		if (map->map[point.y][point.x] == 'O')
			return (door_opened);
		else if (map->map[point.y][point.x] == 'C')
			return (door_closed);
		else if (map->map[point.y][point.x] == '1')
			return (wall);
	}
	return (space);
}

void	pick_shortest_ray(t_vars *vars, t_ray **ray)
{
	if (!*ray)
		*ray = vars->v_ray;
	if (vars->v_ray->distance < vars->h_ray->distance)
		*ray = vars->v_ray;
	else if (vars->v_ray->distance > vars->h_ray->distance)
		*ray = vars->h_ray;
}
