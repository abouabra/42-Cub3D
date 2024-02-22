/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceiling_floor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:48:26 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/02 12:16:15 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_ray_in_minimap(t_vars *vars, t_ray *ray)
{
	t_point	start;
	t_point	end;
	t_line	line;

	start.x = vars->player->pos.x / MINIMAP_SCALE;
	start.y = vars->player->pos.y / MINIMAP_SCALE;
	end.x = ray->end.x / MINIMAP_SCALE;
	end.y = ray->end.y / MINIMAP_SCALE;
	line = (t_line){start, end, 0xFF0000FF};
	draw_line_on_minimap(vars->minimap_img, line, start);
}

void	set_line_height(t_ray *ray)
{
	ray->line_h = WINDOW_HEIGHT / ray->distance * 100;
	if (ray->line_h < 0)
		ray->line_h = 0;
}

void	fix_fish_eye(t_vars *vars, t_ray *ray, float ra, int x)
{
	float	fish_eye;

	fish_eye = vars->player->angle - ra;
	normalize_values(fish_eye);
	ray->distance = ray->distance * cos(fish_eye);
	vars->dists[x] = ray->distance;
}

void	draw_ceiling(t_vars *vars, t_ray *ray, int x)
{
	t_point	celling_start;
	t_point	celling_end;
	int		hex;
	t_line	line;

	celling_start.x = x;
	celling_start.y = 0;
	if (ray->line_h > WINDOW_HEIGHT)
		ray->line_h = WINDOW_HEIGHT;
	celling_end.x = x;
	celling_end.y = (WINDOW_HEIGHT / 2) - (ray->line_h / 2);
	hex = rgba(vars->map->map_colors[C][B], vars->map->map_colors[C][G],
			vars->map->map_colors[C][R], 255);
	line = (t_line){celling_start, celling_end, hex};
	draw_line(vars->scene_img, line);
}

void	draw_floor(t_vars *vars, t_ray *ray, int x)
{
	t_point	floor_start;
	t_point	floor_end;
	int		celling_end;
	int		hex;
	t_line	line;

	if (ray->line_h > WINDOW_HEIGHT)
		ray->line_h = WINDOW_HEIGHT;
	celling_end = (WINDOW_HEIGHT / 2) - (ray->line_h / 2);
	floor_start.x = x;
	floor_start.y = celling_end + ray->line_h;
	floor_end.x = x;
	floor_end.y = WINDOW_HEIGHT;
	hex = rgba(vars->map->map_colors[F][B], vars->map->map_colors[F][G],
			vars->map->map_colors[F][R], 255);
	line = (t_line){floor_start, floor_end, hex};
	draw_line(vars->scene_img, line);
}
