/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:16:57 by corellan          #+#    #+#             */
/*   Updated: 2024/06/16 01:54:38 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(int n)
{
	size_t	i;

	i = 1;
	if (n == 0)
		return (i);
	else if (n == -2147483648LL)
		return (11);
	else
	{
		if (n < 0)
		{
			i = 2;
			n *= -1;
		}
		while ((n / 10) > 0)
		{
			n /= 10;
			i++;
		}
		return (i);
	}
}

void	ft_sitoa(char *str, int n)
{
	int	l;
	int	sign;

	l = ft_intlen(n);
	sign = 0;
	if (n == -2147483648LL)
	{
		ft_strlcpy(str, "-2147483648", 12);
		return ;
	}
	str[l] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		sign = 1;
	}
	while (l > sign)
	{
		str[l - 1] = (n % 10) + '0';
		n /= 10;
		l--;
	}
}
