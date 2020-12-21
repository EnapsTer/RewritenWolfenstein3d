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
#include <stdio.h> // DELETE
#include <fcntl.h>

//init keys
//обработать .cub
// на корректные флаги
// доделать обработку разрешения
int main(int argc, char **argv)
{
	int			fd;
	t_config	config;

	fd = open(argv[1], O_RDONLY);
	if (get_config(fd, &config) == ERROR)
	{
		printf("map error bliat");
		exit(-1);
	}
	game_init(config);
}
