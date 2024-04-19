/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:28:40 by corellan          #+#    #+#             */
/*   Updated: 2024/04/19 12:41:00 by corellan         ###   ########.fr       */
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

static long	handle_return(const char *str, char **endptr, long number, long sig)
{
	if (number < 0 && sig > 0)
		number = LONG_MAX;
	if (number < 0 && sig < 0)
	{
		number = LONG_MIN;
		sig = 1;
	}
	if (endptr != NULL)
		(*endptr) = (char *)str;
	return (number * sig);
}

void	special_cases(const char *str, int *base, size_t *i)
{
	if (((*base) == 0 || (*base) == 16) && ft_strnstr(str + (*i), "0x", 2))
	{
		(*base) = 16;
		if (ft_isxdigit(str[(*i) + 2]))
			(*i) += 2;
		else
			(*i)++;
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
	int		flag;

	flag = 0;
	while (ft_isalnum(str[(*i)]))
	{
		temp_num = get_number(str[(*i)]);
		if (temp_num >= base)
			break ;
		(*number) = (((*number) * base) + temp_num);
		if ((*number) < 0)
		{
			flag = 1;
			break ;
		}
		(*i)++;
	}
	while (flag == 1 && ft_isalnum(str[(*i)]))
	{
		temp_num = get_number(str[(*i)]);
		if (temp_num >= base)
			break ;
		(*i)++;
	}
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	long	sign;
	long	number;
	size_t	i;
	size_t	number_start;

	sign = 1;
	i = 0;
	number = 0;
	if (base > 36 || base < 0)
		return (handle_return(str + i, endptr, number, sign));
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-' && ++i)
		sign *= -1;
	number_start = i;
	special_cases(str, &base, &i);
	calculate_num(str, base, &i, &number);
	if (number_start == i)
		return (handle_return(str, endptr, number, sign));
	return (handle_return(str + i, endptr, number, sign));
}
