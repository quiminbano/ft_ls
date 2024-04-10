/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:30:19 by corellan          #+#    #+#             */
/*   Updated: 2024/04/10 14:54:11 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

int	append_number(unsigned long number, t_base base, t_printf *data)
{
	int				write_status;
	unsigned long	base_num;
	size_t			length;
	char			*str;

	if (base == NORMAL)
		base_num = 10;
	else
		base_num = 16;
	str = ft_ultoa_base(number, base_num, (size_t)base);
	if (!str)
		return (-1);
	length = ft_strlen(str);
	write_status = append_str(data, str, length);
	free(str);
	str = NULL;
	if (write_status == -1)
		return (-1);
	data->count += length;
	return (0);
}

int	append_unsigned(unsigned long number, t_base base, t_printf *data)
{
	size_t	backup;

	backup = data->size_number;
	if (data->flags.conv == 'p')
	{
		data->flags.has_sharp = 1;
		data->flags.type_sharp = LOWER;
	}
	if (data->flags.has_sharp && data->flags.conv != 'p' && number == 0)
		data->flags.has_sharp = 0;
	if (data->flags.size_dot >= data->size_number)
		data->size_number = data->flags.size_dot;
	if (special_case(data) && !number)
		data->size_number = 0;
	if (append_identation(data, data->size_number, BEFORE) == -1)
		return (-1);
	if ((data->size_number >= backup) && \
		append_zeros((data->size_number - backup), data) == -1)
		return (-1);
	if (data->size_number && append_number(number, base, data) == -1)
		return (-1);
	if (append_identation(data, data->size_number, AFTER) == -1)
		return (-1);
	return (0);
}

int	nbr_return(long long number, t_base base, t_printf *data)
{
	size_t	backup;

	backup = data->size_number;
	if (number < 0)
	{
		number *= -1;
		data->flags.has_plus = 0;
		data->flags.has_space = 0;
		data->flags.neg = 1;
	}
	if (data->flags.size_dot >= data->size_number)
		data->size_number = data->flags.size_dot;
	if (special_case(data) && !number)
		data->size_number = 0;
	if (append_identation(data, data->size_number, BEFORE) == -1)
		return (-1);
	if ((data->size_number >= backup) && \
		append_zeros((data->size_number - backup), data) == -1)
		return (-1);
	if (data->size_number && append_number(number, base, data) == -1)
		return (-1);
	if (append_identation(data, data->size_number, AFTER) == -1)
		return (-1);
	return (0);
}

int	char_return(char c, t_printf *data, t_char flag)
{
	if (flag == CHAR && append_identation(data, 1, BEFORE) == -1)
		return (-1);
	if (append_char(data, c) == -1)
		return (-1);
	data->count += 1;
	if (flag == CHAR && append_identation(data, 1, AFTER) == -1)
		return (-1);
	return (0);
}

int	str_return(char *str, t_printf *data)
{
	int		write_status;
	size_t	size_string;

	if (str == NULL)
		size_string = 6;
	else
		size_string = ft_strlen(str);
	if (data->flags.has_dot && data->flags.size_dot < size_string)
		size_string = data->flags.size_dot;
	if (append_identation(data, size_string, BEFORE) == -1)
		return (-1);
	if (str == NULL)
		write_status = append_str(data, "(null)", size_string);
	else
		write_status = append_str(data, str, size_string);
	data->count += (int)size_string;
	if (write_status == -1)
		return (-1);
	if (append_identation(data, size_string, AFTER) == -1)
		return (-1);
	return (0);
}
