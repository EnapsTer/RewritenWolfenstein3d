/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bitmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:44:31 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/24 17:44:33 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_engine.h"

void	set_zero_byts(void *dest, int len)
{
	unsigned char	*cdest;

	cdest = (unsigned char*)dest;
	while (len--)
	{
		*cdest = 0;
		cdest += 1;
	}
}

void	*init_bitmap(t_game *game)
{
	static char		bitmap[54];

	set_zero_byts(bitmap, 54);
	bitmap[0] = 'B';
	bitmap[1] = 'M';
	*((int*)(bitmap + 2)) = game->config.res.x * game->config.res.y * 4 + 54;
	*(int*)(bitmap + 10) = 54;
	*(int*)(bitmap + 14) = 40;
	*(int*)(bitmap + 18) = (int)game->config.res.x;
	*(int*)(bitmap + 22) = (int)game->config.res.y;
	*(bitmap + 26) = 1;
	*(bitmap + 28) = 32;
	return ((void*)bitmap);
}
