/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:09:07 by abouabra          #+#    #+#             */
/*   Updated: 2023/09/29 12:13:55 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_line_err_corr(t_point *err, t_point delta, t_point *p, t_point s)
{
	err->y = 2 * err->x;
	if (err->y > -delta.y)
	{
		err->x -= delta.y;
		p->x += s.x;
	}
	if (err->y < delta.x)
	{
		err->x += delta.x;
		p->y += s.y;
	}
}

void	draw_line(mlx_image_t *img, t_line line)
{
	t_point	pos;
	t_point	delta;
	t_point	s;
	t_point	err;

	pos = (t_point){line.start.x, line.start.y};
	delta = (t_point){abs(line.end.x - line.start.x), abs(line.end.y
			- line.start.y)};
	s = (t_point){1, 1};
	if (line.start.x > line.end.x)
		s.x = -1;
	if (line.start.y > line.end.y)
		s.y = -1;
	err.x = delta.x - delta.y;
	while (pos.x != line.end.x || pos.y != line.end.y)
	{
		mlx_put_pixel(img, pos.x, pos.y, line.color);
		draw_line_err_corr(&err, delta, &pos, s);
	}
}

void	mlx_put_pixel_on_minimap(mlx_image_t *image, t_point point,
		t_point player, int color)
{
	t_point	circle_delta;
	t_point	squared;
	t_point	place_delta;
	t_point	end;

	circle_delta = (t_point){point.x - player.x, point.y - player.y};
	squared = (t_point){circle_delta.x * circle_delta.x, circle_delta.y
		* circle_delta.y};
	place_delta = (t_point){player.x - MINIMAP_X, player.y - MINIMAP_Y};
	if (squared.x + squared.y <= MINIMAP_RADIUS * MINIMAP_RADIUS)
	{
		end = (t_point){point.x - place_delta.x, point.y - place_delta.y};
		if (end.x > 0 && end.x < WINDOW_WIDTH && end.y > 0
			&& end.y < WINDOW_HEIGHT)
			mlx_put_pixel(image, end.x, end.y, color);
	}
}

void	draw_line_on_minimap(mlx_image_t *img, t_line line, t_point player)
{
	t_point	pos;
	t_point	delta;
	t_point	s;
	t_point	err;

	pos = (t_point){line.start.x, line.start.y};
	delta = (t_point){abs(line.end.x - line.start.x), abs(line.end.y
			- line.start.y)};
	s = (t_point){1, 1};
	if (line.start.x > line.end.x)
		s.x = -1;
	if (line.start.y > line.end.y)
		s.y = -1;
	err.x = delta.x - delta.y;
	while (pos.x != line.end.x || pos.y != line.end.y)
	{
		mlx_put_pixel_on_minimap(img, pos, player, line.color);
		draw_line_err_corr(&err, delta, &pos, s);
	}
}
