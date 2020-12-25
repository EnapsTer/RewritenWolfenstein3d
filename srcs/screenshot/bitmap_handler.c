/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:44:18 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/24 17:44:22 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "cub3d.h"

static int		create_clean_file(const char *name)
{
	int		fd;

	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd < 0)
		send_error("ERROR: can't create file\n");
	return (fd);
}

static void		write_img(int fd, t_game game)
{
	int32_t		y;
	int32_t		x;
	int			color;

	y = game.config.res.y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < game.config.res.x)
		{
			color = *(int*)(game.mlx.img.addr + (y * game.mlx.img.line_length +
								  x * (game.mlx.img.bits_per_pixel / 8)));
			write(fd, &color, 4);
			x++;
		}
		y--;
	}
}

void			do_screenshot(t_config config)
{
	int		fd;
	void	*bitmap;
	t_game	game;

	fd = create_clean_file("cub3d.bmp");
	init_space(&game, config);
	game_render(&game);
	bitmap = init_bitmap(&game);
	write(fd, bitmap, 54);
	write_img(fd, game);
	close(fd);
	finish_game(&game);
}