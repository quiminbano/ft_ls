/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_acl_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:31:43 by corellan          #+#    #+#             */
/*   Updated: 2024/06/01 01:29:36 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

static char	**split_acl(char *acl_at)
{
	char	**temp_split;
	char	*temp_arr;

	temp_split = ft_split(acl_at, '\n');
	if (!temp_split)
		return (NULL);
	if (ft_split_length(temp_split) < 2)
	{
		ft_free_split(temp_split);
		temp_split = NULL;
		return (NULL);
	}
	temp_arr = ft_strdup(temp_split[1]);
	if (!temp_arr)
	{
		ft_free_split(temp_split);
		temp_split = NULL;
		return (NULL);
	}
	ft_free_split(temp_split);
	temp_split = NULL;
	temp_split = ft_split(temp_arr, ':');
	ft_del_mem((void **)(&temp_arr));
	return (temp_split);
}

void	print_acl(int *ret_err, char **acl_at)
{
	char	**temp_split;

	temp_split = split_acl((*acl_at));
	if (!temp_split)
	{
		(*ret_err) = -1;
		return ;
	}
	if (ft_split_length(temp_split) < 6)
	{
		ft_free_split(temp_split);
		temp_split = NULL;
		ft_printf(" 0: acl incomplete\n");
		return ;
	}
	ft_printf(" 0: group:%s %s %s\n", temp_split[2], temp_split[4], \
		temp_split[5]);
	ft_free_split(temp_split);
	temp_split = NULL;
}

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
