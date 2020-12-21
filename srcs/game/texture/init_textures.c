/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 14:33:41 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/19 14:33:45 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

BOOL	is_xpm(char	*path)
{
	int i;

	i = 0;
	while (i < (int)ft_strlen(path))
	{
		if (ft_strcmp(path + i, ".xpm") == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	init_texture(t_texture *texture, void *mlx)
{
	texture->img.img = mlx_xpm_file_to_image(mlx, texture->path,
										  &texture->width, &texture->height);
	if (texture->img.img == NULL)
		send_error("ERROR! cant open texture file.");
	texture->img.addr = mlx_get_data_addr(
			texture->img.img,
			&texture->img.bits_per_pixel,
			&texture->img.line_length,
			&texture->img.endian
	);
}

void	init_path(t_textures *textures, t_config config)
{
	if (!is_xpm(config.path.no) || !is_xpm(config.path.so) ||
		!is_xpm(config.path.ea) || !is_xpm(config.path.we))
		send_error("ERROR! invalid texture path.");
	textures->no.path = config.path.no;
	textures->so.path = config.path.so;
	textures->we.path = config.path.we;
	textures->ea.path = config.path.ea;
}

void init_textures(t_textures *textures, t_config config, t_mlx *mlx)
{
	init_path(textures, config);
	init_texture(&textures->no, mlx->mlx);
	init_texture(&textures->so, mlx->mlx);
	init_texture(&textures->we, mlx->mlx);
	init_texture(&textures->ea, mlx->mlx);
}