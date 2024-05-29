/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_column_pad_print_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:42:38 by corellan          #+#    #+#             */
/*   Updated: 2024/05/29 15:49:36 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

#ifdef __APPLE__

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

void	print_columns(t_ls *ls, t_list **copy, size_t index_arr)
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

#else

void	calculate_pad_columns(t_ls *ls, t_list **begin)
{
	size_t		name;
	t_list		*tmp;
	t_fileinfo	*info;

	if (!begin || !(*begin))
		return ;
	tmp = *begin;
	ls->pad.pad_name += (TABSPACE - (ls->pad.pad_name % TABSPACE));
	while (tmp)
	{
		info = tmp->content;
		ls->pad.pad_name += (TABSPACE - (ls->pad.pad_name % TABSPACE));
		name = ft_strlen(info->name);
		name += (TABSPACE - (name % TABSPACE));
		info->tab_pad = (((ls->pad.pad_name - name) + TABSPACE) / TABSPACE);
		handle_colors(info, ls, info->lstat.st_mode);
		tmp = tmp->next;
	}
}

void	print_columns(t_ls *ls, t_list **copy, size_t index_arr)
{
	t_fileinfo	*info;

	info = copy[index_arr]->content;
	if (copy[index_arr + 1])
		ft_printf("%s%s%s%.*s", info->color, info->name, info->end, \
			info->tab_pad, ls->tab_str);
	else
		ft_printf("%s%s%s\n", info->color, info->name, info->end);
	copy[index_arr] = copy[index_arr]->next;
}
#endif
