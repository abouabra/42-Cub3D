/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:39:27 by abouabra          #+#    #+#             */
/*   Updated: 2023/09/29 12:19:43 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_fps(t_vars *vars)
{
	static mlx_image_t	*img;
	char				*fps;

	fps = ft_strjoin("FPS: ", ft_itoa(1 / vars->mlx->delta_time));
	fps = ft_strjoin(fps, "  Coins: ");
	fps = ft_strjoin(fps, ft_itoa(vars->hud->score));
	fps = ft_strjoin(fps, "  Player HP: ");
	fps = ft_strjoin(fps, ft_itoa(vars->hud->hp));
	mlx_delete_image(vars->mlx, img);
	img = mlx_put_string(vars->mlx, fps, 0, 0);
}

void	clear_images(t_vars *vars)
{
	t_point	index;

	index.y = -1;
	while (vars->minimap_img && vars->scene_img && ++index.y < WINDOW_HEIGHT)
	{
		index.x = -1;
		while (++index.x < WINDOW_WIDTH)
			mlx_put_pixel(vars->minimap_img, index.x, index.y, 0);
	}
}

void	loop(void *arg)
{
	t_vars	*vars;

	vars = (t_vars *)arg;
	if (vars->mlx && vars->clock % 2 == 0)
	{
		clear_images(vars);
		raycasting(vars);
		sprites(vars);
		draw_minimap(vars);
		draw_hud(vars);
	}
	vars->clock++;
}
