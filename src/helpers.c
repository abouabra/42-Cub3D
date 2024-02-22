/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:09:07 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/03 15:47:41 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdlib.h>

float	normalize_values(float angle)
{
	if (angle >= M_PI * 2)
		angle -= M_PI * 2;
	else if (angle < 0)
		angle += M_PI * 2;
	return (angle);
}

void	close_win(t_vars *vars)
{
	int	i;

	system("killall afplay &> /dev/null");
	i = -1;
	while (++i < 4)
		mlx_delete_texture(vars->textures[i]);

	mlx_delete_texture(vars->gard_tiles);
	mlx_delete_texture(vars->object_tiles);
	mlx_delete_texture(vars->wall_tiles);
	mlx_delete_texture(vars->hud->main_hud);
	mlx_delete_texture(vars->hud->numbers);
	mlx_delete_texture(vars->hud->guns);
	mlx_delete_texture(vars->hud->guns_on_screen);

	mlx_delete_image(vars->mlx, vars->scene_img);
	mlx_delete_image(vars->mlx, vars->minimap_img);
	mlx_terminate(vars->mlx);
	custom_exit(EXIT_SUCCESS);
}

int	get_color_from_pos(mlx_texture_t *texture, int x, int y)
{
	int	offset;
	int	colors[4];
	int	hex_color;

	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
		return (0);
	offset = (y * texture->width + x) * texture->bytes_per_pixel;
	colors[B] = texture->pixels[offset];
	colors[G] = texture->pixels[offset + 1];
	colors[R] = texture->pixels[offset + 2];
	colors[A] = texture->pixels[offset + 3];
	hex_color = rgba(colors[R], colors[G], colors[B], colors[A]);
	return (hex_color);
}

t_point	downscale_point(t_point init)
{
	t_point	point;

	point.x = init.x / GRID_SIZE;
	point.y = init.y / GRID_SIZE;
	return (point);
}

t_point	downscale_fpoint(t_fpoint init)
{
	t_point	point;

	point.x = init.x / GRID_SIZE;
	point.y = init.y / GRID_SIZE;
	return (point);
}
