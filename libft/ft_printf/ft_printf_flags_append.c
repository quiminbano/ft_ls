/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags_append.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:42:23 by corellan          #+#    #+#             */
/*   Updated: 2024/04/08 16:36:57 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

int	special_case(t_printf *data)
{
	if (data->flags.has_dot && !data->flags.size_dot && !data->flags.orig_num)
		return (1);
	return (0);
}

int	append_zeros(size_t max, t_printf *data)
{
	int		write_status;
	size_t	iter;

	write_status = 0;
	iter = 0;
	while (iter < max)
	{
		write_status = char_return('0', data, NUMBER);
		if (write_status == -1)
			return (-1);
		iter++;
	}
	return (0);
}

static int	append_special(t_printf *data, t_when when)
{
	char	buff[3];
	size_t	length;

	ft_bzero(buff, 3);
	if (when == BEFORE && data->flags.has_plus)
		ft_strlcpy(buff, "+", 2);
	if (when == BEFORE && data->flags.neg)
		ft_strlcpy(buff, "-", 2);
	else if (when == BEFORE && data->flags.has_space)
		ft_strlcpy(buff, " ", 3);
	else if (when == BEFORE && data->flags.has_sharp && \
		data->flags.type_sharp == UPPER)
		ft_strlcpy(buff, "0X", 3);
	else if (when == BEFORE && data->flags.has_sharp && \
		data->flags.type_sharp == LOWER)
		ft_strlcpy(buff, "0x", 3);
	length = ft_strlen(buff);
	if (append_str(data, buff, length) == -1)
		return (-1);
	data->count += length;
	return (0);
}

static int	sp_zero(t_printf *data, size_t total_size, t_when when, char c)
{
	size_t	iter;

	iter = 0;
	while (when == BEFORE && data->flags.has_pure_number && iter < total_size)
	{
		if (append_char(data, c) == -1)
			return (-1);
		iter++;
		(data->count)++;
	}
	if (when == BEFORE && c == ' ' && append_special(data, when) == -1)
		return (-1);
	iter = 0;
	while (when == AFTER && data->flags.has_minus && iter < total_size)
	{
		if (append_char(data, c) == -1)
			return (-1);
		iter++;
		(data->count)++;
	}
	return (0);
}

int	append_identation(t_printf *data, size_t size_parameter, t_when when)
{
	size_t	total_size;
	char	c;

	total_size = data->flags.size_print;
	if (data->flags.has_zero && data->flags.has_pure_number)
		c = '0';
	else
		c = ' ';
	if (data->flags.has_plus || data->flags.has_space || data->flags.neg)
		size_parameter += 1;
	if (data->flags.has_sharp)
		size_parameter += 2;
	if (c == '0' && append_special(data, when) == -1)
		return (-1);
	if (total_size >= size_parameter)
		total_size -= size_parameter;
	else
		total_size = 0;
	if (sp_zero(data, total_size, when, c) == -1)
		return (-1);
	return (0);
}
