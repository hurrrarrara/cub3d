/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   futils.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:02:28 by ihabiby           #+#    #+#             */
/*   Updated: 2024/03/19 18:24:50 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUTILS_H
# define FUTILS_H
# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>

ssize_t	f_ltoa_base(const int fd, long nb, char *base, int base_len);
ssize_t	f_ultoa_base(const int fd, unsigned long nb, char *base, int base_len);
ssize_t	f_itoa_base(const int fd, int nb, char *base, int base_len);
ssize_t	f_uitoa_base(const int fd, unsigned int nb, char *base, int base_len);
ssize_t	f_writer(const int fd, const char *s, va_list list);
ssize_t	f_putstr(const int fd, char *s);
ssize_t	f_print_chr(const int fd, va_list list);
ssize_t	f_print_str(const int fd, va_list list);
ssize_t	f_print_ptr(const int fd, va_list list);
ssize_t	f_print_dec(const int fd, va_list list, char c);
ssize_t	f_print_hex(const int fd, va_list list, char c);
ssize_t	f_putchr(const int fd, char c);
int		f_count_pow(unsigned long n, int base_len);
ssize_t	f_recur_itoa(const int fd, unsigned long nb, char *base, int base_len);
#endif