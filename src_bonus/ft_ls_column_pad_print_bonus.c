/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_column_pad_print_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:42:38 by corellan          #+#    #+#             */
/*   Updated: 2024/06/28 09:43:16 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

void	calculate_pad_columns(t_ls *ls, t_list **begin)
{
	size_t		name;
	t_list		*tmp;
	t_fileinfo	*info;

	if (!begin || !(*begin))
		return ;
	tmp = *begin;
	if (!((ls->flags_info >> GEEFLAG) & 1))
		ls->pad.pad_name += (TABSPACE - (ls->pad.pad_name % TABSPACE));
	else
		ls->pad.pad_name += 1;
	while (tmp)
	{
		info = tmp->content;
		if (!((ls->flags_info >> GEEFLAG) & 1))
		{
			name = ft_strlen(info->name);
			name += (TABSPACE - (name % TABSPACE));
			info->tab_pad = (((ls->pad.pad_name - name) + TABSPACE) / TABSPACE);
		}
		handle_colors(info, ls, info->lstat.st_mode);
		tmp = tmp->next;
	}
}

static void	print_columns(t_ls *ls, t_list **copy, size_t index_arr)
{
	t_fileinfo	*info;
	size_t		length_name;
	size_t		length_reset;

	info = copy[index_arr]->content;
	length_name = ft_strlen(info->name);
	length_reset = ft_strlen(info->end);
	if (copy[index_arr + 1] && !((ls->flags_info >> GEEFLAG) & 1))
		ft_printf("%s%.*s", info->name, info->tab_pad, ls->tab_str);
	else if (copy[index_arr + 1] && ((ls->flags_info >> GEEFLAG) & 1))
		ft_printf("%s%s%-*s", info->color, info->name, \
			((ls->pad.pad_name + length_reset) - length_name), info->end);
	else
		ft_printf("%s%s%s\n", info->color, info->name, info->end);
	copy[index_arr] = copy[index_arr]->next;
}

int	print_arr(t_ls *ls, t_list **arr, size_t nodes)
{
	t_list		**copy;
	size_t		index_arr;
	size_t		index_nodes;

	copy = dup_arr_lst(arr);
	if (!copy)
		return (-1);
	index_nodes = 0;
	while (index_nodes < nodes)
	{
		index_arr = 0;
		while (copy[index_arr])
		{
			print_columns(ls, copy, index_arr);
			index_arr++;
		}
		index_nodes++;
	}
	ft_del_mem((void **)(&copy));
	return (0);
}
