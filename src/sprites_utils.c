/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:48:26 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/03 15:30:18 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <pthread.h>

int	get_sprite_from_pos(t_sprite *sprite, t_point pos)
{
	t_pair	small;
	t_pair	global;
	int		max;
	int		hex;

	max = sprite->sprite_page_max_x;
	small.x = pos.x;
	small.y = pos.y;
	global.x = sprite->id % max * sprite->sprite_size_on_page + small.x;
	global.y = sprite->id / max * sprite->sprite_size_on_page + small.y;
	hex = get_color_from_pos(sprite->page_pointer, global.x, global.y);
	return (hex);
}

int	get_clock_index(t_vars *vars)
{
	static int	index;

	if (vars->clock % 5 == 0)
		index++;
	return (index);
}

int	get_sprite_id(t_sprite *sprite, int y, t_pair corr, int index)
{
	int	location;

	index = index % sprite->sprite_page_max_x;
	if (index < corr.x)
		index = corr.x;
	if (index > corr.y)
		index = corr.y;
	location = y * sprite->sprite_page_max_x + index;
	if (sprite->action == dying && location == 44)
	{
		play_music("Assests/Music/Guard_dying.mp3");
		sprite->action = dead;
	}
	return (location);
}

void	sort_sprites(t_vars *vars)
{
	t_sprite	tmp;
	t_sprite	*sprite;
	t_sprite	*next;

	sprite = vars->sprites;
	while (sprite)
	{
		next = sprite->next;
		while (next)
		{
			if (sprite->dist < next->dist)
			{
				ft_memmove(&tmp, sprite, sizeof(t_sprite) - sizeof(t_sprite *));
				ft_memmove(sprite, next, sizeof(t_sprite) - sizeof(t_sprite *));
				ft_memmove(next, &tmp, sizeof(t_sprite) - sizeof(t_sprite *));
			}
			next = next->next;
		}
		sprite = sprite->next;
	}
}

int	get_y_level(t_sprite *sprite)
{
	int		res;
	float	angle;

	res = 0;
	(void)angle;
	if (sprite->action == walking)
	{
		angle = sprite->angle * (180 / M_PI) + 22.5;
		if (angle > 360)
			angle -= 360;
		if (angle < 0)
			angle += 360;
		res = ((float)angle / 45);
		if (sprite->mov_coff == -1)
			res = 7 - res;
	}
	if (sprite->action == shotting)
		res = 9;
	if (sprite->action == dying || sprite->action == dead)
		res = 8;
	return (res);
}
