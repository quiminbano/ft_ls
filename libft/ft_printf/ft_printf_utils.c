/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:42:13 by corellan          #+#    #+#             */
/*   Updated: 2024/04/08 16:37:30 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

static char	*handle_return(char **s1, char *returned)
{
	if ((*s1))
		free((*s1));
	(*s1) = NULL;
	return (returned);
}

int	append_str(t_printf *data, char const *str, size_t n)
{
	size_t	idx;

	idx = 0;
	while (idx < n)
	{
		if (append_char(data, str[idx]) == -1)
			return (-1);
		idx++;
	}
	return (0);
}

int	append_char(t_printf *data, char c)
{
	if (data->count < 0)
		return (-1);
	if (data->buffer_idx == STRBUFFER)
	{
		data->mct = (size_t)data->count - data->buffer_idx;
		data->str = copy_to_heap(data->str, data->buffer, data->mct, STRBUFFER);
		if (!data->str)
			return (-1);
		ft_bzero(data->buffer, sizeof(data->buffer));
		data->buffer_idx = 0;
	}
	data->buffer[data->buffer_idx] = c;
	(data->buffer_idx)++;
	return (0);
}

char	*copy_to_heap(char *s1, const char *s2, int count, size_t n)
{
	size_t	len2;
	size_t	i;
	char	*res;

	i = 0;
	len2 = n;
	res = NULL;
	if (count < 0)
		return (handle_return(&s1, NULL));
	res = (char *)malloc(sizeof(char) * ((size_t)count + len2 + 1));
	if (!res)
		return (handle_return(&s1, NULL));
	while (i < ((size_t)count + len2))
	{
		if (i < (size_t)count)
			res[i] = s1[i];
		else
			res[i] = s2[i - (size_t)count];
		i++;
	}
	res[i] = '\0';
	return (handle_return(&s1, res));
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
