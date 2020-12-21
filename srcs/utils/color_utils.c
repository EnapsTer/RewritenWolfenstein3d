/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 11:25:39 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/11 11:25:42 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_color		get_rgb(int r, int g, int b)
{
	t_color color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.color = r * 256 * 256 + g * 256 + b;
	return (color);
}

BOOL		is_equal_colors(t_color color1, t_color color2)
{
	if (color1.r == color2.r && color1.g == color2.g && color1.b == color2.b)
		return (TRUE);
	return (FALSE);
}