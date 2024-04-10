/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_padding.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:13:36 by corellan          #+#    #+#             */
/*   Updated: 2024/04/10 14:30:51 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t	count_padding(void)
{
	struct dirent	*data;
	DIR				*dir;
	size_t			length;
	size_t			result;

	length = 0;
	dir = opendir(".");
	if (!dir)
		return (0);
	while (1)
	{
		data = readdir(dir);
		if (!data)
			break ;
		if (length < data->d_namlen)
			length = data->d_namlen;
	}
	closedir(dir);
	result = ((length / 8) + 1);
	return (result);
}
