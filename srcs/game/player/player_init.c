/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 17:58:07 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/17 17:58:09 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "string_array_utils.h"
#include "libft.h"

static t_vector	find_player_pos(t_player *player, char **map)
{
	int			map_lines;
	t_vector	vector;

	vector.x = 0;
	vector.y = 0;
	map_lines = str_arr_len(map);
	while (vector.y != map_lines)
	{
		vector.x = 0;
		while (vector.x != (int)ft_strlen(map[vector.y]))
		{
			if (ft_strcnt("NSWE", map[vector.y][vector.x]))
			{
				player->start_view = map[vector.y][vector.x];
				return (vector);
			}
			vector.x++;
		}
		vector.y++;
	}
	return (vector);
}

static void		init_ns_view(t_player *player)
{
	if (player->start_view == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
		player->plane.x = -0.66;
		player->plane.y = 0;
	}
	else if (player->start_view == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
		player->plane.x = 0.66;
		player->plane.y = 0;
	}
}

static void		init_we_view(t_player *player)
{
	if (player->start_view == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = 0.66;
	}
	if (player->start_view == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = -0.66;
	}
}

void			init_player(t_player *player, t_config config)
{
	t_vector vector;

	vector = find_player_pos(player, config.map);
	player->map_pos = vector;
	player->pos.x = (double)vector.x + 0.5;
	player->pos.y = (double)vector.y + 0.5;
	if (ft_strcnt("NS", player->start_view))
		init_ns_view(player);
	else
		init_we_view(player);
}
