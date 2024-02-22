/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_zones.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:48:26 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/03 16:37:59 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	map_zone_floor_3(t_ray *ray, t_point dp)
{
	int	id;

	id = 0;
	if ((dp.y >= 0 && dp.y <= 21 && dp.x >= 28 && dp.x <= 45) || (dp.y >= 14
			&& dp.y <= 19 && dp.x >= 27 && dp.x <= 39))
	{
		id = 23;
		if (ray->prespective == NO || ray->prespective == WE)
			id = 22;
		if (dp.y == 21 && (dp.x - 1) % 2 == 0)
			id = 18;
	}
	if (dp.y == 30 && (dp.x == 28 || dp.x == 39) && ray->prespective == SO)
		id = 7;
	if (dp.y == 22 && (dp.x == 30 || dp.x == 38) && ray->prespective == NO)
		id = 4;
	if ((dp.x == 26 || dp.x == 42) && dp.y % 4 == 0)
	{
		id = 11;
		if (ray->prespective == NO || ray->prespective == WE)
			id = 10;
	}
	return (id);
}

int	map_zone_floor_2(t_ray *ray, t_point dp)
{
	int	id;

	id = 0;
	if (dp.y == 56 && (dp.x - 1) % 3 == 0)
	{
		id = 8;
		if (dp.x == 34)
			id = 12;
		if (ray->prespective == SO || ray->prespective == EA)
			id += 1;
	}
	if ((dp.x == 62 && dp.y == 26) || (dp.x == 60 && dp.y == 37))
	{
		id = 8;
		if (ray->prespective == SO || ray->prespective == EA)
			id += 1;
	}
	return (id);
}

int	map_zone_floor_1(t_ray *ray)
{
	int		id;
	int		tmp;
	t_point	dp;

	id = ray->prespective;
	dp = (t_point){ray->end.x / GRID_SIZE, ray->end.y / GRID_SIZE};
	if ((dp.y >= 31 && dp.y <= 56 && dp.x >= 27 && dp.x <= 41) || (dp.y >= 21
			&& dp.y <= 40 && dp.x >= 43 && dp.x <= 63))
	{
		id = ray->prespective + 14;
		tmp = map_zone_floor_2(ray, dp);
		if (tmp)
			id = tmp;
	}
	tmp = map_zone_floor_3(ray, dp);
	if (tmp)
		id = tmp;
	return (id);
}
