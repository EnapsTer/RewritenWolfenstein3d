/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 15:40:08 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/09 15:40:10 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "string_array_utils.h"
#include "libft.h"
#include "fcntl.h"

static BOOL	check_texture(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	close(fd);
	if (fd == -1)
		return (FALSE);
	return (TRUE);
}

int			get_texture(char **texture, char **texture_arr)
{
	if (*texture || !check_texture(texture_arr[1]) ||
			str_arr_len(texture_arr) != 2)
		return (ERROR);
	*texture = ft_strdup(texture_arr[1]);
	return (TRUE);
}
