/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maltahay <maltahay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 00:00:00 by maltahay          #+#    #+#             */
/*   Updated: 2026/10/26 00:00:00 by maltahay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	dup = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static void	ft_cat(char *dst, const char *src, size_t *pos)
{
	size_t	i;

	if (!src)
		return ;
	i = 0;
	while (src[i])
	{
		dst[*pos] = src[i];
		(*pos)++;
		i++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	pos;

	if (!s2)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	pos = 0;
	ft_cat(res, s1, &pos);
	ft_cat(res, s2, &pos);
	res[pos] = '\0';
	free(s1);
	return (res);
}
