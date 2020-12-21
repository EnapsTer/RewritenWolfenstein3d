/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 19:19:56 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/17 19:19:59 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void calc_for_render(t_ray *ray, t_player *player, t_config config)
{
	double	temp;

	if (ray->wall_side == 0)
	{
		temp = (player->map_pos.x - player->pos.x + (1 - player->step.x) / 2);
		ray->wall_dist = temp / ray->dir.x;
	}
	else
	{
		temp = (player->map_pos.y - player->pos.y + (1 - player->step.y) / 2);
		ray->wall_dist = temp / ray->dir.y;
	}
	ray->height = (int)(config.res.y / ray->wall_dist);
	ray->draw_start = -ray->height / 2 + config.res.y / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->height / 2 + config.res.y / 2;
	if (ray->draw_end >= config.res.y || ray->draw_end < 0)
		ray->draw_end = config.res.y; // исправлял ray->draw_end = config.res.y - 1;
}

void		raycast(t_ray *ray, t_player *player, t_config config)
{
	int	wall_hit;

	wall_hit = 0;
	while(wall_hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			player->map_pos.x += player->step.x;
			ray->wall_side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			player->map_pos.y += player->step.y;
			ray->wall_side = 1;
		}
		if(config.map[player->map_pos.y][player->map_pos.x] == '1')
			wall_hit = 1;
	}
	calc_for_render(ray, player, config);
}