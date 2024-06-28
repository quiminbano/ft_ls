/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_column_format_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:47:11 by corellan          #+#    #+#             */
/*   Updated: 2024/06/28 10:13:10 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

static void	pad_name_and_add_color(t_ls *ls, t_list **begin)
{
	t_list		*tmp;
	t_fileinfo	*info;
	size_t		name;

	if (!begin || !(*begin))
		return ;
	tmp = *begin;
	while (tmp)
	{
		info = tmp->content;
		name = ft_strlen(info->name);
		if (name > ls->pad.pad_name)
			ls->pad.pad_name = name;
		tmp = tmp->next;
	}
	calculate_pad_columns(ls, begin);
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
			iter_node++;
			if (iter_node < col_inf->ammount_node && tmp)
				tmp = tmp->next;
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

static size_t correct_col_val(t_list **begin, t_colformat *col_inf)
{
	t_list	*tmp;
	size_t	iter_col;
	size_t	iter_node;

	tmp = *begin;
	iter_col = 0;
	while ((iter_col < col_inf->ammount_col) && tmp)
	{
		iter_node = 0;
		while ((iter_node < col_inf->ammount_node) && tmp)
		{
			if (iter_node < col_inf->ammount_node && tmp)
				tmp = tmp->next;
			iter_node++;
		}
		iter_col++;
	}
	return (iter_col);
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
	col_inf->ammount_col = correct_col_val(begin, col_inf);
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

int	process_col(t_ls *ls, t_list **begin)
{
	struct winsize	ws;
	int				return_col;
	t_colformat		col_inf;

	if (!((ls->flags_info >> COLFORM) & 1))
		return (0);
	if (!begin || !(*begin))
		return (0);
	return_col = ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	if (return_col == -1)
		return (-1);
	ft_bzero(&(ls->pad), sizeof(ls->pad));
	pad_name_and_add_color(ls, begin);
	if (ws.ws_col < (2 * ls->pad.pad_name))
		return (0);
	col_inf.ammount_col = (ws.ws_col / ls->pad.pad_name);
	col_inf.lst_size = (size_t)ft_lstsize(*begin);
	if (div_lst_and_print(ls, begin, &col_inf) == -1)
		return (-1);
	return (0);
}
