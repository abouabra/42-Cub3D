/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:19:59 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/03 16:39:23 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parse_loop(t_vars *vars, int *i, int *rep)
{
	int	x;

	while (vars->map->map[++(*i)])
	{
		x = -1;
		if (!ft_isdigit(ft_strtrim(vars->map->map[*i], " \t")[0]))
		{
			ft_dprintf(2, "Invalid map\n");
			custom_exit(1);
		}
		while (ft_strlen(vars->map->map[*i]) < vars->map->size.x)
			vars->map->map[*i] = ft_strjoin(vars->map->map[*i], " ");
		while (vars->map->map[*i][++x])
			parse_player(vars, *i, x, rep);
	}
	if (*rep != 1)
	{
		ft_dprintf(2, "Invalid map\n");
		custom_exit(1);
	}
}

int	parse_infos(t_vars *vars, char **full_map)
{
	t_pair	data;
	int		i;
	char	**arr;
	char	*tmp;

	i = -1;
	while (full_map[++i])
	{
		tmp = ft_strtrim(full_map[i], " \t");
		if (tmp && ft_isdigit(tmp[0]))
			break ;
		if (!tmp[0])
			continue ;
		arr = ft_split_charset(tmp, " \t");
		data.x = 0;
		data.y = detect_type(arr[0], &data.x);
		set_elements(vars, data, arr, tmp);
	}
	if (!i)
	{
		ft_dprintf(2, "Invalid map\n");
		custom_exit(1);
	}
	check_for_correction(vars);
	return (i);
}

void	parse_map(t_vars *vars)
{
	int	i;
	int	rep;

	vars->player = my_alloc(sizeof(t_player));
	vars->hud = my_alloc(sizeof(t_hud));
	vars->map->map += parse_infos(vars, vars->map->map);
	if (!vars->map->map[0])
	{
		ft_dprintf(2, "Invalid map\n");
		custom_exit(1);
	}
	i = -1;
	rep = 0;
	parse_loop(vars, &i, &rep);
	vars->map->size.y = i;
	vars->map->longest_axis = i;
	if (vars->map->size.x > i)
		vars->map->longest_axis = vars->map->size.x;
	vars->map->size_px.x = vars->map->size.x * GRID_SIZE;
	vars->map->size_px.y = i * GRID_SIZE;
}

void	inside_map_check(t_vars *vars, char *line, int *tracker, int *start)
{
	if (!ft_strtrim(line, " \t\n")[0] && *start)
		*tracker = 1;
	if (ft_isdigit(ft_strtrim(line, " \t")[0]) && *tracker)
	{
		ft_dprintf(2, "Invalid map\n");
		custom_exit(1);
	}
	if (ft_isdigit(ft_strtrim(line, " \t")[0]) && ft_strlen(ft_strtrim(line,
				"\n")) > vars->map->size.x)
	{
		vars->map->size.x = ft_strlen(ft_strtrim(line, "\n"));
		*tracker = 0;
		*start = 1;
	}
}

void	map_operations(t_vars *vars, char *map_name)
{
	char	*total;
	int		fd;

	vars->map = my_alloc(sizeof(t_map));
	vars->map->map_colors[0][0] = -1;
	vars->map->map_colors[1][0] = -1;
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(2, "Invalid map\n");
		custom_exit(1);
	}
	total = read_map(vars, fd);
	vars->map->map = ft_split(total, '\n');
	parse_map(vars);
}
