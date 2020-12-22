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
#include <math.h>
#include <tcl.h>
#include "mlx.h"
#include <unistd.h>

void	sort_double_vectors(int *order, double *distance, size_t len)
{
	size_t	i;
	size_t	j;
	double	temp;

	if (len == 0)
		return ;
	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (distance[i] < distance[j])
			{
				temp = distance[i];
				distance[i] = distance[j];
				distance[j] = temp;
				temp = (double)order[i];
				order[i] = order[j];
				order[j] = (int)temp;
			}
			j++;
		}
		i++;
	}
}

void render_textures(t_game *game, int column)
{
	t_texture	*texture;
	int 		y;

	texture = select_texture(&game->textures, game->ray, game->player);
	get_texture_data(texture, game->ray, game->player, game->config);
	y = game->ray.draw_start;
	while (y < game->ray.draw_end)
	{
		texture->pos.y = (int)texture->start_pos & (64 - 1);
		texture->start_pos += texture->step;
		texture->color = ((int *)texture->img.addr)[64 * texture->pos.y + texture->pos.x];
		pixel_put(&game->mlx.img, column, y, texture->color);
		y++;
	}
}

void	render_ray(t_game *game, int column)
{
	int i;

	i = game->ray.draw_start;
	while (i != game->ray.draw_end)
	{
		pixel_put(&game->mlx.img, column, i, 0x000054a6);
		i++;
	}
}

void	render_sky(t_game *game)
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

void	render_floor(t_game *game)
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

int c = 0;


//double dirX = 0, dirY = 1; //initial direction vector
//double posX = 23 + 0.5, posY = 2 + 0.5;  //x and y start position
//double planeX = 0.66, planeY = 0; //the 2d raycaster version of camera plane

BOOL	game_render(t_game *game)
{
	render_sky(game);
	render_floor(game);
	double *ZBuffer;

	ZBuffer = malloc(sizeof(double) * game->config.res.x);
	for(int x = 0; x < game->config.res.x; x++)
	{
		game->player.map_pos.x = (int)game->player.pos.x;
		game->player.map_pos.y = (int)game->player.pos.y;
		init_ray(&game->ray, &game->player, game->config, x);
		raycast(&game->ray, &game->player, game->config);
		render_textures(game, x);

		ZBuffer[x] = game->ray.wall_dist;
//		render_ray(game, x);
	}

	//------------------------------------------------------------------------//
	t_sprites sprites = game->sprites;
	t_sprite *sprite_arr = game->sprites.sprite_arr;
	t_player player = game->player;
	t_ray ray = game->ray;

	int *spriteOrder = (int *)malloc(sizeof(int) * sprites.sprites_count);
	double *spriteDistance = (double *)malloc(sizeof(double) * sprites.sprites_count);

	for(int i = 0; i < sprites.sprites_count; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((player.pos.x - sprite_arr[i].pos.x) * (player.pos.x - sprite_arr[i].pos.x) +
				(player.pos.y - sprite_arr[i].pos.y) * (player.pos.y - sprite_arr[i].pos.y));

	}

	sort_double_vectors(spriteOrder, spriteDistance, sprites.sprites_count);
	for (int i = 0; i < sprites.sprites_count; i++)
	{
		double spriteX = sprite_arr[spriteOrder[i]].pos.x - player.pos.x;
		double spriteY = sprite_arr[spriteOrder[i]].pos.y - player.pos.y;

		double invDet = 1.0 / (player.plane.x * player.dir.y - player.dir.x * player.plane.y);

		double transformX = invDet * (player.dir.y * spriteX - player.dir.x * spriteY);
		double transformY = invDet * (-player.plane.y * spriteX + player.plane.x * spriteY);

		int spriteScreenX = (int)(game->config.res.x - game->config.res.x / 2 * (1 + transformX / transformY));



		int spriteHeight = abs((int)(game->config.res.y / transformY));
		int spriteWidth = abs((int)(game->config.res.y / transformY));
		int drawStartY = -spriteHeight / 2 + game->config.res.y / 2;
		if(drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + game->config.res.y / 2;
		if(drawEndY >= game->config.res.y)
			drawEndY = game->config.res.y - 1;

		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= game->config.res.x)
			drawEndX = game->config.res.x - 1;

		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * sprites.texture.width / spriteWidth) / 256;
			if(transformY > 0 && stripe > 0 && stripe < game->config.res.x && transformY < ZBuffer[stripe])
			{
				for(int y = drawStartY; y < drawEndY; y++)
				{
					int d = y * 256 - game->config.res.y * 128 + spriteHeight * 128;
					int texY = ((d * sprites.texture.width) / spriteHeight) / 256;
					uint32_t color = ((int*)game->sprites.texture.img.addr)[sprites.texture.width * texY + texX];
					if ((color & 0x00FFFFFF) != 9961608)
						pixel_put(&game->mlx.img, stripe, y, color);
				}

			}
		}
	}
//============================================================================//
//	printf("----------------- x = %d ---------------\n", c);
//	printf("rayDir = %f %f\n", game->ray.dir.x , game->ray.dir.y);
//	printf("raySideDist = %f %f\n", game->ray.side_dist.x, game->ray.side_dist.y);
//	printf("rayDeltaDist = %f %f\n", game->ray.delta_dist.x, game->ray.delta_dist.y);
//	printf("ray draw start = %d\n", game->ray.draw_start);
//	printf("ray draw end = %d\n\n", game->ray.draw_end);
//
//	printf("playerDir = %f %f\n", game->player.dir.x, game->player.dir.y);
//	printf("playerPlane = %f %f\n", game->player.plane.x, game->player.plane.y);
//	printf("playerPos = %f %f\n", game->player.pos.x, game->player.pos.y);
//	printf("playerMapPos = %d %d\n", game->player.map_pos.x, game->player.map_pos.y);
//	printf("playerStep = %d %d\n", game->player.step.x, game->player.step.y);
//============================================================================//


	move_player(&game->player, game->keys, game->config);


	//----------------------------------------------------------------//



	c++;
	free(ZBuffer);
	free(spriteOrder);
	free(spriteDistance);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.img.img, 0, 0);
	return (TRUE);
}
