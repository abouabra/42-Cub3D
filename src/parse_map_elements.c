/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:19:59 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/03 16:58:32 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

void	check_for_correction_mandatory(t_vars *vars, int *i)
{
	while (++(*i) < 4)
	{
		if (!vars->map->tex_paths[*i])
		{
			ft_dprintf(2, "Invalid map\n");
			custom_exit(1);
		}
		if (*i < 2 && vars->map->map_colors[*i][0] == -1)
		{
			ft_dprintf(2, "Invalid map\n");
			custom_exit(1);
		}
		vars->textures[*i] = mlx_load_png(vars->map->tex_paths[*i]);
		if (!vars->textures[*i])
		{
			ft_dprintf(2, "Invalid map\n");
			custom_exit(1);
		}
		if (vars->textures[*i]->height != vars->textures[*i]->width)
		{
			ft_dprintf(2, "Invalid map\n");
			custom_exit(1);
		}
	}
}

void	check_for_correction(t_vars *vars)
{
	int	i;

	i = -1;
	check_for_correction_mandatory(vars, &i);
	vars->wall_tiles = mlx_load_png("Assests/Walls/WallTiles-256.png");
	vars->object_tiles = mlx_load_png("Assests/Sprites/Objects-256.png");
	vars->gard_tiles = mlx_load_png("Assests/Sprites/enemy_Guard-256.png");
	vars->hud->main_hud = mlx_load_png("Assests/HUD/main_HUD.png");
	vars->hud->numbers = mlx_load_png("Assests/HUD/numbers_HUB.png");
	vars->hud->guns = mlx_load_png("Assests/HUD/weapons_HUD.png");
	vars->hud->guns_on_screen = mlx_load_png("Assests/HUD/Gun_Animations.png");
	if (!vars->wall_tiles || !vars->object_tiles || !vars->gard_tiles
		|| !vars->hud->main_hud || !vars->hud->numbers || !vars->hud->guns
		|| !vars->hud->guns_on_screen)
	{
		ft_dprintf(2, "Invalid map\n");
		custom_exit(1);
	}
}

void	parse_sprites(t_vars *vars, t_point pos, char c)
{
	t_sprite	*sprite;

	sprite = new_sprite(vars, pos, c);
	add_sprite(vars, sprite);
}

void	parse_player_bonus(t_vars *vars, int i, int x)
{
	t_point	upscalled;

	if (ft_strchr("GCOABDFHIJKLMPQRTUVXYZabcdefghijklmnopqrstuvwxyz",
			vars->map->map[i][x]) && !surrounded_by(vars, i, x))
	{
		ft_dprintf(2, "Invalid map\n");
		custom_exit(1);
	}
	if (ft_strchr("GABDFHIJKLMPQRTUVXYZabcdefghijklmnopqrstuvwxyz",
			vars->map->map[i][x]))
	{
		upscalled = (t_point){x * GRID_SIZE, i * GRID_SIZE};
		parse_sprites(vars, upscalled, vars->map->map[i][x]);
		vars->map->map[i][x] = '0';
	}
}

void	parse_player(t_vars *vars, int i, int x, int *rep)
{
	int		ang;
	t_point	pos;

	pos = (t_point){x, i};
	ang = check_chars(vars->map->map[i][x]);
	if (ang < 0)
	{
		ft_dprintf(2, "Invalid map\n");
		custom_exit(1);
	}
	init_player(vars, pos, ang, rep);
	if (ang >= 0 && ang <= 4 && !surrounded_by(vars, i, x))
	{
		ft_dprintf(2, "Invalid map\n");
		custom_exit(1);
	}
	parse_player_bonus(vars, i, x);
}
