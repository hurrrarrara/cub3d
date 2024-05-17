/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihabiby <ihabiby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:02:28 by ihabiby           #+#    #+#             */
/*   Updated: 2023/11/21 15:07:04 by ihabiby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stdarg.h>
# include <unistd.h>
# include <stddef.h>

ssize_t	_ltoa_base(long nb, char *base, int base_len);
ssize_t	_ultoa_base(unsigned long nb, char *base, int base_len);
ssize_t	_itoa_base(int nb, char *base, int base_len);
ssize_t	_uitoa_base(unsigned int nb, char *base, int base_len);
ssize_t	_writer(const char *s, va_list list);
ssize_t	_putstr(char *s);
ssize_t	_print_chr(va_list list);
ssize_t	_print_str(va_list list);
ssize_t	_print_ptr(va_list list);
ssize_t	_print_dec(va_list list, char c);
ssize_t	_print_hex(va_list list, char c);
ssize_t	_putchr(char c);
int		_count_pow(unsigned long n, int base_len);
ssize_t	_recur_itoa(unsigned long nb, char *base, int base_len);
#endif