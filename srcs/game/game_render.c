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


double dirX = 0, dirY = 1; //initial direction vector
double posX = 23 + 0.5, posY = 2 + 0.5;  //x and y start position
double planeX = 0.66, planeY = 0; //the 2d raycaster version of camera plane

BOOL	game_render(t_game *game)
{
	render_sky(game);
	render_floor(game);

	for(int x = 0; x < game->config.res.x; x++)
	{
		game->player.map_pos.x = (int)game->player.pos.x;
		game->player.map_pos.y = (int)game->player.pos.y;
		init_ray(&game->ray, &game->player, game->config, x);
		raycast(&game->ray, &game->player, game->config);
		render_textures(game, x);
//		render_ray(game, x);
	}

	printf("----------------- x = %d ---------------\n", c);
	printf("rayDir = %f %f\n", game->ray.dir.x , game->ray.dir.y);
	printf("raySideDist = %f %f\n", game->ray.side_dist.x, game->ray.side_dist.y);
	printf("rayDeltaDist = %f %f\n", game->ray.delta_dist.x, game->ray.delta_dist.y);
	printf("ray draw start = %d\n", game->ray.draw_start);
	printf("ray draw end = %d\n\n", game->ray.draw_end);

	printf("playerDir = %f %f\n", game->player.dir.x, game->player.dir.y);
	printf("playerPlane = %f %f\n", game->player.plane.x, game->player.plane.y);
	printf("playerPos = %f %f\n", game->player.pos.x, game->player.pos.y);
	printf("playerMapPos = %d %d\n", game->player.map_pos.x, game->player.map_pos.y);
	printf("playerStep = %d %d\n", game->player.step.x, game->player.step.y);
	move_player(&game->player, game->keys, game->config);


	//----------------------------------------------------------------//



//	int w = game->config.res.x;
//	int h = game->config.res.y;
//	//draw sky
//
//	for(int x = 0; x < game->config.res.x; x++)
//	{
//		//calculate ray position and direction
//		double cameraX = 2 * (w - x) / (double)w - 1; //x-coordinate in camera space
//		double rayDirX = dirX + planeX * cameraX;
//		double rayDirY = dirY + planeY * cameraX;
//		//which box of the map we're in
//		int mapX = (int)posX;
//		int mapY = (int)posY;
//
//		//length of ray from current position to next x or y-side
//		double sideDistX;
//		double sideDistY;
//
//		//length of ray from one x or y-side to next x or y-side
//		double deltaDistX = fabs(1 / rayDirX);
//		double deltaDistY = fabs(1 / rayDirY);
//
//		//what direction to step in x or y-direction (either +1 or -1)
//		int stepX;
//		int stepY;
//
//		//calculate step and initial sideDist
//		if(rayDirX < 0)
//		{
//			stepX = -1;
//			sideDistX = (posX - mapX) * deltaDistX;
//		}
//		else
//		{
//			stepX = 1;
//			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//		}
//
//		if(rayDirY < 0)
//		{
//			stepY = -1;
//			sideDistY = (posY - mapY) * deltaDistY;
//		}
//		else
//		{
//			stepY = 1;
//			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//		}
//
//		//perform DDA
//		int side; //was a NS or a EW wall hit?
//		int hit = 0; //was there a wall hit?
//		while (hit == 0)
//		{
//			//jump to next map square, OR in x-direction, OR in y-direction
//			if(sideDistX < sideDistY)
//			{
//				sideDistX += deltaDistX;
//				mapX += stepX;
//				side = 0;
//			}
//			else
//			{
//				sideDistY += deltaDistY;
//				mapY += stepY;
//				side = 1;
//			}
//			//Check if ray has hit a wall
//			if(game->config.map[mapY][mapX] == '1') hit = 1;
//		}
//		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
//		double perpWallDist;
//		if(side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
//		else          perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
//
//		//Calculate height of line to draw on screen
//		int lineHeight = (int)(h / perpWallDist);
//
//		//calculate lowest and highest pixel to fill in current stripe
//		int drawStart = -lineHeight / 2 + h / 2;
//		if(drawStart < 0)drawStart = 0;
//		int drawEnd = lineHeight / 2 + h / 2;
//		if(drawEnd >= h)drawEnd = h - 1;
//
////		if (x == 6)
////			exit(1);
////		draw the pixels of the stripe as a vertical line
//		int j = 0, i = 0;
//		j = drawStart;
//		while (j != drawEnd)
//		{
//			pixel_put(&game->mlx.img, x, j, 0x000054a6);
//			j++;
//		}
//		if (x == 1919)
//		{
//
//		printf("----------------- x = %d ---------------\n", c);
//		printf("rayDir = %f %f\n", rayDirX, rayDirY);
//		printf("raySideDist = %f %f\n", sideDistX, sideDistY);
//		printf("rayDeltaDist = %f %f\n", deltaDistX, deltaDistY);
//		printf("ray draw start = %d\n", drawStart);
//		printf("ray draw end = %d\n\n", drawEnd);
//
//		printf("playerDir = %f %f\n", dirX, dirY);
//		printf("playerPlane = %f %f\n", planeX, planeY);
//		printf("playerPos = %f %f\n", posX, posY);
//		printf("playerMapPos = %d %d\n", mapX, mapY);
//		printf("playerStep = %d %d\n", stepX, stepY);
//		if (c == 4)
//			exit(1);
//		}
//	}
//
//
////	speed modifiers
//	double moveSpeed = MOVE_SPEED; //the constant value is in squares/second
//	double rotSpeed =  ROT_SPEED; //the constant value is in radians/second
//	//move forward if no wall in front of you
//	if(game->keys.w == 1)
//	{
//		if(is_passable(game->config.map[(int)(posY + dirY * moveSpeed)][(int)posX]))
//			posY += dirY * moveSpeed;
//		if(is_passable(game->config.map[(int)posY][(int)(posX + dirX * moveSpeed)]))
//			posX += dirX * moveSpeed;
//	}
//	//move backwards if no wall behind you
//	if(game->keys.s == 1)
//	{
//		if(game->config.map[(int)(posY - dirY * moveSpeed)][(int)(posX)] == '0') posY -= dirY * moveSpeed;
//		if(game->config.map[(int)(posY)][(int)(posX - dirX * moveSpeed)] == '0') posX -= dirX * moveSpeed;
//	}
//	//rotate to the right
//	if(game->keys.left == 1)
//	{
//		//both camera direction and camera plane must be rotated
//		double oldDirX = dirX;
//		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
//		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
//		double oldPlaneX = planeX;
//		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
//		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
//	}
//	//rotate to the left
//	if(game->keys.right == 1)
//	{
//		//both camera direction and camera plane must be rotated
//		double oldDirX = dirX;
//		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
//		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
//		double oldPlaneX = planeX;
//		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
//		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
//	}



	c++;
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.img.img, 0, 0);
	return (TRUE);
}
