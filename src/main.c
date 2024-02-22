/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:18:50 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/03 17:00:15 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

void	initialize_mlx(t_vars *vars)
{
	int	height;

	height = WINDOW_HEIGHT;
	height += HUD_HEIGHT;
	vars->mlx = mlx_init(WINDOW_WIDTH, height, "Cub3D", false);
	if (!vars->mlx)
	{
		ft_dprintf(2, "mlx_init failed\n");
		custom_exit(EXIT_FAILURE);
	}
	vars->minimap_img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	vars->scene_img = mlx_new_image(vars->mlx, WINDOW_WIDTH, height);
	if (!vars->minimap_img || !vars->scene_img)
	{
		ft_dprintf(2, "mlx_new_image failed\n");
		mlx_terminate(vars->mlx);
		custom_exit(EXIT_FAILURE);
	}
	vars->v_ray = my_alloc(sizeof(t_ray));
	vars->h_ray = my_alloc(sizeof(t_ray));
	play_music("Assests/Music/Main_Music.mp3");
}

void	start_game(t_vars *vars)
{
	initialize_mlx(vars);
	mlx_image_to_window(vars->mlx, vars->scene_img, 0, 0);
	mlx_image_to_window(vars->mlx, vars->minimap_img, 0, 0);
	mlx_loop_hook(vars->mlx, loop, vars);
	mlx_loop_hook(vars->mlx, key_press, vars);
	mlx_key_hook(vars->mlx, door_action, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
}

int	main(int ac, char **av)
{
	t_vars	*vars;

	if (ac != 2)
	{
		ft_dprintf(2, "Example: ./cub3D maps/bonus.cub\n");
		return (EXIT_FAILURE);
	}
	vars = my_alloc(sizeof(t_vars));
	map_operations(vars, av[1]);
	start_game(vars);
	custom_exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
