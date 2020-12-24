/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 16:49:05 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/24 16:49:07 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_double_vectors(int *order, double *distance, int len)
{
	int	i;
	int	j;
	double	temp;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (distance[i] < distance[j])
			{
				temp = distance[i];
				distance[i] = distance[j];
				distance[j] = temp;
				temp = (double)order[i];
				order[i] = order[j];
				order[j] = (int)temp;
			}
			j++;
		}
		i++;
	}
}