/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort_lst_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 20:18:53 by corellan          #+#    #+#             */
/*   Updated: 2024/06/27 19:00:50 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

static t_list	*merge_lst(t_list *a, t_list *b, t_ls *ls, unsigned int bk)
{
	t_list		*result;
	t_fileinfo	*info_a;
	t_fileinfo	*info_b;

	result = NULL;
	if (!a)
		return (b);
	else if (!b)
		return (a);
	info_a = (t_fileinfo *)a->content;
	info_b = (t_fileinfo *)b->content;
	if ((!((bk >> RFLAG) & 1) && check_norev(info_a, info_b, bk)) || \
		(((bk >> RFLAG) & 1) && check_rev(info_a, info_b, bk)))
	{
		result = b;
		result->next = merge_lst(a, b->next, ls, bk);
	}
	else
	{
		result = a;
		result->next = merge_lst(a->next, b, ls, bk);
	}
	return (result);
}

static void	split_lst(t_list *head, t_list **fr, t_list **bc)
{
	t_list	*fast;
	t_list	*slow;

	slow = head;
	fast = head->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	(*fr) = head;
	(*bc) = slow->next;
	slow->next = NULL;
}

void	sort_input(t_ls *ls, t_list **begin, int flag)
{
	t_list			*tmp;
	t_list			*a;
	t_list			*b;
	unsigned int	bk;

	tmp = *begin;
	if (flag == 1)
		bk = 0;
	else
		bk = ls->flags_info;
	if (!tmp || !(tmp->next) || ((ls->flags_info >> FFLAG) & 1))
		return ;
	a = NULL;
	b = NULL;
	split_lst(tmp, &a, &b);
	sort_input(ls, &a, flag);
	sort_input(ls, &b, flag);
	*begin = merge_lst(a, b, ls, bk);
}
