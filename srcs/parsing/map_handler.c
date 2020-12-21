/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 18:15:31 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/14 18:15:37 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "string_array_utils.h"
#include "libft.h"

BOOL	is_valid_interior(int i, int j, char **map)
{
	if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
		return (FALSE);
	if (j > ft_strlen(map[i + 1]) - 1 || j > ft_strlen(map[i - 1]) - 1)
		return (FALSE);
	if (map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
		return (FALSE);
	return (TRUE);
}
BOOL	is_rim(int i, int j, char **map)
{
	int lines_count;

	lines_count = str_arr_len(map);
	if (i == 0 || i == lines_count - 1)
		return (TRUE);
	if (j == 0 || j == ft_strlen(map[i]) - 1)
		return (TRUE);
	return (FALSE);
}

BOOL	is_wall_or_space(char c)
{
	if (c == ' ' || c == '1')
		return (TRUE);
	return (FALSE);
}

int		check_player_pos(char c, BOOL flag)
{
	if (ft_strcnt("NSWE", c))
	{
		if (flag == TRUE)
			return (ERROR);
		return (TRUE);
	}
	else if (flag == TRUE)
		return (TRUE);
	return (FALSE);
}


int		check_map(char **map)
{
	int		lines_count;
	int		i;
	int		j;
	BOOL	status;

	i = 0;
	status = FALSE;
	lines_count = str_arr_len(map);
	while(i < lines_count)
	{
		j = 0;
		while(j < ft_strlen(map[i]))
		{
			if (!is_wall_or_space(map[i][j]))
				if (is_rim(i, j, map) || !is_valid_interior(i, j, map))
					return (ERROR);
			if ((status = check_player_pos(map[i][j], status)) == ERROR)
				return (ERROR);
			j++;
		}
		i++;
	}
	return (status == TRUE ? TRUE : ERROR);
}
