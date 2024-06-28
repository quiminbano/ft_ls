/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_lst_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 09:07:41 by corellan          #+#    #+#             */
/*   Updated: 2024/06/28 09:50:56 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

static size_t	size_arr_lst(t_list **src)
{
	size_t	index;

	index = 0;
	while (src[index])
		index++;
	return (index);
}

void	delete_lst_arr(t_list ***ptr)
{
	size_t	index;

	index = 0;
	while ((*ptr)[index])
	{
		free_lst(&((*ptr)[index]), NULL, NULL);
		(*ptr)[index] = NULL;
		index++;
	}
	ft_del_mem((void **)ptr);
}

t_list	**dup_arr_lst(t_list **src)
{
	size_t	mem_alloc;
	size_t	index;
	t_list	**destination;

	mem_alloc = size_arr_lst(src);
	index = 0;
	destination = (t_list **)malloc(sizeof(t_list *) * (mem_alloc + 1));
	if (!destination)
		return (NULL);
	destination[mem_alloc] = NULL;
	while (src[index])
	{
		destination[index] = src[index];
		index++;
	}
	return (destination);
}

int	free_lst(t_list **dir, t_list **file, t_list **err)
{
	if (dir && *dir)
		ft_lstclear(&(*dir), &delete_fileinfo);
	if (file && *file)
		ft_lstclear(&(*file), &delete_fileinfo);
	if (err && *err)
		ft_lstclear(&(*err), &delete_fileinfo);
	return (-1);
}
