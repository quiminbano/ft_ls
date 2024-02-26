/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:18:32 by corellan          #+#    #+#             */
/*   Updated: 2024/02/26 15:47:03 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int ac, char **av)
{
	int			result;
	struct stat	hello;

	if (ac != 1)
		ft_putendl_fd("Hi", 1);
	(void)av;
	ft_putendl_fd("This is a test", 1);
	result = stat(".", &hello);
	ft_putstr_fd("This is result: ", 1);
	ft_putnbr_fd(result, 1);
	ft_putendl_fd("", 1);
	return (0);
}
