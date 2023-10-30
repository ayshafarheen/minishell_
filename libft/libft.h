/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalshebl <nalshebl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:25:19 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/16 22:43:11 by nalshebl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include "ft_printf.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int			ft_strcmp(char *s1, char *s2);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlen(const char *s);
char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *src);
char		*ft_strndup(const char *src, int n);
char		*ft_strchr(const char *s, int c);
char		*ft_strstr(char *str, char *to_find);
char		*ft_strncpy(char *dest, char *src, unsigned int n);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_atoi(const char *str);
char		**ref_split(char const *s, char c);
char		*ft_itoa(int n);
int			ft_isspace(char c);
int			ft_isalnum(char *c);
int			ft_isalnum2(char *c);
int			ft_charisalnum(char c);

#endif
