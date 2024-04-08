/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:18:32 by corellan          #+#    #+#             */
/*   Updated: 2024/04/08 17:54:09 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int ac, char **av)
{
	int			result;
	struct stat	hello;

	if (ac != 1)
		ft_printf("Hi");
	(void)av;
	ft_printf("This is a test\n");
	result = stat(".", &hello);
	ft_printf("This is the result of stat: %20d\n", result);
	return (0);
}
