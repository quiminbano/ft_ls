/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:36:09 by corellan          #+#    #+#             */
/*   Updated: 2024/06/16 23:16:06 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_undef(const char *s, size_t *af, t_printf *data, va_list *ar)
{
	size_t	i;

	i = data->index;
	while (s[i] == '#' || s[i] == '+' || s[i] == '-' || s[i] == ' ' || \
		s[i] == '.' || s[i] == '*' || ft_isdigit(s[i]))
		i++;
	(*af) = i;
	if (s[i] == '\0')
	{
		data->index = ((*af) - 1);
		return (1);
	}
	if (s[i] != 'd' && s[i] != 'i' && \
		s[i] != 'c' && s[i] != 'p' && \
		s[i] != 'x' && s[i] != 'X' && \
		s[i] != 's' && s[i] != 'u' && \
		s[i] != '%')
	{
		data->index = (*af);
		return (1);
	}
	data->flags.ptr = ar;
	return (0);
}
