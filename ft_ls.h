/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:17:15 by corellan          #+#    #+#             */
/*   Updated: 2024/04/22 18:05:58 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <sys/stat.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <string.h>
# include <time.h>

typedef enum e_erls
{
	FLAGSERR,
	ALLOCERR
}	t_erls;

typedef enum e_lstls
{
	ARGUMENT,
	DIRECTORY
}	t_lstls;

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
	char			*name;
	char			*rel_path;
	char			*time;
	char			*file_size;
	struct stat		stat;
	struct stat		lstat;
	struct passwd	*pw;
	struct group	*gr;
}	t_fileinfo;

typedef struct s_dircol
{
	t_list	*files;
	t_list	*dir;
}	t_dircol;

typedef struct s_lspad
{
	size_t	pad_hl;
	size_t	pad_pw;
	size_t	pad_gr;
	size_t	pad_size;
}	t_lspad;

typedef struct s_ls
{
	int				ac;
	int				stat_status;
	int				exit_status;
	char			**av;
	char			char_flag;
	char			*tmpdir;
	char			*tmpinter;
	char			perm[11];
	size_t			starting_point;
	size_t			len_link;
	size_t			len_size;
	int				total_blocks;
	unsigned int	flags_info;
	t_list			*dir;
	t_list			*file;
	t_list			*error;
	t_lspad			pad;
	t_erls			error_c;
}	t_ls;

void	count_options(t_ls *ls);
int		valid_flag(t_ls *ls);
int		check_files_args(t_ls *ls);
t_list	*process_argument(t_ls *ls, const char *input, t_lstls type);
void	sort_input(t_ls *ls, t_list **begin, int flag);
void	swap_pointers(void **a, void **b);
int		free_lst(t_list **dir, t_list **file, t_list **err);
void	delete_fileinfo(void *fileinfo);
int		print_files_or_error(t_list **begin, t_ls *ls, int error, t_lstls type);
int		calculate_paddings(t_list **begin, t_ls *ls, t_lstls type);
void	store_attributes(t_fileinfo *info, t_ls *ls);
int		print_folder(t_list **begin, t_ls *ls, int flag);

#endif