/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_return.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:23:05 by corellan          #+#    #+#             */
/*   Updated: 2024/04/10 13:31:30 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

int	append_or_return(va_list *ar, t_printf *data, int value, int flag)
{
	size_t	buf_idx;

	buf_idx = data->buffer_idx;
	if (flag == 0)
	{
		if (data->str)
			free(data->str);
		data->str = NULL;
		va_end(*ar);
		return (value);
	}
	if (buf_idx)
	{
		data->mct = (size_t)data->count - data->buffer_idx;
		data->str = copy_to_heap(data->str, data->buffer, data->mct, buf_idx);
		if (!data->str)
			return (-1);
		ft_bzero(data->buffer, sizeof(data->buffer));
	}
	return (0);
}
