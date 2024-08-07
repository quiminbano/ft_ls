/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:16:53 by corellan          #+#    #+#             */
/*   Updated: 2024/05/29 11:12:01 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	count_options(t_ls *ls, int ac, char **av)
{
	size_t	i;

	i = 1;
	ls->ac = ac;
	ls->av = av;
	ls->starting_point = i;
	if (ls->ac == 1)
		return ;
	while (ls->av[i])
	{
		if (!ft_strcmp(ls->av[i], "-") || ls->av[i][0] != '-')
			break ;
		i++;
	}
	ls->starting_point = i;
}

static void	fill_flags(char flag, t_ls *ls)
{
	if (flag == 'R')
		ls->flags_info |= (1 << RECFLAG);
	else if (flag == 'a')
		ls->flags_info |= (1 << AFLAG);
	else if (flag == 'l')
		ls->flags_info |= (1 << LFLAG);
	else if (flag == 'r')
		ls->flags_info |= (1 << RFLAG);
	else
		ls->flags_info |= (1 << TFLAG);
}

static int	iterate_flags(const char *str, t_ls *ls)
{
	const char	*flags = "Ralrt";
	size_t		i;
	size_t		j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (flags[j])
		{
			if (flags[j] == str[i])
				break ;
			j++;
		}
		ls->char_flag = str[i];
		if (flags[j] == '\0')
			return (-1);
		i++;
		fill_flags(ls->char_flag, ls);
	}
	return (0);
}

int	valid_flag(t_ls *ls)
{
	size_t	i;

	i = 1;
	while (i < ls->starting_point)
	{
		if (iterate_flags(ls->av[i], ls) == -1)
			return (-1);
		i++;
	}
	return (0);
}
