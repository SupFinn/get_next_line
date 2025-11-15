/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 04:03:39 by rhssayn           #+#    #+#             */
/*   Updated: 2025/11/15 10:40:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*join_and_free(char *remainder, char *buffer)
{
	char	*joined;

	joined = ft_strjoin(remainder, buffer);
	free(remainder);
	return (joined);
}

char	*read_and_join(int fd, char *remainder)
{	
	char		*buffer;
	ssize_t		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!remainder)
		remainder = ft_strdup("");
	bytes = 1;
	while (!ft_strchr(remainder, '\n') && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			free(remainder);
			return (NULL);
		}
		buffer[bytes] = '\0';
		remainder = join_and_free(remainder, buffer);
	}
	free (buffer);
	return (remainder);
}

char	*extract_line(char *remainder)
{
	char	*line;
	char	*newline_pos;
	size_t	len;

	if (!remainder)
		return (NULL);
	newline_pos = ft_strchr(remainder, '\n');
	if (!newline_pos)
		return (ft_strdup(remainder));
	len = ft_strlen(remainder) - ft_strlen(newline_pos) + 1;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_strncpy(line, remainder, len);
	return (line);
}

char	*update_remainder(char *remainder)
{
	char	*newline_pos;
	char	*new_remainder;
	size_t	len;

	if (!remainder)
		return (NULL);
	newline_pos = ft_strchr(remainder, '\n');
	if (!newline_pos || newline_pos[1] == '\0')
	{
		free (remainder);
		return (NULL);
	}
	len = ft_strlen(newline_pos + 1);
	new_remainder = malloc(len + 1);
	if (!new_remainder)
	{
		free(remainder);
		return (NULL);
	}
	ft_strncpy(new_remainder, newline_pos + 1, len);
	free(remainder);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char		*remainder[1024];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder[fd] = read_and_join(fd, remainder[fd]);
	if (!remainder[fd] || remainder[fd][0] == '\0')
	{
		free(remainder[fd]);
		remainder[fd] = NULL;
		return (NULL);
	}
	line = extract_line(remainder[fd]);
	remainder[fd] = update_remainder(remainder[fd]);
	return (line);
}
