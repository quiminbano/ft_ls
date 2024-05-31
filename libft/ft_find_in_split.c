/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_in_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 01:04:03 by corellan          #+#    #+#             */
/*   Updated: 2024/06/01 01:08:47 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_find_in_split(char **split, char *needle)
{
	size_t	i;

	i = 0;
	if (!needle)
		return (ft_split_length(split));
	while (split[i])
	{
		if (!ft_strcmp(split[i], needle))
			break ;
		i++;
	}
	return (i);
}
