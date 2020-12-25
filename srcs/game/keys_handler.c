/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:04:41 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/17 13:04:51 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->s = 0;
	keys->a = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
	keys->esc = 0;
}

BOOL	handle_pressed_key(int key, t_game *game)
{
	if (key == KEY_W)
		game->keys.w = 1;
	if (key == KEY_S)
		game->keys.s = 1;
	if (key == KEY_A)
		game->keys.a = 1;
	if (key == KEY_D)
		game->keys.d = 1;
	if (key == KEY_LEFT || key == KEY_Q)
		game->keys.left = 1;
	if (key == KEY_RIGHT || key == KEY_E)
		game->keys.right = 1;
	if (key == ESC)
		finish_game(game);
	return (TRUE);
}

BOOL	handle_unpressed_key(int key, t_game *game)
{
	if (key == KEY_W)
		game->keys.w = 0;
	if (key == KEY_S)
		game->keys.s = 0;
	if (key == KEY_A)
		game->keys.a = 0;
	if (key == KEY_D)
		game->keys.d = 0;
	if (key == KEY_LEFT || key == KEY_Q)
		game->keys.left = 0;
	if (key == KEY_RIGHT || key == KEY_E)
		game->keys.right = 0;
	return (TRUE);
}
