/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:48:26 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/03 16:34:11 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

void	detect_coalition_3(t_vars *vars, t_sprite *sprite)
{
	if (sprite->type == ammo)
	{
		play_music("Assests/Music/ammo_and_hp.mp3");
		vars->hud->ammo += 10;
	}
	if (sprite->type == gun)
	{
		if (sprite->loc == 29)
		{
			vars->hud->slots[2] = 1;
			vars->hud->selected_gun = 2;
		}
		else if (sprite->loc == 30)
		{
			vars->hud->slots[3] = 1;
			vars->hud->selected_gun = 3;
		}
		play_music("Assests/Music/ammo_and_hp.mp3");
	}
}

void	detect_coalition_2(t_vars *vars, t_sprite *sprite)
{
	if (sprite->type == collectibale)
	{
		if (sprite->loc == 31)
			vars->hud->score += 150;
		else if (sprite->loc == 32)
			vars->hud->score += 200;
		else if (sprite->loc == 33)
			vars->hud->score += 250;
		else if (sprite->loc == 34)
			vars->hud->score += 300;
		play_music("Assests/Music/score_plus.mp3");
	}
	if (sprite->type == health)
	{
		if (sprite->loc == 25)
			vars->hud->hp += 10;
		else if (sprite->loc == 26)
			vars->hud->hp += 40;
		else if (sprite->loc == 27)
			vars->hud->hp += 100;
		if (vars->hud->hp > 100)
			vars->hud->hp = 100;
		play_music("Assests/Music/ammo_and_hp.mp3");
	}
}

void	detect_coalition(t_vars *vars)
{
	t_sprite	*sprite;

	sprite = vars->sprites;
	while (sprite)
	{
		if (sprite->dist < 50 && sprite->type != enemy)
		{
			detect_coalition_2(vars, sprite);
			detect_coalition_3(vars, sprite);
			remove_if(vars, sprite);
			return ;
		}
		sprite = sprite->next;
	}
}

void	set_sprite_id(t_vars *vars, t_sprite *sprite, int index)
{
	int		y;
	t_pair	corr;

	corr = (t_pair){0, 0};
	configure_sprite(vars, sprite);
	sprite->id = sprite->loc;
	if (sprite->type == enemy)
	{
		y = get_y_level(sprite);
		if (sprite->action == shotting)
			corr = (t_pair){1, 2};
		if (sprite->action == walking)
			corr = (t_pair){1, 4};
		if (sprite->action == dying)
			corr = (t_pair){0, 4};
		else if (sprite->action == dead)
			corr = (t_pair){4, 4};
		sprite->id = get_sprite_id(sprite, y, corr, index);
	}
}
