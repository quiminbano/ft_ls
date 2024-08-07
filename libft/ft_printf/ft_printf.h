/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:46:08 by corellan          #+#    #+#             */
/*   Updated: 2024/06/16 23:16:17 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef STRBUFFER
#  define STRBUFFER 2
# endif

# if STRBUFFER <= 0
#  undef STRBUFFER
#  define STRBUFFER 4096
# endif

# include <stdarg.h>
# include "../libft.h"

typedef enum e_typeprintf
{
	PRINTF,
	SPRINTF
}	t_typeprintf;

typedef enum e_base
{
	NORMAL,
	UPPER,
	LOWER
}	t_base;

typedef enum e_char
{
	CHAR,
	NUMBER,
	NOCONV
}	t_char;

typedef enum when
{
	BEFORE,
	AFTER
}	t_when;

typedef struct s_flags
{
	char	begin;
	char	conv;
	int		orig_num;
	int		dot_number;
	int		has_minus;
	int		has_dot;
	int		has_pure_number;
	int		has_zero;
	int		has_sharp;
	int		has_space;
	int		has_plus;
	int		neg;
	size_t	size_dot;
	size_t	size_print;
	t_base	type_sharp;
	va_list	*ptr;
}	t_flags;

typedef struct s_printf
{
	char			*str;
	char			buffer[STRBUFFER + 1];
	char			ul_buf[21];
	char			*str_sprintf;
	int				count;
	int				return_status;
	int				fd;
	size_t			buffer_idx;
	size_t			index;
	size_t			size_number;
	size_t			count_buf;
	size_t			pos_str;
	t_flags			flags;
	t_typeprintf	type;
}	t_printf;

int		ft_printf(const char *s, ...);
int		ft_dprintf(int fd, const char *s, ...);
int		ft_sprintf(char *str, const char *s, ...);
int		str_return(char *str, t_printf *data);
int		char_return(char c, t_printf *data, t_char flag);
int		nbr_return(long long number, t_base base, t_printf *data);
int		append_unsigned(unsigned long number, t_base base, t_printf *data);
int		append_number(unsigned long number, t_base base, t_printf *data);
int		append_char(t_printf *data, char c, size_t idx);
int		append_str(t_printf *data, char const *str, size_t n);
int		return_interface(va_list *ar, t_printf *data);
int		check_undef(const char *s, size_t *af, t_printf *data, va_list *ar);
void	fill_format(t_flags *fl, size_t begin, size_t end, const char *s);
int		fill_ident(t_flags *fl, size_t *begin, size_t end, const char *s);
size_t	length_number(const char c, va_list *ar, int base);
int		append_identation(t_printf *data, size_t size_parameter, t_when when);
int		append_zeros(size_t max, t_printf *data);
int		special_case(t_printf *data);

#endif
