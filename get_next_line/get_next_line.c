/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:21:54 by yzhang2           #+#    #+#             */
/*   Updated: 2025/06/02 23:40:09 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_save(int fd, char *backup)
{
	ssize_t	count;
	char	*buf;
	char	*temp;

	if (!backup && !(backup = ft_strdup("")))
		return (NULL);
	if (!(buf = malloc(BUFFER_SIZE + 1)))
		return (free(backup), NULL);
	count = 1;
	while (!ft_strchr(backup, '\n') && count > 0)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count < 0)
			return (free(buf), free(backup), NULL);
		if (count == 0)
			break ;
		buf[count] = '\0';
		temp = backup;
		backup = ft_strjoin(temp, buf);
		free(temp);
		if (!backup)
			return (free(buf), NULL);
	}
	return (free(buf), backup);
}

char	*get_the_line(char *backup)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!backup || !*backup)
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	if (backup[i] == '\n')
		i++;
	line = ft_substr(backup, 0, i);
	return (line);
}

char	*refresh_backup(char *backup)
{
	size_t	i;
	char	*fresh;

	if (!backup)
		return (NULL);
	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	fresh = ft_strdup(backup + i + 1);
	free(backup);
	return (fresh);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = read_save(fd, backup);
	if (!backup)
		return (NULL);
	line = get_the_line(backup);
	backup = refresh_backup(backup);
	if (!line)
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	return (line);
}
