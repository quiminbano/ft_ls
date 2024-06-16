/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sultoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:16:57 by corellan          #+#    #+#             */
/*   Updated: 2024/06/16 01:55:18 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	create_string(char *str, size_t n, size_t base, const char *templ)
{
	size_t	i;
	size_t	length;

	if (base > 16)
		return ;
	length = ft_numlength_base(n, base);
	i = length;
	str[i] = '\0';
	while (i-- > 0)
	{
		str[i] = templ[(n % base)];
		n /= base;
	}
}

void	ft_sultoa_base(char *str, size_t n, size_t base, size_t format)
{
	const char	*lower = "0123456789abcdef";
	const char	*upper = "0123456789ABCDEF";

	if (format % 2 == 0)
		create_string(str, n, base, lower);
	else
		create_string(str, n, base, upper);
}
