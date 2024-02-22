/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:09:07 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/03 16:42:45 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_gun_id(t_vars *vars, int y, t_pair corr, int index)
{
	int	location;

	index = index % 5;
	if (index < corr.x)
		index = corr.x;
	if (index > corr.y)
		index = corr.y;
	location = y * 5 + index;
	if (vars->hud->ammo != 0)
		return (location);
	return (y * 5);
}

void	enemy_shooting_3(t_vars *vars, t_sprite *sprite)
{
	float	an;

	if (sprite->type == enemy && sprite->action != dead
		&& sprite->action != dying)
	{
		an = (sprite->angle - vars->player->angle) * (180.0f / M_PI);
		if (fabs(an) < 10)
		{
			if (vars->hud->ammo && vars->clock % 10 == 0)
			{
				sprite->sprite_hp -= 10;
				if (sprite->sprite_hp <= 0)
				{
					vars->hud->score += 150;
					sprite->action = dying;
				}
			}
		}
	}
}

void	enemy_shooting_2(t_vars *vars)
{
	t_sprite	*sprite;
	int			index;
	t_pair		corr;
	int			id;

	index = get_clock_index(vars);
	corr = (t_pair){1, 3};
	id = get_gun_id(vars, vars->hud->selected_gun, corr, index);
	draw_gun_on_screen(vars, id);
	sprite = vars->sprites;
	while (sprite)
	{
		enemy_shooting_3(vars, sprite);
		sprite = sprite->next;
	}
}

void	enemy_shooting(t_vars *vars)
{
	if (vars->clock % 20 == 0)
	{
		if (vars->hud->selected_gun)
		{
			vars->hud->ammo--;
			if (vars->hud->ammo < 0)
				vars->hud->ammo = 0;
		}
		if (vars->hud->ammo && vars->hud->selected_gun == 0)
			play_music("Assests/Music/knife.mp3");
		else if (vars->hud->ammo && vars->hud->selected_gun == 1)
			play_music("Assests/Music/pistol.mp3");
		else if (vars->hud->ammo && vars->hud->selected_gun == 2)
			play_music("Assests/Music/ak-47.mp3");
		else if (vars->hud->ammo && vars->hud->selected_gun == 3)
			play_music("Assests/Music/machine_gun.mp3");
	}
	enemy_shooting_2(vars);
}

void	door_action(struct mlx_key_data key, void *arg)
{
	t_vars	*vars;
	t_point	index;
	t_point	pos;

	vars = (t_vars *)arg;
	if (key.key == MLX_KEY_E && key.action == MLX_PRESS)
	{
		index.x = vars->player->pos.x + cos(vars->player->angle) * GRID_SIZE;
		index.y = vars->player->pos.y + sin(vars->player->angle) * GRID_SIZE;
		index = downscale_point(index);
		pos = downscale_point(vars->player->pos);
		if (vars->map->map[index.y][index.x] == 'C')
			vars->map->map[index.y][index.x] = 'O';
		else if (vars->map->map[index.y][index.x] == 'O'
				&& vars->map->map[pos.y][pos.x] != 'O')
			vars->map->map[index.y][index.x] = 'C';
	}
}
