/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:58:30 by cauranus          #+#    #+#             */
/*   Updated: 2020/01/17 18:58:33 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

int	g_count;

typedef struct	s_flags
{
	char		flag;
	char		zero;
	char		hash;
	char		minus;
	char		plus;
	char		space;
	int			width;
	int			precision;
	char		size;
	char		type;
	char		dot;
	char		error;
	int			index;
}				t_flags;

int				ft_printf(const char *format, ...);
char			*base_10_trans(uintmax_t n, int base, t_flags print);
char			*base_16_trans(uintmax_t n, int up, t_flags *print);
char			*put_addr(uintmax_t n, t_flags print);
void			ft_putchar(char c);
void			ft_putnbr_unsigned(unsigned int n);
void			ft_putnbr(int n);
void			ft_putstr(char const *s);
size_t			ft_strlen(const char *s);
char			*ft_strnew(size_t size);
char			*ft_strrev(char *s);
int				ft_atoi(const char *str);
char			*ft_itoa_p(intmax_t n);
void			put_int(char *str, t_flags print);
t_flags			init_print();
void			put_int_unsigned(char *str, t_flags print);
char			*ft_itoa_unsigned(uintmax_t n, t_flags print);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_swapfree(void **ptr, void *ptr2);
void			*ft_memalloc(size_t size);
void			ft_bzero(void *s, size_t n);
void			putst(char *str, t_flags print);
int				ft_strcmp(const char *s1, const char *s2);
void			put_char(wchar_t c, t_flags print);
char			*ft_dtoa(long double n, t_flags *print);
void			ft_unicode(wchar_t c);
void			putstl(wchar_t *str, t_flags print);
size_t			ft_strlenw(const wchar_t *s);
void			put_16x(char *str, t_flags print);
int				get_flags(va_list va, t_flags print);
void			get_ints(va_list va, t_flags print);
void			get_unsigned(va_list va, t_flags print);
void			get_o(va_list va, t_flags print);
void			get_x(va_list va, t_flags print);
void			put_16x_plus(char *str, t_flags print, int i, int len);
void			put_16x_minus(char *str, t_flags *print, int i, int len);
void			ft_unicode2(wchar_t c);
void			check_len(uintmax_t len, char *str, uintmax_t *i, int up);
void			put_int_minus(char *str, t_flags print, int len, int i);
void			put_int_plus(char *str, t_flags print, int len, int i);
void			put_int_plus2(char *str, t_flags print, int *i);
void			put_int_unsigned_minus(char *str, t_flags print, int l);
void			put_int_unsigned_plus(char *str, t_flags print, int len);
void			putst_plus(char *str, t_flags print, int len);
void			putstl_minus(wchar_t *str, t_flags print, int i, int len);
void			putstl_plus(wchar_t *str, t_flags print, int i, int len);
long double		round_of(long double nb, int power);
t_flags			parce(const char *format, int i);

#endif
