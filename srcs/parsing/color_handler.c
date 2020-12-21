/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 18:14:06 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/09 18:14:08 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "string_array_utils.h"
#include "color_utils.h"
#include "libft.h"

static BOOL	check_color(char **strs)
{
	int		r;
	int		g;
	int		b;

	r = ft_atoi(strs[0]);
	g = ft_atoi(strs[1]);
	b = ft_atoi(strs[2]);
	if (get_num_len(r) != ft_strlen(strs[0]) ||
		get_num_len(g) != ft_strlen(strs[1]) ||
		get_num_len(b) != ft_strlen(strs[2]) ||
		r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (FALSE);
	return (TRUE);
}

int 	get_color(t_color *color, char **color_arr)
{
	char	**strs;

	strs = ft_split(color_arr[1], ',');
	if (str_arr_len(color_arr) != 2 || ft_strcnt(color_arr[1], ',') != 2 ||
		str_arr_len(strs) != 3 || !check_color(strs) ||
		!is_equal_colors(*color, get_rgb(-1, -1 , -1)) )
		return (ERROR);
	*color = get_rgb(ft_atoi(strs[0]),ft_atoi(strs[1]),ft_atoi(strs[2]));
	free_str_arr(&strs);
	return (TRUE);
}