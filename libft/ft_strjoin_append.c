/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_append.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:42:10 by corellan          #+#    #+#             */
/*   Updated: 2024/04/16 15:48:16 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*handle_return(char **s1, char *returned)
{
	if ((*s1))
		free((*s1));
	(*s1) = NULL;
	return (returned);
}

char	*ft_strjoin_append(char *s1, const char *s2, size_t n)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*res;

	i = 0;
	len1 = 0;
	len2 = n;
	if (len2 > ft_strlen(s2))
		len2 = ft_strlen(s2);
	if (s1)
		len1 = ft_strlen(s1);
	res = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!res)
		return (handle_return(&s1, NULL));
	while (i < (len1 + len2))
	{
		if (i < len1)
			res[i] = s1[i];
		else
			res[i] = s2[i - len1];
		i++;
	}
	res[i] = '\0';
	return (handle_return(&s1, res));
}