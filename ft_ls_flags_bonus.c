/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_flags_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:16:53 by corellan          #+#    #+#             */
/*   Updated: 2024/05/23 13:11:58 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_bonus.h"

void	count_options(t_ls *ls)
{
	size_t	i;

	i = 1;
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

static void	fill_flags_cont(char flag, t_ls *ls)
{
	unsigned char	inverse;

	inverse = ~(ls->flags_info);
	if (flag == 'l' || flag == 'g')
	{
		inverse |= (1 << ONEFLAG);
		ls->flags_info = ~(inverse);
		ls->flags_info |= (1 << LFLAG);
		if (flag == 'g')
			ls->flags_info |= (1 << GFLAG);
	}
	else if (flag == 'r')
		ls->flags_info |= (1 << RFLAG);
	else if (flag == 't')
		ls->flags_info |= (1 << TFLAG);
	else if (flag == 'u')
		ls->flags_info |= (1 << UFLAG);
	else if (flag == '@')
		ls->flags_info |= (1 << ATFLAG);
	else
	{
		inverse |= (1 << LFLAG);
		ls->flags_info = ~(inverse);
		ls->flags_info |= (1 << ONEFLAG);
	}
}

static void	fill_flags(char flag, t_ls *ls)
{
	if (flag == 'G')
		ls->flags_info |= (1 << GEEFLAG);
	else if (flag == 'R')
		ls->flags_info |= (1 << RECFLAG);
	else if (flag == 'a')
		ls->flags_info |= (1 << AFLAG);
	else if (flag == 'd')
		ls->flags_info |= (1 << DFLAG);
	else if (flag == 'e')
		ls->flags_info |= (1 << EFLAG);
	else if (flag == 'f')
	{
		ls->flags_info |= (1 << AFLAG);
		ls->flags_info |= (1 << FFLAG);
	}
	else
		fill_flags_cont(flag, ls);
}

static int	iterate_flags(const char *str, t_ls *ls)
{
	const char	*flags = "GRadefglrtu@1";
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
	if (!((ls->flags_info >> LFLAG)) && !((ls->flags_info >> ONEFLAG)))
		ls->flags_info |= (1 << COLFORM);
	return (0);
}

int	valid_flag(t_ls *ls)
{
	size_t		i;

	i = 1;
	while (i < ls->starting_point)
	{
		if (iterate_flags(ls->av[i], ls) == -1)
			return (-1);
		i++;
	}
	return (0);
}
