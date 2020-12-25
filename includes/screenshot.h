/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 17:46:21 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/24 17:46:24 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREENSHOT_H
# define SCREENSHOT_H

void	*init_bitmap(t_game *game);

void	set_zero_byts(void *dest, int len);

#endif
