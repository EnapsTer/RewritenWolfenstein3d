/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_engine.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:45:23 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/17 12:45:45 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H
# define ESC 53
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

typedef struct  s_data
{
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef struct	s_vector
{
	int			x;
	int			y;
}				t_vector;

typedef struct	s_d_vector
{
	double			x;
	double			y;
}				t_d_vector;


typedef struct	s_ray
{
	t_d_vector 	dir;
	t_d_vector	side_dist;
	t_d_vector	delta_dist;
	int 		draw_start; // сделать как вектор
	int 		draw_end;
	int			wall_side;
	double		wall_dist;
	int			height;
}				t_ray;

typedef struct	s_player
{
	t_d_vector 	dir;
	t_d_vector	plane;
	t_d_vector	pos;
	t_vector	map_pos;
	t_vector	step;
	char 		start_view;
}				t_player;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	t_data		img;
}				t_mlx;

typedef struct	s_keys
{
	int			w;
	int			s;
	int 		a;
	int			d;
	int			left;
	int			right;
} 				t_keys;

typedef struct	s_texture
{
	char		*path;
	t_data		img;
	int			height;
	int			width;
	double		start_pos;
	t_vector	pos;
	int			num;
	double		step;
	uint32_t	color;
}				t_texture;

typedef struct	s_textures
{
	t_texture	no;
	t_texture	so;
	t_texture	ea;
	t_texture	we;
}				t_textures;

typedef struct	s_sprite
{
	t_d_vector	pos;
}				t_sprite;

typedef struct	s_sprites
{
	t_sprite	*sprite_arr;
	int			sprites_count;
	t_texture	texture;
}				t_sprites;

typedef struct	s_game
{
	t_keys		keys;
	t_config	config;
	t_mlx		mlx;
	t_player	player;
	t_ray		ray;
	t_textures	textures;
	t_sprites	sprites;
}				t_game;

BOOL handle_pressed_key(int key, t_game *game);

BOOL handle_unpressed_key(int key, t_game *game);

BOOL	game_render(t_game *game);

void init_player(t_player *player, t_config config);

void init_ray(t_ray *ray, t_player *player, t_config config, int stripe);

void		raycast(t_ray *ray, t_player *player, t_config config);

void	move_player(t_player *player, t_keys keys, t_config config);

void init_textures(t_textures *textures, t_config config, t_mlx *mlx);

void		get_texture_data(t_texture *texture, t_ray ray, t_player player, t_config config);

t_texture	*select_texture(t_textures *textures, t_ray ray, t_player player);

void	init_sprites(t_sprites *sprites, t_config config, void *mlx);
#endif
