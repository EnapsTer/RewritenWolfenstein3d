/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 17:45:21 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/17 17:45:24 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	calculate_dir_x(t_ray *ray, t_player *player)
{
	if (ray->dir.x < 0)
	{
		player->step.x = -1;
		ray->side_dist.x =
				(player->pos.x - player->map_pos.x) * ray->delta_dist.x;
	}
	else
	{
		player->step.x = 1;
		ray->side_dist.x =
				(player->map_pos.x + 1.0 - player->pos.x) * ray->delta_dist.x;
	}
}

static void	calculate_dir_y(t_ray *ray, t_player *player)
{
	if (ray->dir.y < 0)
	{
		player->step.y = -1;
		ray->side_dist.y =
				(player->pos.y - player->map_pos.y) * ray->delta_dist.y;
	}
	else
	{
		player->step.y = 1;
		ray->side_dist.y =
				(player->map_pos.y + 1.0 - player->pos.y) * ray->delta_dist.y;
	}
}

void		init_ray(t_ray *ray, t_player *player, t_config config, int stripe)
{
	double camera;

	camera = 2 * (config.res.x - stripe) / (double)config.res.x - 1;
	ray->dir.x = player->dir.x + player->plane.x * camera;
	ray->dir.y = player->dir.y + player->plane.y * camera;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	calculate_dir_x(ray, player);
	calculate_dir_y(ray, player);
}
