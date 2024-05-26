/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_col_format_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:47:11 by corellan          #+#    #+#             */
/*   Updated: 2024/05/26 22:13:29 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

static void	pad_name(t_ls *ls, t_list **begin)
{
	t_list		*tmp;
	t_fileinfo	*info;
	size_t		name;

	if (!begin || !(*begin))
		return ;
	tmp = *begin;
	ft_bzero(&(ls->pad), sizeof(ls->pad));
	while (tmp)
	{
		name = ft_strlen(((t_fileinfo *)(tmp->content))->name);
		if (name > ls->pad.pad_name)
			ls->pad.pad_name = name;
		tmp = tmp->next;
	}
	ls->pad.pad_name += (TABSPACE - (ls->pad.pad_name % TABSPACE));
	tmp = *begin;
	while (tmp)
	{
		info = (t_fileinfo *)tmp->content;
		name = ft_strlen(info->name);
		name += (TABSPACE - (name % TABSPACE));
		info->tab_pad = (((ls->pad.pad_name - name) + TABSPACE) / TABSPACE);
		tmp = tmp->next;
	}
}

static void	populate_array(t_list **begin, t_colformat *col_inf, t_list ***arr)
{
	t_list	*tmp;
	t_list	*next;
	size_t	iter_col;
	size_t	iter_node;

	tmp = *begin;
	iter_col = 0;
	while ((iter_col < col_inf->ammount_col) && tmp)
	{
		iter_node = 0;
		(*arr)[iter_col] = tmp;
		while ((iter_node < col_inf->ammount_node) && tmp)
		{
			tmp = tmp->next;
			iter_node++;
		}
		if (tmp)
		{
			next = tmp->next;
			tmp->next = NULL;
			tmp = next;
		}
		iter_col++;
	}
}

static int	print_arr(t_ls *ls, t_list **arr, size_t nodes)
{
	t_list		**copy;
	t_fileinfo	*info;
	size_t		index_arr;
	size_t		index_nodes;

	copy = dup_arr_lst(arr);
	if (!copy)
		return (-1);
	index_nodes = 0;
	while (index_nodes++ < nodes)
	{
		index_arr = 0;
		while (copy[index_arr])
		{
			info = copy[index_arr]->content;
			if (copy[index_arr + 1])
				ft_printf("%s%.*s", info->name, info->tab_pad, ls->tab_str);
			else
				ft_printf("%s\n", info->name);
			copy[index_arr] = copy[index_arr]->next;
			index_arr++;
		}
	}
	ft_del_mem((void **)(&copy));
	return (0);
}

static int	div_lst_and_print(t_ls *ls, t_list **begin, t_colformat *col_inf)
{
	t_list	**lst_arr;
	int		return_func;

	return_func = 0;
	if (!begin || !(*begin))
		return (return_func);
	if (col_inf->ammount_col > col_inf->lst_size)
		col_inf->ammount_col = col_inf->lst_size;
	col_inf->ammount_node = (col_inf->lst_size / col_inf->ammount_col);
	while ((col_inf->ammount_node * col_inf->ammount_col) < col_inf->lst_size)
		(col_inf->ammount_node)++;
	lst_arr = (t_list **)malloc(sizeof(t_list *) * (col_inf->ammount_col + 1));
	if (!lst_arr)
		return (-1);
	lst_arr[col_inf->ammount_col] = NULL;
	populate_array(begin, col_inf, &lst_arr);
	if (print_arr(ls, lst_arr, col_inf->ammount_node) == -1)
		return_func = -1;
	delete_lst_arr(&lst_arr);
	(*begin) = NULL;
	return (return_func);
}

int	print_col(t_ls *ls, t_list **begin)
{
	struct winsize	ws;
	int				return_col;
	t_colformat		col_inf;

	if (!((ls->flags_info >> COLFORM) & 1))
		return (0);
	return_col = ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	if (return_col == -1)
		return (-1);
	pad_name(ls, begin);
	if (ws.ws_col < (2 * ls->pad.pad_name))
		return (0);
	col_inf.ammount_col = (ws.ws_col / ls->pad.pad_name);
	col_inf.lst_size = (size_t)ft_lstsize(*begin);
	if (div_lst_and_print(ls, begin, &col_inf) == -1)
		return (-1);
	return (0);
}