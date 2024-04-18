/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:34:27 by corellan          #+#    #+#             */
/*   Updated: 2024/04/19 00:42:13 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	fill_file_dir_list(t_list **files, t_ls *ls, struct dirent *data)
{
	t_list	*tmp;

	tmp = process_argument(ls, data->d_name, DIRECTORY);
	if (!tmp)
	{
		free_lst(NULL, files, NULL);
		return (-1);
	}
	ft_lstadd_back(&(*files), tmp);
	return (0);
}

static int	process_folder(t_fileinfo *info, t_ls *ls)
{
	t_list			*files;
	DIR				*tmpdir;
	struct dirent	*data;

	files = NULL;
	tmpdir = opendir(info->name);
	if (!tmpdir)
		return (-1);
	while (1)
	{
		data = readdir(tmpdir);
		if (!data)
			break ;
		if (fill_file_dir_list(&files, ls, data) == -1)
		{
			closedir(tmpdir);
			return (-1);
		}
	}
	sort_input(ls, &files, 0);
	closedir(tmpdir);
	if (print_files_or_error(&files, ls, 0) == -1)
		ls->exit_status = -1;
	free_lst(NULL, &files, NULL);
	return (ls->exit_status);
}

int	print_folder(t_list **begin, t_ls *ls)
{
	t_list		*tmp;
	t_fileinfo	*info;

	tmp = *begin;
	if (!tmp)
		return (0);
	while (tmp)
	{
		info = tmp->content;
		if (process_folder(info, ls) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
