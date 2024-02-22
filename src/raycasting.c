/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:48:26 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/03 16:32:57 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_draw_textures(t_vars *vars, t_ray *ray, t_sprite *sprite,
		t_pair *loop)
{

	sprite->page_pointer = vars->wall_tiles;
	sprite->sprite_size_on_page = 256;
	sprite->sprite_page_max_x = 6;
	sprite->sprite_page_max_y = 18;
	sprite->id = map_zone_floor_1(ray);
	loop->x = (WINDOW_HEIGHT / 2) - (ray->line_h / 2);
	loop->y = loop->x + ray->line_h;
	if (loop->x < 0)
		loop->x = 0;
}

int	draw_textures_bonus(t_ray *ray, t_sprite *sprite, t_pair *loop, int y)
{
	float	scale;
	int		hex;
	t_pair	pos;

	hex = 0;
	scale = sprite->sprite_size_on_page;
	ray->tex.y = (1.0 - ((float)(loop->y - y) / ray->line_h)) * scale;
	pos = (t_pair){ray->tex.x, ray->tex.y};
	hex = get_sprite_from_pos(sprite, pos);
	if (ray->r_type == door_closed)
	{
		sprite->id = 28;
		hex = get_sprite_from_pos(sprite, pos);
	}
	return (hex);
}

void	draw_textures(t_vars *vars, t_ray *ray, int x)
{
	t_point		loop;
	int			y;
	int			hex;
	t_sprite	sprite;

	init_draw_textures(vars, ray, &sprite, &loop);
	y = loop.x - 1;
	while (++y < loop.y && y < WINDOW_HEIGHT)
	{
		hex = draw_textures_bonus(ray, &sprite, &loop, y);
		if (hex)
			mlx_put_pixel(vars->scene_img, x, y, hex);
	}
}

void	raycasting_init(t_vars *vars, float *ra, float *angle_between_ray)
{
	*angle_between_ray = (FOV * M_PI / 180) / WINDOW_WIDTH;
	*ra = vars->player->angle - ((float)FOV / 2) * (M_PI / 180)
		+ *angle_between_ray * 0.5;
	*ra = normalize_values(*ra);
}

void	raycasting(t_vars *vars)
{
	float	ra;
	float	angle_between_ray;
	t_ray	*ray;
	int		i;

	raycasting_init(vars, &ra, &angle_between_ray);
	ray = NULL;
	i = -1;
	while (++i < WINDOW_WIDTH)
	{
		shoot_h_ray(vars, ra);
		shoot_v_ray(vars, ra);
		pick_shortest_ray(vars, &ray);
		draw_ray_in_minimap(vars, ray);
		fix_fish_eye(vars, ray, ra, i);
		set_line_height(ray);
		draw_textures(vars, ray, i);
		draw_ceiling(vars, ray, i);
		draw_floor(vars, ray, i);
		ra += angle_between_ray;
		ra = normalize_values(ra);
	}
}
