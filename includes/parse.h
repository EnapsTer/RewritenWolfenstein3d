/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 11:28:56 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/11 11:28:58 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct	s_res
{
	int x;
	int y;
}				t_res;

typedef struct	s_color
{
	int r;
	int g;
	int b;
	int color;
}				t_color;

typedef struct	s_path
{
	char *no;
	char *so;
	char *we;
	char *ea;
	char *sprite;
}				t_path;

typedef struct	s_config
{
	t_res		res;
	t_color		floor_color;
	t_color		ceil_color;
	t_path		path;
	char		**map;
}				t_config;

int				get_resolution(t_res *res, char **res_arr);

int				get_texture(char **texture, char **texture_arr);

int				get_color(t_color *color, char **color_arr);

void			init_config(t_config *config);

void			free_config(t_config *config);

void			free_lines(char ***arr, char **line);

int				check_map(char **map);

#endif
