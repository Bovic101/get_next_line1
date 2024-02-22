/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 00:59:52 by vodebunm          #+#    #+#             */
/*   Updated: 2024/02/22 11:49:34 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// allocate sufficient memory for a copy of the string
char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len_s1;

	len_s1 = ft_strlen(s1) + 1;
	ptr = malloc(len_s1 * sizeof(char));
	if (!ptr)
	{
		return (0);
	}
	ft_memcpy(ptr, s1, len_s1 - 1);
	ptr[len_s1 - 1] = '\0';
	return (ptr);
}

static char	*scan_new_line(char *line)
{
	char	*l2;
	size_t	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (NULL);
	l2 = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*l2 == '\0')
	{
		free(l2);
		l2 = NULL;
	}
	line[i + 1] = '\0';
	return (l2);
}

static char	*find_new_line(int fd, char *buffer, char *backup)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!backup)
			backup = ft_strdup("");
		temp = backup;
		backup = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*backup;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (!buffer)
		return (NULL);
	line = find_new_line(fd, buffer, backup);
	free(buffer);
	if (!line)
		return (line);
	backup = extract_new_line(line);
	return (line);
}
