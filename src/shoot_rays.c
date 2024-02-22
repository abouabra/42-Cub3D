/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:48:26 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/02 15:03:40 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_h_values(t_ray *ray, t_player *player, float angle, int *x)
{
	float	atan;

	ray->start = (t_point){player->pos.x + GRID_SIZE / 8, player->pos.y
		+ GRID_SIZE / 8};
	ray->angle = angle;
	ray->distance = (float)INT_MAX;
	atan = -1 / tan(ray->angle);
	if (ray->angle > M_PI)
	{
		ray->prespective = NO;
		ray->end.y = round_down(player->pos.y) - 0.001;
		ray->offset.y = -GRID_SIZE;
	}
	if (ray->angle < M_PI)
	{
		ray->prespective = SO;
		ray->end.y = round_down(player->pos.y) + GRID_SIZE;
		ray->offset.y = GRID_SIZE;
	}
	ray->end.x = (player->pos.y - ray->end.y) * atan + player->pos.x;
	ray->offset.x = -ray->offset.y * atan;
	*x = -1;
}

void	init_v_values(t_ray *ray, t_player *player, float angle, int *x)
{
	float	ntan;

	ray->start = (t_point){player->pos.x + GRID_SIZE / 8, player->pos.y
		+ GRID_SIZE / 8};
	ray->distance = (float)INT_MAX;
	ray->angle = angle;
	ntan = -tan(ray->angle);
	if (ray->angle > M_PI_2 && ray->angle < TPI2)
	{
		ray->prespective = WE;
		ray->end.x = round_down(player->pos.x) - 0.001;
		ray->offset.x = -GRID_SIZE;
	}
	if (ray->angle < M_PI_2 || ray->angle > TPI2)
	{
		ray->prespective = EA;
		ray->end.x = round_down(player->pos.x) + GRID_SIZE;
		ray->offset.x = GRID_SIZE;
	}
	ray->end.y = (player->pos.x - ray->end.x) * ntan + player->pos.y;
	ray->offset.y = -ray->offset.x * ntan;
	*x = -1;
}

void	check_ray(t_vars *vars, t_ray *ray, int type)
{
	float	scale;
	float	end;
	int		width;

	(void)vars;
	end = ray->end.x;
	if (type)
		end = ray->end.y;
	scale = 0;
	ray->distance = calc_dist(ray->start, (t_point){ray->end.x, ray->end.y});
	width = 256;
	scale = 256.0 / GRID_SIZE;
	ray->tex.x = fmod(end, GRID_SIZE) * scale;
	if (ray->prespective == SO || ray->prespective == WE)
		ray->tex.x = width - ray->tex.x;
	if (ray->r_type == door_closed)
		ray->tex.x = fmod(end, GRID_SIZE) * ((float)256 / GRID_SIZE);
}

void	shoot_h_ray(t_vars *vars, float ra)
{
	int	x;

	init_h_values(vars->h_ray, vars->player, ra, &x);
	while (++x < vars->map->longest_axis)
	{
		vars->h_ray->map = downscale_fpoint(vars->h_ray->end);
		vars->h_ray->r_type = has_hit_a_wall(vars->map, vars->h_ray->map);
		if (vars->h_ray->r_type > 0)
		{
			check_ray(vars, vars->h_ray, 0);
			break ;
		}
		else
		{
			vars->h_ray->end.x += vars->h_ray->offset.x;
			vars->h_ray->end.y += vars->h_ray->offset.y;
		}
	}
}

void	shoot_v_ray(t_vars *vars, float ra)
{
	int	x;

	init_v_values(vars->v_ray, vars->player, ra, &x);
	while (++x < vars->map->longest_axis)
	{
		vars->v_ray->map = downscale_fpoint(vars->v_ray->end);
		vars->v_ray->r_type = has_hit_a_wall(vars->map, vars->v_ray->map);
		if (vars->v_ray->r_type > 0)
		{
			check_ray(vars, vars->v_ray, 1);
			break ;
		}
		else
		{
			vars->v_ray->end.x += vars->v_ray->offset.x;
			vars->v_ray->end.y += vars->v_ray->offset.y;
		}
	}
}
