/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:30:36 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/22 16:30:40 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "string_array_utils.h"
#include "libft.h"
#include "mlx.h"

int		count_sprites(char **map)
{
	int 	count;
	int 	i;
	int 	j;
	int 	len;

	i = 0;
	len = str_arr_len(map);
	count = 0;
	while (i < len)
	{
		j = 0;
		while (j < (int)ft_strlen(map[i]))
		{
			if (map[i][j] == '2')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	write_sprite_array(t_sprite *sprite_arr, char **map)
{
	int 	i;
	int 	j;
	int		index;
	int 	len;

	i = 0;
	index = 0;
	len = str_arr_len(map);
	while (i < len)
	{
		j = 0;
		while (j < (int)ft_strlen(map[i]))
		{
			if (map[i][j] == '2')
			{
				sprite_arr[index].pos.x = j + 0.5;
				sprite_arr[index].pos.y = i + 0.5;
				index++;
			}
			j++;
		}
		i++;
	}
}

void	init_sprites(t_sprites *sprites, t_config config, void *mlx)
{
	int 	sprites_cnt;

	sprites_cnt = count_sprites(config.map);
	sprites->sprites_count = sprites_cnt;
	sprites->sprite_arr = (t_sprite *)malloc(sizeof(t_sprite)
			* (sprites_cnt + 1));
	if (!sprites->sprite_arr || !is_xpm(config.path.sprite))
		send_error("Error");
	write_sprite_array(sprites->sprite_arr, config.map);
	sprites->texture.img.img = mlx_xpm_file_to_image(
			mlx, config.path.sprite,
			&sprites->texture.width,
			&sprites->texture.height
	);
	if (!sprites->texture.img.img)
		send_error("Can't open sprite texture");
	sprites->texture.img.addr = mlx_get_data_addr(
			sprites->texture.img.img,
			&sprites->texture.img.bits_per_pixel,
			&sprites->texture.img.line_length,
			&sprites->texture.img.endian
	);
}