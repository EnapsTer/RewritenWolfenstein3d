/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlind <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 11:29:10 by aherlind          #+#    #+#             */
/*   Updated: 2020/12/11 11:29:12 by aherlind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_ARRAY_UTILS_H
#define STRING_ARRAY_UTILS_H

int 	str_arr_len(char **arr);

int		str_arr_append(char ***arr, char *line);

void 	free_str_arr(char ***arr);
#endif
