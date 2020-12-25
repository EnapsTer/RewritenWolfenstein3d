/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 11:27:57 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/11 11:28:04 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PROJECT_COLOR_UTILS_H
# define CUB3D_PROJECT_COLOR_UTILS_H

t_color		get_rgb(int r, int g, int b);

BOOL		is_equal_colors(t_color color1, t_color color2);

#endif
