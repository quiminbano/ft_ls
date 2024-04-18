/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:28:40 by corellan          #+#    #+#             */
/*   Updated: 2024/04/19 00:46:25 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	get_number(char c)
{
	const char	*lower = "0123456789abcdefghijklmnopqrstuvwxyz";
	const char	*upper = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	long		i;

	i = 0;
	while (lower[i] && upper[i])
	{
		if (c == lower[i] || c == upper[i])
			break ;
		i++;
	}
	return (i);
}

static long	handle_return(const char *str, char **endptr, size_t i, long number)
{
	if (endptr != NULL)
		(*endptr) = (char *)str + i;
	return (number);
}

void	special_cases(const char *str, int *base, size_t *i)
{
	if (((*base) == 0 || (*base) == 16) && ft_strnstr(str + (*i), "0x", 2))
	{
		(*base) = 16;
		(*i) += 2;
	}
	else if ((*base) == 0 && str[(*i)] == '0')
	{
		(*base) = 8;
		(*i)++;
	}
	else if ((*base) == 0)
		(*base) = 10;
}

static void	calculate_num(const char *str, int base, size_t *i, long *number)
{
	long	temp_num;

	while (ft_isalnum(str[(*i)]))
	{
		temp_num = get_number(str[(*i)]);
		if (temp_num >= base)
			break ;
		(*number) = (((*number) * base) + temp_num);
		if ((*number) < 0)
			break ;
		(*i)++;
	}
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	long	sign;
	long	number;
	size_t	i;

	sign = 1;
	i = 0;
	number = 0;
	if (base > 36 || base < 0)
		return (handle_return(str, endptr, i, number));
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-' && ++i)
		sign *= -1;
	special_cases(str, &base, &i);
	calculate_num(str, base, &i, &number);
	if (number < 0 && sign == 1)
		return (handle_return(str, endptr, i, LONG_MAX));
	if (number < 0 && sign == -1)
		return (handle_return(str, endptr, i, LONG_MIN));
	return (handle_return(str, endptr, i, (number * sign)));
}
