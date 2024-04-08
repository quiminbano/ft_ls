/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:37:01 by corellan          #+#    #+#             */
/*   Updated: 2024/04/08 16:37:16 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

static size_t	get_size(const size_t begin, const char *s)
{
	size_t	numbers_size;

	numbers_size = 0;
	if (s[begin] == '*')
		return (1);
	while (ft_isdigit(s[begin + numbers_size]))
		numbers_size++;
	return (numbers_size);
}

static int	asteric_to_number(t_flags *fl)
{
	int	number;

	number = va_arg(*(fl->ptr), int);
	if (number < 0 && fl->begin == '.')
	{
		fl->orig_num = number;
		number = 0;
	}
	else if (number < 0)
	{
		fl->has_minus = 1;
		fl->has_pure_number = 0;
		number *= -1;
	}
	return ((int)number);
}

static int	get_numbers(t_flags *fl, size_t *begin, const char *s)
{
	int		converted_number;
	size_t	numbers_size;

	converted_number = 0;
	numbers_size = get_size(*begin, s);
	if (!numbers_size)
		return (1);
	if (s[*begin] != '*')
		converted_number = ft_atoi(s + (*begin));
	else
		converted_number = asteric_to_number(fl);
	if (converted_number < 0 || numbers_size > 10)
		return (-1);
	if (!fl->has_minus && ((fl->begin != '.') || (fl->begin == '.' && \
		fl->conv != 'c' && fl->conv != 's')))
		fl->has_pure_number = 1;
	if (fl->begin == '.')
		fl->size_dot = converted_number;
	else
		fl->size_print = converted_number;
	(*begin) += numbers_size;
	return (0);
}

int	fill_ident(t_flags *fl, size_t *begin, size_t end, const char *s)
{
	fl->conv = s[end];
	if (s[*begin] == '-')
	{
		fl->has_minus = 1;
		fl->has_pure_number = 0;
		(*begin)++;
	}
	else if (s[*begin] == '.')
	{
		if (fl->conv != 'c' && fl->conv != '%')
			fl->has_dot = 1;
		if (fl->has_zero && fl->conv != 's' && fl->conv != 'c' && \
			fl->conv != '%')
		{
			fl->has_zero = 0;
			fl->dot_number = 1;
		}
		(*begin)++;
	}
	if (s[*begin] == '0' && (!fl->has_minus && fl->begin != '.' && \
		!fl->dot_number))
		fl->has_zero = 1;
	if (s[*begin] == '0')
		(*begin)++;
	return (get_numbers(fl, begin, s));
}

void	fill_format(t_flags *fl, size_t begin, size_t end, const char *s)
{
	size_t	iter;

	iter = begin;
	while (iter < end)
	{
		if ((s[end] == 'd' || s[end] == 'i') && \
			s[iter] == ' ' && !fl->has_plus)
			fl->has_space = 1;
		else if ((s[end] == 'd' || s[end] == 'i') && s[iter] == '+')
		{
			fl->has_plus = 1;
			fl->has_space = 0;
		}
		else if (s[end] == 'x' && s[iter] == '#')
		{
			fl->has_sharp = 1;
			fl->type_sharp = LOWER;
		}
		else if (s[end] == 'X' && s[iter] == '#')
		{
			fl->has_sharp = 1;
			fl->type_sharp = UPPER;
		}
		iter++;
	}
}
