/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlength_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 23:40:35 by corellan          #+#    #+#             */
/*   Updated: 2024/04/04 23:41:47 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_numlength_base(size_t number, size_t base)
{
	size_t	result;

	result = 1;
	if (number == 0)
		return (result);
	while ((number / base) > 0)
	{
		number /= base;
		result++;
	}
	return (result);
}
