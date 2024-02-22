/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:09:07 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/03 16:42:35 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

int	enemy_player_coalition(t_vars *vars, t_point new)
{
	t_sprite	*sprite;
	int			radius;
	t_pair		delta;
	int			move;

	sprite = vars->sprites;
	move = 1;
	radius = 100;
	while (sprite)
	{
		if (sprite->type == enemy && sprite->action != dead)
		{
			delta = (t_point){sprite->pos.x - new.x, sprite->pos.y - new.y};
			if (delta.x * delta.x + delta.y * delta.y < radius * radius)
				move = 0;
		}
		sprite = sprite->next;
	}
	return (move);
}

void	move_player(t_vars *vars, char **map, float direction)
{
	t_fpoint	delta;
	t_point		new;
	t_point		new_index;
	t_point		index;
	t_point		off;

	off = (t_point){32, 32};
	delta.x = cos(direction) * 10;
	delta.y = sin(direction) * 10;
	if (delta.x < 0)
		off.x = -off.x;
	if (delta.y < 0)
		off.y = -off.y;
	new.x = vars->player->pos.x + delta.x + off.x;
	new.y = vars->player->pos.y + delta.y + off.y;
	new_index = downscale_point(new);
	index = downscale_point(vars->player->pos);
	if (map[index.y][new_index.x] != '1' && map[index.y][new_index.x] != 'C')
		vars->player->pos.x += delta.x * enemy_player_coalition(vars, new);
	if (map[new_index.y][index.x] != '1' && map[new_index.y][index.x] != 'C')
		vars->player->pos.y += delta.y * enemy_player_coalition(vars, new);
}

void	mouse(t_vars *vars)
{
	static int	x;
	int			y;
	int			before;

	y = 0;
	before = x;
	mlx_get_mouse_pos(vars->mlx, &x, &y);
	if (x == before)
		return ;
	if (x > before)
		vars->player->angle += 0.1;
	if (x < before)
		vars->player->angle -= 0.1;
	vars->player->angle = normalize_values(vars->player->angle);
	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		mlx_set_mouse_pos(vars->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mlx_set_cursor_mode(vars->mlx, MLX_MOUSE_DISABLED);
}

void	key_press_2(t_vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_SPACE))
		enemy_shooting(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_1))
		vars->hud->selected_gun = 0;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_2))
		vars->hud->selected_gun = 1;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_3))
		if (vars->hud->slots[2])
			vars->hud->selected_gun = 2;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_4))
		if (vars->hud->slots[3])
			vars->hud->selected_gun = 3;
	mouse(vars);
}

void	key_press(void *arg)
{
	t_vars	*vars;

	vars = (t_vars *)arg;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		close_win(vars);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
		move_player(vars, vars->map->map, vars->player->angle);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
		move_player(vars, vars->map->map, vars->player->angle + M_PI);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		move_player(vars, vars->map->map, vars->player->angle - M_PI_2);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		move_player(vars, vars->map->map, vars->player->angle + M_PI_2);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		vars->player->angle -= 0.05;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		vars->player->angle += 0.05;
	vars->player->angle = normalize_values(vars->player->angle);
	key_press_2(vars);
}
