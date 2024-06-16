/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:42:13 by corellan          #+#    #+#             */
/*   Updated: 2024/06/16 23:15:17 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	append_str(t_printf *data, char const *str, size_t n)
{
	size_t	idx;

	idx = 0;
	while (idx < n)
	{
		if (append_char(data, str[idx], idx) == -1)
			return (-1);
		idx++;
	}
	return (0);
}

int	append_char(t_printf *data, char c, size_t idx)
{
	if (data->count < 0)
		return (-1);
	if (data->buffer_idx == STRBUFFER && data->type == PRINTF)
	{
		if (write(data->fd, data->buffer, data->buffer_idx) == -1)
			return (-1);
		ft_bzero(data->buffer, sizeof(data->buffer));
		data->buffer_idx = 0;
	}
	else if (data->buffer_idx == STRBUFFER && data->type == SPRINTF)
	{
		data->pos_str = ((size_t)data->count + idx) - data->buffer_idx;
		ft_memcpy((data->str_sprintf + data->pos_str), data->buffer, STRBUFFER);
		ft_bzero(data->buffer, sizeof(data->buffer));
		data->buffer_idx = 0;
	}
	data->buffer[data->buffer_idx] = c;
	(data->buffer_idx)++;
	return (0);
}

int	return_interface(va_list *ar, t_printf *data)
{
	size_t	buf_idx;
	int		value;

	buf_idx = data->buffer_idx;
	if (data->return_status == -1 || data->count < 0)
		value = -1;
	else
		value = data->count;
	if (buf_idx && data->type == PRINTF && value != -1)
	{
		if (write(data->fd, data->buffer, buf_idx) == -1)
			value = -1;
		ft_bzero(data->buffer, sizeof(data->buffer));
	}
	if (buf_idx && data->type == SPRINTF && value != -1)
	{
		data->pos_str = (size_t)data->count - data->buffer_idx;
		ft_memcpy((data->str_sprintf + data->pos_str), data->buffer, buf_idx);
		ft_bzero(data->buffer, sizeof(data->buffer));
	}
	va_end(*ar);
	return (value);
}

size_t	length_number(const char c, va_list *ar, int base)
{
	va_list	copy;
	size_t	number;
	long	original;

	va_copy(copy, *ar);
	original = 0;
	number = 0;
	if (c == 'x' || c == 'X' || c == 'u')
		number = va_arg(copy, unsigned int);
	else if (c == 'd' || c == 'i')
	{
		original = va_arg(copy, int);
		if (original < 0)
			number = (size_t)(original * -1);
		else
			number = (size_t)original;
	}
	else
		number = va_arg(copy, unsigned long);
	va_end(copy);
	return (ft_numlength_base(number, (size_t)base));
}
