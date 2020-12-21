/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:55:44 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/14 11:55:47 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "color_utils.h"
#include "string_array_utils.h"

/*
**	Config initialization
*/

void	init_config(t_config *config)
{
	config->res.x = -1;
	config->res.y = -1;
	config->floor_color = get_rgb(-1, -1, -1);
	config->ceil_color = get_rgb(-1, -1, -1);
	config->path.no = NULL;
	config->path.so = NULL;
	config->path.we = NULL;
	config->path.ea = NULL;
	config->path.sprite = NULL;
	config->map = NULL;
}

/*
**	Frees the config
*/
void	free_config(t_config *config)
{
	if (config->path.no)
		free(config->path.no);
	if (config->path.so)
		free(config->path.so);
	if (config->path.we)
		free(config->path.we);
	if (config->path.ea)
		free(config->path.ea);
	if (config->path.sprite)
		free(config->path.sprite);
	if (config->map)
		free_str_arr(&config->map);
}

void	free_lines(char ***arr, char **line)
{
	free_str_arr(arr);
	free(*line);
	*arr = NULL;
	*line = NULL;
}