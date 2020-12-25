/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 15:11:46 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/25 15:11:49 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "string_array_utils.h"
#include "libft.h"

/*
**	Return true if config handle is successful
*/

static int	handle_configs(char **settings, t_config *config)
{
	if (!ft_strcmp(settings[0], "R"))
		return (get_resolution(&config->res, settings));
	else if (!ft_strcmp(settings[0], "NO"))
		return (get_texture(&config->path.no, settings));
	else if (!ft_strcmp(settings[0], "SO"))
		return (get_texture(&config->path.so, settings));
	else if (!ft_strcmp(settings[0], "WE"))
		return (get_texture(&config->path.we, settings));
	else if (!ft_strcmp(settings[0], "EA"))
		return (get_texture(&config->path.ea, settings));
	else if (!ft_strcmp(settings[0], "S"))
		return (get_texture(&config->path.sprite, settings));
	else if (!ft_strcmp(settings[0], "F"))
		return (get_color(&config->floor_color, settings));
	else if (!ft_strcmp(settings[0], "C"))
		return (get_color(&config->ceil_color, settings));
	else
		return (ERROR);
}

/*
**	Return true if map is start
*/

static BOOL	is_map_line(char *line)
{
	if (!*line)
		return (ERROR);
	while (*line == ' ' || ft_strcnt("NSWE102", *line))
		line++;
	return (*line == '\0' ? TRUE : ERROR);
}

/*
**	Return true if config is full without map
*/

static BOOL	is_full_config(t_config *config)
{
	if (config->res.x != -1 && config->res.y != -1 &&
		config->ceil_color.color != -65793
		&& config->floor_color.color != -65793 &&
		config->path.no != NULL && config->path.so != NULL &&
		config->path.we != NULL && config->path.ea != NULL &&
		config->path.sprite != NULL)
		return (TRUE);
	return (FALSE);
}

/*
**	Return true if function gets full config
*/

int			get_config(int fd, t_config *config)
{
	char	*line;
	char	**settings;
	int		status;

	init_config(config);
	while (get_next_line(fd, &line) && status != ERROR)
	{
		if ((settings = ft_split(line, ' ')) && (*settings || config->map))
		{
			if (is_full_config(config))
			{
				if ((status = is_map_line(line)) != ERROR)
					status = str_arr_append(&config->map, ft_strdup(line));
			}
			else
				status = handle_configs(settings, config);
		}
		free_lines(&settings, &line);
	}
	if (status != ERROR && (status = is_map_line(line)) != ERROR)
		status = str_arr_append(&config->map, ft_strdup(line));
	free_lines(&settings, &line);
	if (status == ERROR || (status = check_map(config->map)) == ERROR)
		free_config(config);
	return (status);
}
