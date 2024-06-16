/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:45:22 by corellan          #+#    #+#             */
/*   Updated: 2024/06/16 23:14:46 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_variadic(va_list *ar, t_printf *data, const char *s)
{
	data->flags.conv = s[data->index];
	if (data->flags.conv == 'd' || data->flags.conv == 'i')
		return (nbr_return(va_arg(*ar, int), NORMAL, data));
	else if (data->flags.conv == 'c')
		return (char_return(va_arg(*ar, int), data, CHAR));
	else if (data->flags.conv == 'u')
		return (append_unsigned(va_arg(*ar, unsigned int), NORMAL, data));
	else if (data->flags.conv == 'x')
		return (append_unsigned(va_arg(*ar, unsigned int), LOWER, data));
	else if (data->flags.conv == 'X')
		return (append_unsigned(va_arg(*ar, unsigned int), UPPER, data));
	else if (data->flags.conv == 'p')
		return (append_unsigned(va_arg(*ar, unsigned long), LOWER, data));
	else if (data->flags.conv == 's')
		return (str_return(va_arg(*ar, char *), data));
	else if (data->flags.conv == '%')
		return (char_return('%', data, CHAR));
	return (0);
}

static int	check_flags(const char *s, va_list *ar, t_printf *data)
{
	size_t	after_fl;
	int		ident_status;

	after_fl = 0;
	ident_status = 0;
	if (check_undef(s, &after_fl, data, ar))
		return (0);
	fill_format(&(data->flags), data->index, after_fl, s);
	while (data->index < after_fl)
	{
		data->flags.begin = s[data->index];
		ident_status = fill_ident(&(data->flags), &(data->index), after_fl, s);
		if (ident_status == -1)
			return (-1);
		else if (ident_status && data->flags.begin != '.' && \
			data->flags.begin != '-' && data->flags.begin != '0')
			(data->index)++;
	}
	if (s[data->index] == 'x' || s[data->index] == 'X' || \
		s[data->index] == 'p')
		data->size_number = length_number(s[data->index], ar, 16);
	else if (s[data->index] == 'd' || s[data->index] == 'i' || \
		s[data->index] == 'u')
		data->size_number = length_number(s[data->index], ar, 10);
	return (handle_variadic(ar, data, s));
}

int	ft_sprintf(char *str, const char *s, ...)
{
	va_list		ar;
	t_printf	data;

	ft_bzero(&data, sizeof(data));
	data.str_sprintf = str;
	data.type = SPRINTF;
	va_start(ar, s);
	while (s[data.index])
	{
		ft_bzero(&(data.flags), sizeof(data.flags));
		if (s[data.index] == '%' && s[data.index + 1] != '\0')
		{
			(data.index)++;
			data.return_status = check_flags(s, &ar, &data);
		}
		else if (s[data.index] != '%' && s[data.index] != '\0')
			data.return_status = char_return(s[data.index], &data, NOCONV);
		if (data.return_status == -1 || data.count < 0)
			return (return_interface(&ar, &data));
		(data.index)++;
	}
	return (return_interface(&ar, &data));
}

int	ft_dprintf(int fd, const char *s, ...)
{
	va_list		ar;
	t_printf	data;

	ft_bzero(&data, sizeof(data));
	data.fd = fd;
	data.type = PRINTF;
	va_start(ar, s);
	while (s[data.index])
	{
		ft_bzero(&(data.flags), sizeof(data.flags));
		if (s[data.index] == '%' && s[data.index + 1] != '\0')
		{
			(data.index)++;
			data.return_status = check_flags(s, &ar, &data);
		}
		else if (s[data.index] != '%' && s[data.index] != '\0')
			data.return_status = char_return(s[data.index], &data, NOCONV);
		if (data.return_status == -1 || data.count < 0)
			return (return_interface(&ar, &data));
		(data.index)++;
	}
	return (return_interface(&ar, &data));
}

int	ft_printf(const char *s, ...)
{
	va_list		ar;
	t_printf	data;

	ft_bzero(&data, sizeof(data));
	data.fd = 1;
	data.type = PRINTF;
	va_start(ar, s);
	while (s[data.index])
	{
		ft_bzero(&(data.flags), sizeof(data.flags));
		if (s[data.index] == '%' && s[data.index + 1] != '\0')
		{
			(data.index)++;
			data.return_status = check_flags(s, &ar, &data);
		}
		else if (s[data.index] != '%' && s[data.index] != '\0')
			data.return_status = char_return(s[data.index], &data, NOCONV);
		if (data.return_status == -1 || data.count < 0)
			return (return_interface(&ar, &data));
		(data.index)++;
	}
	return (return_interface(&ar, &data));
}
