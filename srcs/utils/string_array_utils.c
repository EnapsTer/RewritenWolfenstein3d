/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_dim_array_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 14:35:12 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/09 14:35:13 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int 	str_arr_len(char **arr)
{
	int	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

int		str_arr_append(char ***arr, char *line)
{
	char **temp;
	int i;

	i = -1;
	if (!(temp = (char **)malloc(sizeof(char *) * (str_arr_len(*arr) + 2))))
		return (ERROR);
	if (!(*arr))
		temp[++i] = line;
	else
	{
		while ((*arr)[++i])
			temp[i] = (*arr)[i];
		temp[i] = line;
		free(*arr);
	}
	temp[++i] = NULL;
	char *str = temp[i];
	*arr = temp;
	return (TRUE);
}

void 	free_str_arr(char ***arr)
{
	int	i;

	i = 0;
	char *line;
	if (*arr == NULL)
		return;
	while ((*arr)[i])
	{
		line = (*arr)[i];
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}