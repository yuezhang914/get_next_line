/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:22:08 by yzhang2           #+#    #+#             */
/*   Updated: 2025/06/03 15:45:36 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*join_free(char *s1, char *s2)
{
	char	*joined;
	char	*tmp;

	tmp = s1;
	joined = ft_strjoin(tmp, s2);
	free(tmp);
	return (joined);
}

char	*read_save(int fd, char *backup)
{
	ssize_t	count;
	char	*buf;

	if (!backup)
		backup = ft_strdup("");
	if (!backup)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(backup), NULL);
	count = 1;
	while (backup && !ft_strchr(backup, '\n') && count > 0)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count < 0)
			return (free(buf), free(backup), NULL);
		if (count == 0)
			break ;
		buf[count] = '\0';
		backup = join_free(backup, buf);
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
	static char	*backup[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	backup[fd] = read_save(fd, backup[fd]);
	if (!backup[fd])
		return (NULL);
	line = get_the_line(backup[fd]);
	backup[fd] = refresh_backup(backup[fd]);
	if (!line)
	{
		free(backup[fd]);
		backup[fd] = NULL;
		return (NULL);
	}
	return (line);
}
