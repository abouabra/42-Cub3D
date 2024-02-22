/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:52:42 by ayman             #+#    #+#             */
/*   Updated: 2023/10/03 16:43:11 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define HUD_HEIGHT 215

# define GRID_SIZE 64

# define TPI2 4.71238898038468985769

# define MINIMAP_RADIUS 128

# define MINIMAP_X MINIMAP_RADIUS
# define MINIMAP_Y 96

# define MINIMAP_SCALE 4

# define FOV 60

# include "../MLX/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>
# include <time.h>

typedef struct t_point
{
	int				x;
	int				y;
}					t_point;

typedef t_point		t_pair;

typedef struct t_line
{
	t_point			start;
	t_point			end;
	int				color;
}					t_line;

typedef struct t_fpoint
{
	float			x;
	float			y;
}					t_fpoint;
typedef t_fpoint	t_fpair;

typedef struct t_ray
{
	float			angle;

	t_point			start;
	t_fpoint		end;
	t_fpoint		offset;
	t_point			map;

	int				prespective;
	float			distance;
	int				line_h;

	t_fpoint		tex;

	int				r_type;
}					t_ray;

typedef struct t_map
{
	char			**map;
	t_point			size;
	t_point			size_px;
	int				longest_axis;
	char			*tex_paths[4];
	int				map_colors[2][3];
}					t_map;

typedef struct t_player
{
	t_point			pos;
	t_point			initial_pos;
	float			angle;
	float			initial_angle;

}					t_player;

typedef struct t_hud
{
	mlx_texture_t	*main_hud;
	mlx_texture_t	*numbers;
	mlx_texture_t	*guns;

	mlx_texture_t	*guns_on_screen;
	int				floor;
	int				score;
	int				lives;
	int				hp;
	int				ammo;
	int				selected_gun;
	int				slots[4];
}					t_hud;

typedef struct t_sprite
{
	int				id;
	int				sprite_hp;
	char			c;
	int				loc;

	mlx_texture_t	*page_pointer;
	int				sprite_size_on_page;
	int				sprite_page_max_x;
	int				sprite_page_max_y;

	int				type;
	t_point			pos;

	float			angle;
	float			dist;
	float			tex_size;

	t_pair			tex;
	t_pair			off;

	int				mov_coff;
	int				action;
	struct t_sprite	*next;
}					t_sprite;

typedef struct t_vars
{
	mlx_t			*mlx;
	mlx_image_t		*minimap_img;
	mlx_image_t		*scene_img;

	t_map			*map;
	t_player		*player;

	t_ray			*v_ray;
	t_ray			*h_ray;
	float			dists[WINDOW_WIDTH];

	mlx_texture_t	*textures[4];

	mlx_texture_t	*wall_tiles;
	mlx_texture_t	*object_tiles;
	mlx_texture_t	*gard_tiles;

	t_sprite		*sprites;
	t_hud			*hud;

	int				clock;
}					t_vars;

enum				e_prespective
{
	NO,
	SO,
	WE,
	EA
};
enum				e_enemy_actions
{
	walking,
	shotting,
	dying,
	dead
};
enum				e_colors
{
	F,
	C
};

enum				e_ray_type
{
	space,
	wall,
	door_closed,
	door_opened = -1
};

enum				e_rgb
{
	R,
	G,
	B,
	A
};
enum				e_type
{
	color = 1,
	direction
};

enum				e_sprite_type
{
	collectibale,
	enemy,
	ammo,
	gun,
	health,
	block
};

void				map_operations(t_vars *vars, char *map_name);
void				loop(void *vars);
void				key_press(void *arg);
void				raycasting(t_vars *vars);
float				normalize_values(float angle);
void				clear_images(t_vars *vars);
void				draw_minimap(t_vars *vars);
void				draw_fps(t_vars *vars);
int					round_down(int num);
void				door_action(struct mlx_key_data key, void *arg);

void				draw_line(mlx_image_t *img, t_line line);
void				draw_line_on_minimap(mlx_image_t *img, t_line line,
						t_point player);

void				sprites(t_vars *vars);
int					get_color_from_pos(mlx_texture_t *texture, int x, int y);

t_sprite			*new_sprite(t_vars *vars, t_point pos, char c);
void				add_sprite(t_vars *vars, t_sprite *sprite);
void				remove_if(t_vars *vars, t_sprite *sprite);

int					get_sprite_from_pos(t_sprite *sprite, t_point pos);
int					map_zone_floor_1(t_ray *ray);

t_point				downscale_point(t_point init);
t_point				downscale_fpoint(t_fpoint init);
void				close_win(t_vars *vars);
void				mlx_put_pixel_on_minimap(mlx_image_t *image, t_point point,
						t_point player, int color);
void				draw_hud(t_vars *vars);
int					surrounded_by(t_vars *vars, int i, int j);
int					count_elements(char **arr, int max);
int					detect_type(char *element, int *key);
int					get_sprite_type(t_sprite *sprite, char c);
int					check_chars(char c);
void				check_for_correction(t_vars *vars);
void				parse_sprites(t_vars *vars, t_point pos, char c);
void				init_player(t_vars *vars, t_point point, int ang, int *rep);
void				parse_player(t_vars *vars, int i, int x, int *rep);
void				set_paths(t_vars *vars, char *line, int key);
void				set_colors(t_vars *vars, char *line, int key);
void				set_elements(t_vars *vars, t_pair data, char **arr,
						char *tmp);
int					rgba(int r, int g, int b, int a);
void				init_h_values(t_ray *ray, t_player *player, float angle,
						int *x);
void				init_v_values(t_ray *ray, t_player *player, float angle,
						int *x);
void				check_ray(t_vars *vars, t_ray *ray, int type);
void				shoot_h_ray(t_vars *vars, float ra);
void				shoot_v_ray(t_vars *vars, float ra);
void				pick_shortest_ray(t_vars *vars, t_ray **ray);
void				draw_ray_in_minimap(t_vars *vars, t_ray *ray);
void				set_line_height(t_ray *ray);
void				fix_fish_eye(t_vars *vars, t_ray *ray, float ra, int x);
void				fix_fish_eye(t_vars *vars, t_ray *ray, float ra, int x);
void				draw_ceiling(t_vars *vars, t_ray *ray, int x);
void				draw_floor(t_vars *vars, t_ray *ray, int x);
float				calc_dist(t_point start, t_point end);
int					round_down(int num);
int					has_hit_a_wall(t_map *map, t_point point);
void				detect_player(t_vars *vars, t_sprite *sprite);
void				enemy_movement(t_vars *vars, t_sprite *sprite);
int					get_sprite_from_pos(t_sprite *sprite, t_point pos);
int					get_clock_index(t_vars *vars);
int					get_sprite_id(t_sprite *sprite, int y, t_pair corr,
						int index);
void				sort_sprites(t_vars *vars);
int					get_y_level(t_sprite *sprite);
void				detect_coalition(t_vars *vars);
void				set_sprite_id(t_vars *vars, t_sprite *sprite, int index);
void				configure_sprite(t_vars *vars, t_sprite *sprite);
void				draw_gun_on_screen(t_vars *vars, int id);
int					get_gun_id(t_vars *vars, int y, t_pair corr, int index);
void				play_music(char *path);
char				*read_map(t_vars *vars, int fd);
void				inside_map_check(t_vars *vars, char *line, int *tracker,
						int *start);
void				enemy_shooting(t_vars *vars);

#endif
