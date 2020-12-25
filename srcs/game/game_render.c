/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:28:46 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/17 13:28:49 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "sort_utils.h"
#include <tcl.h>
#include "mlx.h"

static void	render_textures(t_game *game, int column)
{
	t_texture	*texture;
	int			y;

	texture = select_texture(&game->textures, game->ray, game->player);
	get_texture_data(texture, game->ray, game->player, game->config);
	y = game->ray.draw_start;
	while (y < game->ray.draw_end)
	{
		texture->pos.y = (int)texture->start_pos & (64 - 1);
		texture->start_pos += texture->step;
		texture->color = ((int *)texture->img.addr)
				[64 * texture->pos.y + texture->pos.x];
		pixel_put(&game->mlx.img, column, y, texture->color);
		y++;
	}
}

static void	render_sky(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i != game->config.res.y / 2)
	{
		j = 0;
		while (j != game->config.res.x)
		{
			pixel_put(&game->mlx.img, j, i, game->config.ceil_color.color);
			j++;
		}
		i++;
	}
}

static void	render_floor(t_game *game)
{
	int i;
	int j;

	i = game->config.res.y / 2;
	while (i != game->config.res.y)
	{
		j = 0;
		while (j != game->config.res.x)
		{
			pixel_put(&game->mlx.img, j, i, game->config.floor_color.color);
			j++;
		}
		i++;
	}
}

static void	render_sprites(t_game *game, double *buffer)
{
	int			*order;
	double		*distance;
	int			i;
	t_sprite	sprite;

	i = 0;
	order = (int *)malloc(sizeof(int) * game->sprites.sprites_count);
	distance = (double *)malloc(sizeof(double) *
			game->sprites.sprites_count);
	init_sprites_position(order, distance, game->player, game->sprites);
	sort_double_vectors(order, distance, game->sprites.sprites_count);
	while (i < game->sprites.sprites_count)
	{
		sprite = game->sprites.sprite_arr[order[i]];
		get_sprite_data(&sprite, game->player, game->config);
		calculate_sprite_render_data(&sprite, game->config);
		render_sprite(sprite, game, buffer);
		i++;
	}
	free(order);
	order = NULL;
	free(distance);
	distance = NULL;
}

BOOL		game_render(t_game *game)
{
	double	*buffer;
	int		x;

	buffer = malloc(sizeof(double) * game->config.res.x);
	x = 0;
	render_sky(game);
	render_floor(game);
	while (x < game->config.res.x)
	{
		game->player.map_pos.x = (int)game->player.pos.x;
		game->player.map_pos.y = (int)game->player.pos.y;
		init_ray(&game->ray, &game->player, game->config, x);
		raycast(&game->ray, &game->player, game->config);
		render_textures(game, x);
		buffer[x] = game->ray.wall_dist;
		x++;
	}
	if (game->sprites.sprites_count)
		render_sprites(game, buffer);
	move_player(&game->player, game->keys, game->config);
	free(buffer);
	buffer = NULL;
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win,
									game->mlx.img.img, 0, 0);
	return (TRUE);
}
