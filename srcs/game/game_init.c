/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:41:15 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/17 12:41:17 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static void	mlx_data_init(t_game *game)
{
	game->mlx.mlx = mlx_init();
	game->mlx.win = mlx_new_window(
			game->mlx.mlx,
			game->config.res.x,
			game->config.res.y,
			"Cub3d");
	game->mlx.img.img = mlx_new_image(
			game->mlx.mlx,
			game->config.res.x,
			game->config.res.y);
	game->mlx.img.addr = mlx_get_data_addr(
			game->mlx.img.img,
			&game->mlx.img.bits_per_pixel,
			&game->mlx.img.line_length,
			&game->mlx.img.endian);
}

void		init_space(t_game *game, t_config config)
{
	game->config = config;
	mlx_data_init(game);
	init_keys(&game->keys);
	init_player(&game->player, game->config);
	init_textures(&game->textures, config, &game->mlx);
	init_sprites(&game->sprites, config, game->mlx.mlx);
}

BOOL		init_game(t_config config)
{
	t_game	game;

	init_space(&game, config);
	mlx_do_key_autorepeatoff(game.mlx.mlx);
	mlx_hook(game.mlx.win, 2, 0, handle_pressed_key, &game);
	mlx_hook(game.mlx.win, 3, 0, handle_unpressed_key, &game);
	mlx_hook(game.mlx.win, 17, 0, finish_game, &game);
	mlx_loop_hook(game.mlx.mlx, game_render, &game);
	mlx_loop(game.mlx.mlx);
	return (TRUE);
}

int			finish_game(t_game *game)
{
	if (game->sprites.sprites_count)
	{
		free(game->sprites.sprite_arr);
		game->sprites.sprite_arr = NULL;
	}
	exit(1);
	return (0);
}
