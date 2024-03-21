/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barpent <barpent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:06:11 by bcarpent          #+#    #+#             */
/*   Updated: 2024/02/29 14:21:31 by barpent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *ft_read_file(char *stash, char *buffer, int fd)
{
	int read_count;

	read_count = read(fd, buffer, BUFFER_SIZE);
	while (read_count > 0)
	{
		buffer[read_count] = 0;
		if (!stash)
			stash = ft_strdup(buffer);
		else
			stash = ft_strjoin(stash, buffer);
		if (!stash || check_nl(stash) != -1)
			break;
		else
			read_count = read(fd, buffer, BUFFER_SIZE);
	}
	if (read_count < 0)
	{
		if (stash)
			free(stash);
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (stash);
}

static char *ft_get_line(char *stash)
{
	int size;
	int i;
	char *line;

	size = check_nl(stash);
	if (size == -1)
		size = ft_strlen(stash);
	else
		size++;
	line = malloc(sizeof(char) * (size + 1));
	if (!line)
		return (NULL);
	i = -1;
	while (++i < size)
		line[i] = stash[i];
	line[i] = 0;
	return (line);
}

static char *ft_next_line(char *stash)
{
	int i;
	int size;
	char *new_stash;

	i = check_nl(stash);
	size = 0;
	new_stash = NULL;
	if (i == -1)
	{
		free(stash);
		return (new_stash);
	}
	if (stash[i] && stash[i + 1])
		while (stash[i + size])
			size++;
	if (size > 0)
	{
		new_stash = malloc(sizeof(char) * (size));
		if (new_stash)
			ft_strcpy(new_stash, stash + i + 1);
	}
	free(stash);
	return (new_stash);
}

char *get_next_line(int fd)
{
	static char *stash;
	char *buffer;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	stash = ft_read_file(stash, buffer, fd);
	if (!stash)
		return (NULL);
	line = ft_get_line(stash);
	stash = ft_next_line(stash);
	return (line);
}