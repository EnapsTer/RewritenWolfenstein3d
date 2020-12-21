/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 12:02:50 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/21 12:02:54 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

t_texture	*select_texture(t_textures *textures, t_ray ray, t_player player)
{
	if (ray.wall_side == 1)
	{
		if (player.step.y > 0)
			return (&textures->no);
		if (player.step.y < 0)
			return (&textures->so);
	}
	if (ray.wall_side == 0)
	{
		if (player.step.x > 0)
			return (&textures->we);
		if (player.step.x < 0)
			return (&textures->ea);
	}
	return (NULL);
}

void		get_texture_data(t_texture *texture, t_ray ray, t_player player, t_config config)
{
	double	wall_hit_x;

	if (ray.wall_side == 0)
		wall_hit_x = player.pos.y + ray.wall_dist * ray.dir.y;
	else
		wall_hit_x = player.pos.x + ray.wall_dist * ray.dir.x;
	wall_hit_x = 1 - (wall_hit_x - floor(wall_hit_x));
	texture->pos.x = (int)(wall_hit_x * (double)(texture->width));
	if (ray.wall_side == 0 && ray.dir.x > 0)
		texture->pos.x = texture->width - texture->pos.x - 1;
	if (ray.wall_side == 1 && ray.dir.y < 0)
		texture->pos.x = texture->width - texture->pos.x - 1;
	texture->step = 1.0 * texture->height / ray.height;
	texture->start_pos = (ray.draw_start - config.res.y / 2 + ray.height / 2) *
			texture->step;
	texture->num = config.map[player.map_pos.y][player.map_pos.x] - 1;
}



