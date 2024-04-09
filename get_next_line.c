/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:07:00 by tchaloei          #+#    #+#             */
/*   Updated: 2024/04/03 15:09:32 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*clean_the_stash(char *str)
{
	char	*stash;
	size_t	i;
	size_t	j;

	if (!*str)
		return (free(str), NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	stash = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!stash)
		return (NULL);
	j = i;
	while (str[i])
	{
		stash[i - j] = str[i];
		i++;
	}
	stash[i - j] = '\0';
	if (!*stash)
		return (free(str), free(stash), NULL);
	free(str);
	return (stash);
}

static char	*get_the_line(char *str)
{
	char	*line;
	size_t	i;
	size_t	j;

	if (!*str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*free_stash(char *line, char *stash)
{
	free(line);
	free(stash);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			read_b;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	read_b = 1;
	while (!(ft_strchr(stash, '\n')) && read_b != 0)
	{
		read_b = read(fd, line, BUFFER_SIZE);
		if (read_b == -1)
		{
			stash = free_stash(line, stash);
			return (NULL);
		}
		line[read_b] = '\0';
		stash = ft_strjoin(stash, line);
	}
	free(line);
	line = get_the_line(stash);
	stash = clean_the_stash(stash);
	return (line);
}
