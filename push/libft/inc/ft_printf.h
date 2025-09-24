/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:34:38 by jeetienn          #+#    #+#             */
/*   Updated: 2025/01/22 19:34:41 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdint.h>

int			ft_ptr_len(uintptr_t num);
void		ft_put_ptr(uintptr_t num);
int			ft_print_ptr(void *ptr);
void		ft_putstr(char *str);
int			ft_printstr(char *str);
int			ft_printnbr(int n);
int			ft_printpercent(void);
int			ft_print_c(int c);
int			ft_printf(const char *str, ...);
int			ft_printnbr(int n);
int			ft_percent(void);
int			ft_print_u(unsigned int n);
int			ft_len_num(unsigned	int num);
int			ft_print_hex(unsigned int num, const char format);
void		ft_put_hex(unsigned int num, const char format);
int			ft_hex_len(unsigned	int num);
int			ft_formats(va_list args, const char format);

#endif