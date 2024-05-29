/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_acl_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:31:43 by corellan          #+#    #+#             */
/*   Updated: 2024/05/29 19:12:35 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

static size_t	get_size_alloc_acl(t_fileinfo *info, int *ret_er, char **acl_at)
{
	size_t	length_acl;
	size_t	size_alloc;
	char	*acl;

	acl = (*acl_at);
	size_alloc = 0;
	while (length_acl < info->acl_size)
	{
		length_acl = (ft_strlen(acl) + 1);
		acl += length_acl;
		size_alloc++;
	}
	return (size_alloc);
}

void	process_acl(t_fileinfo *info, int *ret_err, char **acl_at)
{
	size_t	size_alloc;

	if (info->acl_usage != 1)
		return ;
	size_alloc = 0;
	(*acl_at) = acl_to_text(info->acl, &(info->acl_size));
	if (!(*acl_at))
	{
		(*ret_err) = -1;
		return ;
	}
	size_alloc = get_size_alloc_acl(info, ret_err, acl_at);
	
}
