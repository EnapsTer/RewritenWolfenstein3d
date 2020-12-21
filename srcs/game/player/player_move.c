/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 19:57:59 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/17 19:58:04 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

BOOL is_passable(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '0')
		return (TRUE);
	return (FALSE);
}

void	move_x(t_player *player, t_keys keys, t_config config)
{
	double i;
	double j;

	if (keys.w == 1)
	{
		i = (player->pos.y + player->dir.y * MOVE_SPEED);
		j = (player->pos.x);
		if (is_passable(config.map[(int)i][(int)j]))
			player->pos.y += player->dir.y * MOVE_SPEED;
		i = (int)(player->pos.y);
		j = (int)(player->pos.x + player->dir.x * MOVE_SPEED);
		if (is_passable(config.map[(int)i][(int)j]))
			player->pos.x += player->dir.x * MOVE_SPEED;
	}
	if (keys.s == 1)
	{
		i = (int)(player->pos.y - player->dir.y * MOVE_SPEED);
		j = (int)(player->pos.x);
		if (is_passable(config.map[(int)i][(int)j]))
			player->pos.y -= player->dir.y * MOVE_SPEED;
		i = (int)(player->pos.y);
		j = (int)(player->pos.x - player->dir.x * MOVE_SPEED);
		if (is_passable(config.map[(int)i][(int)j]))
			player->pos.x -= player->dir.x * MOVE_SPEED;
	}
}

void	move_y(t_player *player, t_keys keys, t_config config)
{
	int i;
	int j;

	if (keys.a == 1)
	{
		i = (int)(player->pos.y + player->plane.y * MOVE_SPEED);
		j = (int)(player->pos.x);
		if (is_passable(config.map[i][j]))
			player->pos.y += player->plane.y * MOVE_SPEED;
		i = (int)(player->pos.y);
		j = (int)(player->pos.x + player->plane.x * MOVE_SPEED);
		if (is_passable(config.map[i][j]))
			player->pos.x += player->plane.x * MOVE_SPEED;
	}
	if (keys.d == 1)
	{
		i = (int)(player->pos.y - player->plane.y * MOVE_SPEED);
		j = (int)(player->pos.x);
		if (is_passable(config.map[i][j]))
			player->pos.y -= player->plane.y * MOVE_SPEED;
		i = (int)(player->pos.y);
		j = (int)(player->pos.x - player->plane.x * MOVE_SPEED);
		if (is_passable(config.map[i][j]))
			player->pos.x -= player->plane.x * MOVE_SPEED;
	}
}

void	rotate_x(t_d_vector *dir, t_d_vector *plane, t_keys keys)
{
	double temp_dir_x;
	double temp_plane_x;
	if (keys.left == 1)
	{
		temp_dir_x = dir->x;
		temp_plane_x = plane->x;
		dir->x = dir->x * cos(-ROT_SPEED) - dir->y * sin(-ROT_SPEED);
		dir->y = temp_dir_x * sin(-ROT_SPEED) + dir->y * cos(-ROT_SPEED);
		plane->x = plane->x * cos(-ROT_SPEED) - plane->y * sin(-ROT_SPEED);
		plane->y = temp_plane_x * sin(-ROT_SPEED) + plane->y * cos(-ROT_SPEED);
	}
	if (keys.right == 1)
	{
		temp_dir_x = dir->x;
		temp_plane_x = plane->x;
		dir->x = dir->x * cos(ROT_SPEED) - dir->y * sin(ROT_SPEED);
		dir->y = temp_dir_x * sin(ROT_SPEED) + dir->y * cos(ROT_SPEED);
		plane->x = plane->x * cos(ROT_SPEED) - plane->y * sin(ROT_SPEED);
		plane->y = temp_plane_x * sin(ROT_SPEED) + plane->y * cos(ROT_SPEED);
	}
}

void	move_player(t_player *player, t_keys keys, t_config config)
{
	move_x(player, keys, config);
	move_y(player, keys, config);
	rotate_x(&player->dir, &player->plane, keys);
}