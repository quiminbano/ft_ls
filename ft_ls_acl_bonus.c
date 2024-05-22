/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_acl_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:31:43 by corellan          #+#    #+#             */
/*   Updated: 2024/05/22 12:23:19 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

void	process_acl(t_fileinfo *info, int *ret_err, char **acl_at)
{
	if (info->acl_usage != 1)
		return ;
	(*acl_at) = acl_to_text(info->acl, &(info->acl_size));
	if (!(*acl_at))
	{
		(*ret_err) = -1;
		return ;
	}
}
