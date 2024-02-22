/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 02:34:44 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/02 20:23:44 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_sprites_y(t_vars *vars, t_sprite *sprite, t_pair loop_i)
{
	t_pair	loop_j;
	t_pair	pos;
	int		hex;

	loop_j = (t_pair){sprite->off.y - 1, sprite->tex_size + sprite->off.y};
	while (++loop_j.x < loop_j.y && vars->dists[loop_i.x] > sprite->dist)
	{
		sprite->tex.y = (float)(loop_j.x - sprite->off.y) / sprite->tex_size
			* sprite->sprite_size_on_page;
		if (loop_j.x >= 0 && loop_j.x < WINDOW_HEIGHT)
		{
			pos = (t_pair){sprite->tex.x, sprite->tex.y};
			hex = get_sprite_from_pos(sprite, pos);
			if (hex)
				mlx_put_pixel(vars->scene_img, loop_i.x, loop_j.x, hex);
		}
	}
}

void	draw_sprites(t_vars *vars, t_sprite *sprite)
{
	t_pair	loop_i;

	loop_i = (t_pair){sprite->off.x - 1, sprite->tex_size + sprite->off.x};
	while (++loop_i.x < loop_i.y)
	{
		sprite->tex.x = (float)(loop_i.x - sprite->off.x) / sprite->tex_size
			* sprite->sprite_size_on_page;
		if (loop_i.x >= 0 && loop_i.x < WINDOW_WIDTH)
		{
			draw_sprites_y(vars, sprite, loop_i);
		}
	}
}

void	configure_sprite_2(t_sprite *sprite, float angle)
{
	float	scale;
	float	height;
	float	size;
	float	perc;

	scale = 100 / sprite->dist;
	height = (WINDOW_HEIGHT / sprite->dist) * scale;
	size = 512.0f;
	if (sprite->type == enemy)
		size = 1024.0f;
	sprite->tex_size = size * scale;
	perc = ((float)(WINDOW_WIDTH - sprite->tex_size) / WINDOW_WIDTH) * 50;
	sprite->off.x = (angle * (180.0f / M_PI) * (90.0f / FOV) + perc)
		* WINDOW_WIDTH / 100;
	if (sprite->type != enemy)
		sprite->off.y = (int)(WINDOW_HEIGHT / 2) - (height / 2);
	else if (sprite->type == enemy)
		sprite->off.y = (int)(WINDOW_HEIGHT / 2) - (sprite->tex_size / 2);
}

void	configure_sprite(t_vars *vars, t_sprite *sprite)
{
	t_fpair	delta;
	float	angle;

	delta.x = sprite->pos.x - vars->player->pos.x;
	delta.y = sprite->pos.y - vars->player->pos.y;
	sprite->angle = atan2(delta.y, delta.x);
	if (sprite->angle < vars->player->angle - M_PI)
		sprite->angle += 2 * M_PI;
	else if (sprite->angle > vars->player->angle + M_PI)
		sprite->angle -= 2 * M_PI;
	angle = sprite->angle - vars->player->angle;
	sprite->dist = sqrt(delta.x * delta.x + delta.y * delta.y);
	sprite->dist = sprite->dist + cos(angle);
	configure_sprite_2(sprite, angle);
}

void	sprites(t_vars *vars)
{
	t_sprite	*sprite;
	int			index;

	index = get_clock_index(vars);
	sprite = vars->sprites;
	while (sprite)
	{
		set_sprite_id(vars, sprite, index);
		sprite = sprite->next;
	}
	sort_sprites(vars);
	sprite = vars->sprites;
	while (sprite)
	{
		draw_sprites(vars, sprite);
		enemy_movement(vars, sprite);
		sprite = sprite->next;
	}
	detect_coalition(vars);
	draw_gun_on_screen(vars, vars->hud->selected_gun * 5);
}
