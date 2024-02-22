/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_operations_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:19:59 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/02 20:52:56 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	count_elements(char **arr, int max)
{
	int	x;

	x = -1;
	while (arr[++x])
		;
	if (x != max)
		return (0);
	return (1);
}

int	detect_type(char *element, int *key)
{
	if (!ft_strncmp(element, "NO", -1))
		return (*key = NO, direction);
	else if (!ft_strncmp(element, "SO", -1))
		return (*key = SO, direction);
	else if (!ft_strncmp(element, "WE", -1))
		return (*key = WE, direction);
	else if (!ft_strncmp(element, "EA", -1))
		return (*key = EA, direction);
	else if (!ft_strncmp(element, "F", -1))
		return (*key = F, color);
	else if (!ft_strncmp(element, "C", -1))
		return (*key = C, color);
	return (0);
}

int	get_sprite_type(t_sprite *sprite, char c)
{
	char	*charset;
	int		i;

	charset = "ABDFHIJKLMPQRTUVXYZabcdefghijklmnopqrstuvwxyz";
	i = -1;
	while (charset[++i])
		if (charset[i] == c)
			break ;
	sprite->loc = i;
	if (i >= 25 && i <= 27)
		return (health);
	if (i == 28)
		return (ammo);
	if (i == 29 || i == 30)
		return (gun);
	if (i >= 31 && i <= 34)
		return (collectibale);
	if (c == 'G')
		return (enemy);
	return (block);
}

int	check_chars(char c)
{
	int		i;
	char	*charset;

	i = -1;
	charset = "ESWN01 \tGCOABDFHIJKLMPQRTUVXYZabcdefghijklmnopqrstuvwxyz";
	while (charset[++i])
	{
		if (c == charset[i])
			return (i);
	}
	return (-1);
}

int	surrounded_by(t_vars *vars, int i, int j)
{
	if (i == 0 || i == vars->map->size.y - 1 || j == 0 || j == vars->map->size.x
		- 1)
		return (0);
	if (ft_strchr(" \t", vars->map->map[i][j + 1]) || ft_strchr(" \t",
			vars->map->map[i][j - 1]))
		return (0);
	if (ft_strchr(" \t", vars->map->map[i + 1][j]) || ft_strchr(" \t",
			vars->map->map[i - 1][j]))
		return (0);
	return (1);
}
