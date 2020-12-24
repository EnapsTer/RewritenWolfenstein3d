/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:26:36 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/24 14:26:39 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <math.h>
#include "mlx.h"

void	init_sprites_position(int *order, double *distance,
						   t_player player, t_sprites sprites)
{
	int i;
	t_sprite *sprite_arr;

	sprite_arr = sprites.sprite_arr;
	i = 0;
	while (i < sprites.sprites_count)
	{
		order[i] = i;
		distance[i] = (
				(player.pos.x - sprite_arr[i].map_pos.x) *
				(player.pos.x - sprite_arr[i].map_pos.x) +
				(player.pos.y - sprite_arr[i].map_pos.y) *
				(player.pos.y - sprite_arr[i].map_pos.y)
		);
		i++;
	}
}

BOOL	is_need_to_draw(t_sprite sprite, int i, double *Zbuffer, int x)
{
	return (sprite.transform.y > 0 && i > 0 &&
			i < x && sprite.transform.y < Zbuffer[i]);
}

void	render_sprite(t_sprite sprite, t_game *game, double *Zbuffer)
{
	int i;
	int j;
	int temp;
	t_vector tex_pos;
	uint32_t color;

	i = sprite.draw_start.x - 1;
	while (++i < sprite.draw_end.x)
	{
		tex_pos.x = (int)(256 * (i - (-sprite.width / 2 + sprite.sprite_screen))
				* game->sprites.texture.width / sprite.width) / 256;
		if (is_need_to_draw(sprite, i, Zbuffer, game->config.res.x))
		{
			j = sprite.draw_start.y - 1;
			while (++j < sprite.draw_end.y)
			{
				temp = j * 256 - game->config.res.y * 128 + sprite.height * 128;
				tex_pos.y = ((temp * game->sprites.texture.width)
						/ sprite.height) / 256;
				color = ((int*)game->sprites.texture.img.addr)
						[game->sprites.texture.width * tex_pos.y + tex_pos.x];
				if ((color & 0x00FFFFFF) != 9961608)
					pixel_put(&game->mlx.img, i, j, color);
			}
		}
	}
}

void	calculate_sprite_render_data(t_sprite *sprite, t_config config)
{
	sprite->height = abs((int)(config.res.y / sprite->transform.y));
	sprite->width = abs((int)(config.res.y / sprite->transform.y));
	sprite->draw_start.x = -sprite->width / 2 + sprite->sprite_screen;
	if(sprite->draw_start.x < 0)
		sprite->draw_start.x = 0;
	sprite->draw_end.x = sprite->width / 2 + sprite->sprite_screen;
	if(sprite->draw_end.x >= config.res.x)
		sprite->draw_end.x = config.res.x - 1;
	sprite->draw_start.y = -sprite->height  / 2 + config.res.y / 2;
	if(sprite->draw_start.y < 0)
		sprite->draw_start.y = 0;
	sprite->draw_end.y = sprite->height / 2 + config.res.y / 2;
	if(sprite->draw_end.y >= config.res.y)
		sprite->draw_end.y = config.res.y - 1;
}

void	get_sprite_data(t_sprite *sprite, t_player player, t_config config)
{
	double		inv_det;

	sprite->pos.x = sprite->map_pos.x - player.pos.x;
	sprite->pos.y = sprite->map_pos.y - player.pos.y;
	inv_det = 1.0 / (player.plane.x * player.dir.y -
		player.dir.x * player.plane.y);
	sprite->transform.x = inv_det * (player.dir.y *
		sprite->pos.x - player.dir.x * sprite->pos.y);
	sprite->transform.y = inv_det * (-player.plane.y *
		sprite->pos.x + player.plane.x * sprite->pos.y);
	sprite->sprite_screen = (int)(config.res.x - config.res.x / 2 *
		(1 + sprite->transform.x / sprite->transform.y));
}