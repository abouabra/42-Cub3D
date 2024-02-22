/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 02:34:44 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/03 16:16:00 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_sprite	*new_sprite(t_vars *vars, t_point pos, char c)
{
	t_sprite	*sprite;

	sprite = my_alloc(sizeof(t_sprite));
	sprite->pos = pos;
	sprite->c = c;
	sprite->type = get_sprite_type(sprite, c);
	sprite->mov_coff = 1;
	sprite->sprite_size_on_page = 256;
	sprite->sprite_page_max_x = 5;
	sprite->sprite_page_max_y = 10;
	sprite->page_pointer = vars->object_tiles;
	if (sprite->type == enemy)
	{
		sprite->action = walking;
		sprite->sprite_hp = 100;
		sprite->page_pointer = vars->gard_tiles;
	}
	return (sprite);
}

void	add_sprite(t_vars *vars, t_sprite *sprite)
{
	t_sprite	*tmp;

	tmp = vars->sprites;
	if (!tmp)
		vars->sprites = sprite;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = sprite;
	}
}

void	remove_if(t_vars *vars, t_sprite *sprite)
{
	t_sprite	*tmp;
	t_sprite	*prev;

	tmp = vars->sprites;
	prev = NULL;
	while (tmp)
	{
		if (tmp == sprite)
		{
			if (prev)
				prev->next = tmp->next;
			else
				vars->sprites = tmp->next;
			tmp = NULL;
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
