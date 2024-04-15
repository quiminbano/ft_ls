/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_sort_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 20:18:53 by corellan          #+#    #+#             */
/*   Updated: 2024/04/15 12:46:36 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	make_comparisions(t_fileinfo *inf, t_fileinfo *nxt, unsigned int bk)
{
	unsigned int	reverse;
	unsigned int	time;

	reverse = ((bk >> RFLAG) & 1);
	time = ((bk >> TFLAG) & 1);
	if (!time && !reverse && ft_strcmp(inf->name, nxt->name) >= 1)
		return (1);
	else if (!time && reverse && ft_strcmp(inf->name, nxt->name) <= -1)
		return (1);
	else if (time && !reverse && inf->lstat.st_mtime < nxt->lstat.st_mtime)
		return (1);
	else if (time && reverse && inf->lstat.st_mtime > nxt->lstat.st_mtime)
		return (1);
	return (0);
}

void	sort_input(t_ls *ls, t_list **begin, int flag)
{
	t_list			*tmp;
	t_fileinfo		*inf;
	t_fileinfo		*nxt;
	unsigned int	bk;

	tmp = *begin;
	if (flag == 1)
		bk = 0;
	else
		bk = ls->flags_info;
	while (tmp->next != NULL)
	{
		inf = tmp->content;
		nxt = tmp->next->content;
		if (make_comparisions(inf, nxt, bk) == 1)
		{
			swap_pointers(&(tmp->content), &(tmp->next->content));
			tmp = *begin;
		}
		else
			tmp = tmp->next;
	}
}
