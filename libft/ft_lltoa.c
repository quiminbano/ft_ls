/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:16:57 by corellan          #+#    #+#             */
/*   Updated: 2024/04/16 22:22:57 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_lllen(long long n)
{
	size_t	i;

	i = 1;
	if (n == 0)
		return (i);
	else if (n == LLONG_MIN)
		return (20);
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

static char	*ft_lltoa_aux(char *digit, long long n, size_t sign, size_t l)
{
	size_t	len;
	int		num;

	len = ft_lllen(n);
	len += sign;
	num = 0;
	while (l > sign)
	{
		num = n % 10;
		n /= 10;
		digit[l - 1] = num + '0';
		l--;
	}
	digit[len] = '\0';
	return (digit);
}

char	*ft_lltoa(long long n)
{
	char	*digit;
	size_t	l;

	l = ft_lllen(n);
	digit = (char *)malloc(sizeof(char) * (l + 1));
	if (digit == NULL)
		return (NULL);
	if (n == LLONG_MIN)
	{
		ft_strlcpy(digit, "-9223372036854775808", 21);
		return (digit);
	}
	if (n < 0)
	{
		digit[0] = '-';
		n *= -1;
		return (ft_lltoa_aux(digit, n, 1, l));
	}
	else
		return (ft_lltoa_aux(digit, n, 0, l));
}
