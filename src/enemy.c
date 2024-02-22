/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:18:50 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/03 16:08:53 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	reset_player(t_vars *vars)
{
	vars->hud->hp = 100;
	vars->hud->ammo = 15;
	vars->hud->score = 0;
	vars->player->pos = vars->player->initial_pos;
	vars->player->angle = vars->player->initial_angle;
	vars->hud->lives--;
	if (!vars->hud->lives)
	{
		ft_dprintf(2, "Game Over!\n");
		close_win(vars);
	}
}

void	detect_player(t_vars *vars, t_sprite *sprite)
{
	int		radius;
	t_point	delta;

	if (vars->clock % 50 != 0)
		return ;
	radius = 256;
	delta = (t_point){sprite->pos.x - vars->player->pos.x, sprite->pos.y
		- vars->player->pos.y};
	if (sprite->type == enemy && sprite->action != dead)
	{
		if (delta.x * delta.x + delta.y * delta.y < radius * radius)
		{
			sprite->action = shotting;
			vars->hud->hp -= 10;
			play_music("Assests/Music/player_pain.mp3");
			if (vars->hud->hp <= 0)
				reset_player(vars);
		}
		else
			sprite->action = walking;
	}
}

void	enemy_movement(t_vars *vars, t_sprite *sprite)
{
	int		radius;
	t_point	delta;
	t_point	dp;

	detect_player(vars, sprite);
	if (sprite->type == enemy && sprite->action == walking)
	{
		radius = 100;
		delta = (t_point){sprite->pos.x - vars->player->pos.x, sprite->pos.y
			- vars->player->pos.y};
		if (delta.x * delta.x + delta.y * delta.y > radius * radius)
		{
			sprite->pos.x += 8 * sprite->mov_coff;
			dp = downscale_point(sprite->pos);
			if (dp.x + sprite->mov_coff >= 0 && dp.x
				+ sprite->mov_coff < vars->map->size.x
				&& (vars->map->map[dp.y][dp.x + sprite->mov_coff] == '1'
				|| vars->map->map[dp.y][dp.x + sprite->mov_coff] == 'C'))
				sprite->mov_coff *= -1;
		}
	}
}
