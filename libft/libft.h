/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:26:16 by makarkao          #+#    #+#             */
/*   Updated: 2025/07/14 10:19:45 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct sp_var
{
	size_t			i;
	size_t			j;
	size_t			k;
}					t_spvar;

long long			ft_atoll(const char *str, int *flag);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_itoa(int x);
int					ft_isdigit(int c);
int					ft_putchar_fd(int fd, char c);
int					ft_putnbr_fd(int fd, int n);
int					ft_putstr_fd(int fd, char *s);
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
ssize_t				ft_chrinstr(char *str, char c);
int					ft_isalnum(int c);
char				*ft_slashjoin(char *s1, char *s3);
int					ft_numericheck(char *num);
int					ft_isalpha(int c);
void				ft_concat(char *dest, char *src, int *i);
char				*ft_sthreecat(char *s1, char *s2, char *s3);
char				*ft_strsjoin(char **strs, char c);

#endif
