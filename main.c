/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 12:22:39 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/08 12:22:41 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>

BOOL	is_cub(char *path)
{
	int i;

	i = 0;
	while (i < (int)ft_strlen(path))
	{
		if (ft_strcmp(path + i, ".cub") == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int		main(int argc, char **argv)
{
	int			fd;
	t_config	config;

	if (argc < 2 || argc > 3)
		send_error("Incorrect number of arguments");
	if (!is_cub(argv[1]))
		send_error("Not .cub file");
	if (argc == 3 && ft_strcmp(argv[2], "--save"))
		send_error("Invalid flag name try --save");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		send_error("Incorrect file");
	if (get_config(fd, &config) == ERROR)
		send_error("Map error!");
	if (argc == 2)
		init_game(config);
	else
		do_screenshot(config);
}
