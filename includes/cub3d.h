/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 11:28:25 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/11 11:28:39 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
# define ERROR -1
# define TRUE 1
# define FALSE 0
# define BOOL int

#include <stdio.h> //delete
#include <fcntl.h>//delete
#include <unistd.h> //delete
#include <stdlib.h>
#include "parse.h"
#include "game_engine.h"

int		get_config(int fd, t_config *config);

BOOL	init_game(t_config config);

void	pixel_put(t_data *data, int x, int y, int color);

void	init_keys(t_keys *keys);

BOOL is_passable(char c);//delete

void	send_error(char *str);

BOOL	is_xpm(char	*path);

int		finish_game(t_game *game);

void			*init_bitmap(t_game *game);

void			do_screenshot(t_config config);
#endif
