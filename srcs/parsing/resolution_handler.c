/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:09:22 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/09 12:09:24 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "string_array_utils.h"
#include "libft.h"

static BOOL	check_resolution(char *res_str_x, char *res_str_y)
{
	int x;
	int y;

	x = ft_atoi(res_str_x);
	y = ft_atoi(res_str_y);
	if (get_num_len(x) != ft_strlen(res_str_x) ||
		get_num_len(y) != ft_strlen(res_str_y) ||
		x <= 0 || y <= 0)
		return (FALSE);
	return (TRUE);
}
int get_resolution(t_res *res, char **res_arr)
{
	if (str_arr_len(res_arr) != 3 || !check_resolution(res_arr[1], res_arr[2]))
		return (ERROR);
	if (res->x == -1 && res->y == -1)
	{
		res->x = ft_atoi(res_arr[1]);
		res->y = ft_atoi(res_arr[2]);
		if (res->x > 5120 / 2)
			res->x = 5120 / 2;
		if (res->y > 2880 / 2)
			res->y = 2880 / 2;
		return (TRUE);
	}
	return (ERROR);
}