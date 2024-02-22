/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:39:27 by abouabra          #+#    #+#             */
/*   Updated: 2023/10/03 16:42:05 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_number_on_screen(t_vars *vars, int number, int px, int py)
{
	t_pair	loop;
	int		end;
	int		hex;

	loop = (t_pair){-1, -1};
	while (++loop.y < (int)vars->hud->numbers->height)
	{
		loop.x = 51 * number - 1;
		end = 51 + loop.x;
		while (++loop.x <= end)
		{
			hex = get_color_from_pos(vars->hud->numbers, loop.x, loop.y);
			if (loop.x >= 0 && loop.x < WINDOW_WIDTH && loop.y >= 0
				&& loop.y < WINDOW_HEIGHT)
				mlx_put_pixel(vars->scene_img, loop.x % 51 + px,
					loop.y + py, hex);
		}
	}
}

void	draw_number(t_vars *vars, int x_offset, int number)
{
	int	py;
	int	nb_count;
	int	temp;
	int	px;

	py = WINDOW_HEIGHT + 82;
	nb_count = 0;
	temp = number;
	while (temp)
	{
		temp /= 10;
		nb_count++;
	}
	if (number == 0)
		nb_count = 1;
	px = x_offset + (nb_count * 51);
	while (nb_count)
	{
		px -= 51;
		draw_number_on_screen(vars, number % 10, px, py);
		number /= 10;
		nb_count--;
	}
}

void	draw_guns(t_vars *vars, int x_offset)
{
	t_pair	loop;
	int		end;
	int		hex;
	int		py;
	int		px;

	py = WINDOW_HEIGHT + 32;
	px = x_offset;
	loop = (t_pair){-1, -1};
	while (++loop.y < (int)vars->hud->guns->height)
	{
		loop.x = 304 * vars->hud->selected_gun - 1;
		end = loop.x + 304;
		while (++loop.x <= end)
		{
			hex = get_color_from_pos(vars->hud->guns, loop.x, loop.y);
			if (loop.x >= 0 && loop.x < WINDOW_WIDTH && loop.y >= 0
				&& loop.y < WINDOW_HEIGHT)
				mlx_put_pixel(vars->scene_img, px + loop.x % 304,
					loop.y + py, hex);
		}
	}
}

void	draw_hud(t_vars *vars)
{
	t_pair	loop;
	int		hex;

	loop = (t_pair){-1, -1};
	while (++loop.y < (int)vars->hud->main_hud->height)
	{
		loop.x = -1;
		while (++loop.x < (int)vars->hud->main_hud->width)
		{
			hex = get_color_from_pos(vars->hud->main_hud, loop.x, loop.y);
			if (loop.x >= 0 && loop.x < WINDOW_WIDTH && loop.y >= 0
				&& loop.y < WINDOW_HEIGHT)
				mlx_put_pixel(vars->scene_img, loop.x, 
					loop.y + WINDOW_HEIGHT, hex);
		}
	}
	draw_number(vars, 30, vars->hud->floor);
	draw_number(vars, 275, vars->hud->score);
	draw_number(vars, 600, vars->hud->lives);
	draw_number(vars, 1000, vars->hud->hp);
	draw_number(vars, 1300, vars->hud->ammo);
	draw_guns(vars, 1568);
}

void	draw_gun_on_screen(t_vars *vars, int id)
{
	t_pair	loop;
	int		end;
	int		hex;
	t_pair	global;
	t_pair	pos;

	global.x = (id % 5) * 512;
	global.y = (id / 5) * 512;
	pos.y = WINDOW_HEIGHT - 512;
	pos.x = (WINDOW_WIDTH / 2) - (512 / 2);
	loop = (t_pair){-1, -1};
	while (++loop.y < 512)
	{
		loop.x = -1;
		end = loop.x + 512;
		while (++loop.x <= end)
		{
			hex = get_color_from_pos(vars->hud->guns_on_screen, loop.x
					+ global.x, loop.y + global.y);
			if (loop.x >= 0 && loop.x < WINDOW_WIDTH && loop.y >= 0
				&& loop.y < WINDOW_HEIGHT && hex)
				mlx_put_pixel(vars->scene_img, pos.x + loop.x % 512,
					loop.y + pos.y, hex);
		}
	}
}
