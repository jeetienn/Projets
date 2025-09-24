/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeetienn <jeetienn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:05:45 by jeetienn          #+#    #+#             */
/*   Updated: 2025/03/27 17:58:59 by jeetienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// HEADERS //

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <ctype.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdint.h>

// #include <bsd/string.h>

// PROTOTYPES //

// Prototypes de libft
int				ft_atoi(const char *str);
void			*ft_bzero(void *s, int n);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int nb, int fd);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char *s1, char *s2);
unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size);
unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size);
size_t			ft_strlen(char *str);
int				ft_strncmp( char *s1, char *s2, size_t n);
char			*ft_strnstr(char *str, char *to_find, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_substr(char *s, unsigned int start, size_t len);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strmapi(char *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			**ft_split(char *s, char c);
char			*ft_itoa(int n);
char			*ft_strdup(char *s);
char			*ft_strtrim(char *s1, char *set);
int				ft_strcmp(const char *s1, const char *s2);

// Prototypes de ft_printf
int				ft_printf(const char *format, ...);
int				ft_print_hex(unsigned int n, const char format);
int				ft_print_nbr(int n);
int				ft_percent(void);
int				ft_print_ptr(void *ptr);
int				ft_print_u(unsigned int n);
int				ft_print_char(char c);
int				ft_print_c(int c);
int				ft_printstr(char *str);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32 // Valeur par défaut pour get_next_line
# endif

// Prototype de get_next_line
char			*get_next_line(int fd);
size_t			ft_strlengnl(const char *s);
void			ft_strcat(char **dst_ptr, const char *src);
#endif