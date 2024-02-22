/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:19:59 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/03 16:34:35 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

void	set_paths(t_vars *vars, char *line, int key)
{
	char	**arr;
	char	*tmp;

	if (vars->map->tex_paths[key] && vars->map->tex_paths[key][0])
	{
		ft_dprintf(2, "Invalid map\n");
		custom_exit(1);
	}
	line = ft_strtrim(line, " \t");
	tmp = ft_strnstr(line, ".png", -1);
	if (!tmp)
	{
		ft_dprintf(2, "Invalid map\n");
		custom_exit(1);
	}
	arr = ft_split_charset(tmp, " \t");
	if (!count_elements(arr, 1))
	{
		ft_dprintf(2, "Invalid map\n");
		custom_exit(1);
	}
	vars->map->tex_paths[key] = line;
}

void	set_colors_2(t_vars *vars, char **colors, int key)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (colors[i][++j])
		{
			if (!ft_isdigit(colors[i][j]))
			{
				ft_dprintf(2, "Invalid map\n");
				custom_exit(1);
			}
		}
		if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
		{
			ft_dprintf(2, "Invalid map\n");
			custom_exit(1);
		}
		vars->map->map_colors[key][i] = ft_atoi(colors[i]);
	}
}

void	set_colors(t_vars *vars, char *line, int key)
{
	char	**colors;
	int		i;

	if (vars->map->map_colors[key][0] != -1)
	{
		ft_dprintf(2, "Invalid map\n");
		custom_exit(1);
	}
	colors = ft_split(line, ',');
	if (!count_elements(colors, 3))
	{
		ft_dprintf(2, "Invalid map\n");
		custom_exit(1);
	}
	i = -1;
	while (line[++i])
	{
		if (line[i] == ',' && (!line[i + 1] || line[i + 1] == ','))
		{
			ft_dprintf(2, "Invalid map\n");
			custom_exit(1);
		}
	}
	set_colors_2(vars, colors, key);
}

void	set_elements(t_vars *vars, t_pair data, char **arr, char *tmp)
{
	if (!data.y)
	{
		ft_dprintf(2, "Invalid map\n");
		custom_exit(1);
	}
	if (data.y == direction)
		set_paths(vars, tmp + 2, data.x);
	else if (data.y == color)
	{
		if (!count_elements(arr, 2))
		{
			ft_dprintf(2, "Invalid map\n");
			custom_exit(1);
		}
		set_colors(vars, arr[1], data.x);
	}
}
