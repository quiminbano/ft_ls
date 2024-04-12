/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:17:15 by corellan          #+#    #+#             */
/*   Updated: 2024/04/12 16:55:57 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>

typedef enum e_lsflags
{
	RECFLAG,
	AFLAG,
	LFLAG,
	RFLAG,
	TFLAG
}	t_lsflags;

typedef struct s_fileinfo
{
	char		*name;
	struct stat	stat;
}	t_fileinfo;

typedef struct s_ls
{
	int				ac;
	char			**av;
	char			char_flag;
	char			*tmpdir;
	size_t			starting_point;
	unsigned int	flags_info;
	t_list			*dir;
	t_list			*file;
	t_list			*error;
}	t_ls;

void	count_options(t_ls *ls);
int		valid_flag(t_ls *ls);

#endif