/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_fill_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:00:40 by corellan          #+#    #+#             */
/*   Updated: 2024/04/13 20:18:26 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*process_argument(t_ls *ls, const char *input)
{
	t_list		*tmp;
	t_fileinfo	*info;

	ls->tmpdir = ft_strdup(input);
	if (!ls->tmpdir)
		return (NULL);
	info = (t_fileinfo *)ft_calloc(1, sizeof(t_fileinfo));
	if (!info)
	{
		free(ls->tmpdir);
		return (NULL);
	}
	ls->stat_status = stat(ls->tmpdir, &info->stat);
	info->name = ls->tmpdir;
	ls->tmpdir = NULL;
	tmp = ft_lstnew(info);
	if (!tmp)
	{
		free(info->name);
		ft_bzero(&(info->stat), sizeof(info->stat));
		free(info);
		return (NULL);
	}
	return (tmp);
}

static int	free_lst_error(t_list *dir, t_list *file, t_list *err)
{
	free_lst(dir, file, err);
	return (-1);
}

static int	process_one_argument(t_ls *ls, const char *str)
{
	t_list	*tmp;

	tmp = NULL;
	tmp = process_argument(ls, str);
	if (!tmp)
		return (-1);
	ft_lstadd_back(&(ls->dir), tmp);
	return (0);
}

int	check_files_args(t_ls *ls)
{
	size_t	i;
	t_list	*tmp;

	i = ls->starting_point;
	if (ls->ac == 1)
		return (process_one_argument(ls, "."));
	while ((int)i < ls->ac)
	{
		tmp = NULL;
		tmp = process_argument(ls, ls->av[i]);
		if (!tmp)
			return (free_lst_error(ls->dir, ls->file, ls->error));
		if (ls->stat_status == -1)
			ft_lstadd_back(&(ls->error), tmp);
		else if (S_ISDIR(((t_fileinfo *)tmp->content)->stat.st_mode))
			ft_lstadd_back(&(ls->dir), tmp);
		else
			ft_lstadd_back(&(ls->file), tmp);
		i++;
	}
	sort_input(ls, &(ls->error), 1);
	return (0);
}
