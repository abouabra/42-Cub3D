/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:39:27 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/03 16:19:56 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_single_grid(t_player *player, mlx_image_t *image, t_point pos,
		int color)
{
	t_point	p;
	int		scale;
	t_point	point;
	t_point	d_p;
	t_point	index;

	scale = GRID_SIZE / MINIMAP_SCALE;
	p = (t_point){pos.x * scale, pos.y * scale};
	index.y = p.y - 1;
	while (++index.y < p.y + scale)
	{
		index.x = p.x - 1;
		while (++index.x < p.x + scale)
		{
			point = (t_point){index.x, index.y};
			d_p = (t_point){player->pos.x / MINIMAP_SCALE, player->pos.y
				/ MINIMAP_SCALE};
			if (index.y == p.y || index.y == p.y + GRID_SIZE / MINIMAP_SCALE
				|| index.x == p.x || index.x == p.x + GRID_SIZE / MINIMAP_SCALE)
				mlx_put_pixel_on_minimap(image, point, d_p, 0x000000FF);
			else
				mlx_put_pixel_on_minimap(image, point, d_p, color);
		}
	}
}

void	draw_circle_on_minimap(t_player *player, mlx_image_t *image,
		size_t color)
{
	t_point	start;
	t_point	point;
	t_point	dp;
	t_point	delta;
	t_point	index;

	start.x = player->pos.x / MINIMAP_SCALE - MINIMAP_RADIUS;
	start.y = player->pos.y / MINIMAP_SCALE - MINIMAP_RADIUS;
	index.y = start.y - 1;
	while (++index.y < start.y + MINIMAP_RADIUS * 2)
	{
		index.x = start.x - 1;
		while (++index.x < start.x + MINIMAP_RADIUS * 2)
		{
			point = (t_point){index.x, index.y};
			dp = (t_point){player->pos.x / MINIMAP_SCALE, player->pos.y
				/ MINIMAP_SCALE};
			delta = (t_point){index.x - player->pos.x / MINIMAP_SCALE, index.y
				- player->pos.y / MINIMAP_SCALE};
			if (delta.x * delta.x + delta.y * delta.y > (MINIMAP_RADIUS - 2)
				* (MINIMAP_RADIUS - 2))
				mlx_put_pixel_on_minimap(image, point, dp, color);
		}
	}
}

void	draw_player_on_minimap(t_vars *vars, mlx_image_t *image, t_point pos,
		size_t color)
{
	int		player_grid;
	t_point	point;
	t_point	index;
	t_point	dp;

	player_grid = GRID_SIZE / MINIMAP_SCALE / 4;
	index.y = pos.y / MINIMAP_SCALE;
	while (++index.y < pos.y / MINIMAP_SCALE + player_grid)
	{
		index.x = pos.x / MINIMAP_SCALE;
		while (++index.x < pos.x / MINIMAP_SCALE + player_grid)
		{
			point = (t_point){index.x, index.y};
			dp = (t_point){vars->player->pos.x / MINIMAP_SCALE + player_grid
				/ 2, vars->player->pos.y / MINIMAP_SCALE + player_grid / 2};
			mlx_put_pixel_on_minimap(image, point, dp, color);
		}
	}
}

void	draw_minimap_grids(t_vars *vars, t_map *map, mlx_image_t *image)
{
	t_point	idx;
	t_point	pos;

	idx.y = -1;
	while (map->map[++idx.y])
	{
		idx.x = -1;
		while (map->map[idx.y][++idx.x])
		{
			pos = (t_point){idx.x, idx.y};
			if (map->map[idx.y][idx.x] == '1')
				draw_single_grid(vars->player, image, pos, 0xFFFFFFFF);
			else if (map->map[idx.y][idx.x] == 'C')
				draw_single_grid(vars->player, image, pos, 0x181818FF);
			else if (map->map[idx.y][idx.x] == 'O')
				draw_single_grid(vars->player, image, pos, 0xFFFFFFAA);
		}
	}
}

void	draw_minimap(t_vars *vars)
{
	draw_minimap_grids(vars, vars->map, vars->minimap_img);
	draw_player_on_minimap(vars, vars->minimap_img,
		vars->player->pos, 0xFFFFFFFF);
	draw_circle_on_minimap(vars->player, vars->minimap_img, 0xFFFFFFFF);
	draw_fps(vars);
}
