/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:17:15 by corellan          #+#    #+#             */
/*   Updated: 2024/06/19 12:47:41 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_BONUS_H
# define FT_LS_BONUS_H

# include "libft/libft.h"
# include <sys/stat.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <string.h>
# include <time.h>
# include <errno.h>
# include <sys/ioctl.h>

# ifdef __linux__
#  include <sys/sysmacros.h>
#  include <linux/limits.h>
#  ifndef S_ISVTX
#   define S_ISVTX __S_ISVTX
#  endif
# else
#  include <sys/acl.h>
# endif

# define SIX_MONTHS 15811200

# ifdef __APPLE__
#  define BLOCKDIV 1
# else
#  define BLOCKDIV 2
# endif

# define SOCKCOL "\033[0;32m"
# define EXECCOL "\033[0;31m"
# define DIRCOL "\033[0;34m"
# define SYMCOL "\033[0;35m"
# define PIPECOL "\033[0;33m"
# define BLKCOL "\033[46;34m"
# define CHRCOL "\033[43;34m"
# define XUIDCOL "\033[41;30m"
# define XGIDCOL "\033[46;30m"
# define STKCOL "\033[42;30m"
# define WSTKCOL "\033[43;30m"
# define RESET "\033[0m"

# ifndef TABSPACE
#  define TABSPACE 8
# endif

# if TABSPACE <= 0
#  undef TABSPACE
#  define TABSPACE 8
# endif

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
	GEEFLAG,
	RECFLAG,
	AFLAG,
	DFLAG,
	EFLAG,
	FFLAG,
	GFLAG,
	LFLAG,
	RFLAG,
	TFLAG,
	UFLAG,
	ATFLAG,
	ONEFLAG,
	COLFORM
}	t_lsflags;

typedef struct s_colformat
{
	size_t	ammount_col;
	size_t	ammount_node;
	size_t	lst_size;
}	t_colformat;

# ifdef __APPLE__

typedef struct s_fileinfo
{
	acl_t			acl;
	char			*name;
	char			*rel_path;
	char			*time;
	char			*file_size;
	char			*color;
	char			*end;
	char			lk[PATH_MAX];
	int				er_st;
	int				er_dr;
	int				is_dir;
	struct stat		stat;
	struct stat		lstat;
	struct passwd	*pw;
	struct group	*gr;
	size_t			ext_size;
	size_t			tab_pad;
	ssize_t			acl_size;
	int				acl_usage;
}	t_fileinfo;
# else

typedef struct s_fileinfo
{
	char			*name;
	char			*rel_path;
	char			*time;
	char			*file_size;
	char			*color;
	char			*end;
	char			lk[PATH_MAX];
	int				er_st;
	int				er_dr;
	int				is_dir;
	struct stat		stat;
	struct stat		lstat;
	struct passwd	*pw;
	struct group	*gr;
	size_t			ext_size;
	size_t			tab_pad;
	ssize_t			acl_size;
	int				acl_usage;
}	t_fileinfo;
# endif

typedef struct s_dircol
{
	t_list	*files;
	t_list	*dir;
	t_list	*err;
}	t_dircol;

typedef struct s_lspad
{
	size_t	pad_hl;
	size_t	pad_pw;
	size_t	pad_gr;
	size_t	pad_size;
	size_t	pad_major;
	size_t	pad_minor;
	size_t	pad_name;
}	t_lspad;

typedef struct s_ls
{
	int				ac;
	int				stat_status;
	int				exit_status;
	int				size_file_lst;
	int				nofirst_dir;
	char			tab_str[4096];
	char			**av;
	char			char_flag;
	char			*tmpdir;
	char			*tmpinter;
	char			perm[11];
	char			empty[1];
	size_t			starting_point;
	size_t			len_link;
	size_t			len_size;
	size_t			iter_lst;
	int				total_blocks;
	unsigned int	flags_info;
	t_list			*dir;
	t_list			*file;
	t_list			*error;
	t_list			*last;
	t_lspad			pad;
	t_erls			error_c;
}	t_ls;

void	count_options(t_ls *ls, int ac, char **av);
int		valid_flag(t_ls *ls);
int		check_files_args(t_ls *ls);
t_list	*process_argument(t_ls *ls, const char *input, t_lstls type);
void	sort_input(t_ls *ls, t_list **begin, int flag);
int		free_lst(t_list **dir, t_list **file, t_list **err);
void	delete_fileinfo(void *fileinfo);
t_list	**dup_arr_lst(t_list **src);
void	delete_lst_arr(t_list ***ptr);
int		print_files_or_error(t_list **begin, t_ls *ls, int error, t_lstls type);
int		calculate_paddings(t_list **begin, t_ls *ls, t_lstls type);
void	store_attributes(t_fileinfo *info, t_ls *ls);
int		print_folder(t_list **begin, t_ls *ls, int flag);
int		loop_dir(t_fileinfo *info, t_ls *ls, t_dircol *col, DIR **tmpdir);
void	check_special_files(t_fileinfo *info, t_ls *ls);
void	padding_file_size(t_fileinfo *info, t_ls *ls);
void	process_link(t_fileinfo **info, t_lstls type, t_ls *ls);
void	print_ext_attr(t_fileinfo *info, t_ls *ls, int *ret_err);
int		process_col(t_ls *ls, t_list **begin);
void	calculate_pad_columns(t_ls *ls, t_list **begin);
void	print_columns(t_ls *ls, t_list **copy, size_t index_arr);
void	handle_colors(t_fileinfo *info, t_ls *ls, mode_t mode);

#endif