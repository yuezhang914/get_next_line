/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:21:54 by yzhang2           #+#    #+#             */
/*   Updated: 2025/05/29 17:00:33 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_save(int fd, char *backup)
{
	size_t	i;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
}

char	*get_line(char *backup)
{
	char	*line;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (!backup[i])
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	if (backup[i] != '\n')
		len = i;
	else
		len = i + 1;
	line = ft_substr(backup, 0, len);
	return (line);
}

char	*refresh_backup(char *backup)
{
	size_t	i;

	char *fresh_backup i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	fresh_backup = ft_strdup(backup + i + 1);
	free(backup);
	return (fresh_backup);
}

char	*get_next_line(int fd)
{
	static char *backup;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = read_save(fd, backup);
	if (!backup)
		return (NULL);
	line = get_line(backup);
	backup = refresh_backup(backup);
	return (line);
}