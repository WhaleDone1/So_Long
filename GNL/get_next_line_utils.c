/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barpent <barpent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:22:37 by bcarpent          #+#    #+#             */
/*   Updated: 2024/02/29 14:21:58 by barpent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int check_nl(char *stash)
{
	size_t i;

	i = -1;
	if (!stash)
		return (-1);
	while (stash[++i])
		if (stash[i] == '\n')
			return (i);
	return (-1);
}

char *ft_strcpy(char *dst, const char *src)
{
	size_t i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

char *ft_strjoin(char *stash, char *buffer)
{
	char *result;
	size_t i;
	size_t a;

	a = -1;
	i = -1;
	result = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buffer) + 1));
	if (!result)
		return (NULL);
	while (stash[++i])
		result[i] = stash[i];
	while (buffer[++a])
		result[i++] = buffer[a];
	result[i] = 0;
	free(stash);
	return (result);
}

char *ft_strdup(char *buffer)
{
	char *result;
	size_t i;

	i = -1;
	result = malloc(sizeof(char) * (ft_strlen(buffer) + 1));
	if (!result)
		return (NULL);
	while (buffer[++i])
		result[i] = buffer[i];
	result[i] = 0;
	return (result);
}
