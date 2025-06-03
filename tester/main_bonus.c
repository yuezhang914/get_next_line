/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhang2 <yzhang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:55:04 by yzhang2           #+#    #+#             */
/*   Updated: 2025/06/03 01:58:17 by yzhang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

#define FILE_COUNT 4

static void	open_all(const char **names, int *fd)
{
	int	i;

	i = 0;
	while (i < FILE_COUNT)
	{
		fd[i] = open(names[i], O_RDONLY);
		if (fd[i] < 0)
			printf("❌  open() failed: %s\n", names[i]);
		else
			printf("🗂️   opened %-13s → fd %d\n", names[i], fd[i]);
		i++;
	}
	printf("\n");
}

static void	round_robin(const char **names)
{
	int		fd[FILE_COUNT];
	int		line[FILE_COUNT] = {0};
	int		done;
	char	*txt;
	int		i;

	done = 0;
	open_all(names, fd);
	while (done < FILE_COUNT)
	{
		i = 0;
		while (i < FILE_COUNT)
		{
			if (fd[i] != -1)
			{
				txt = get_next_line(fd[i]);
				if (txt)
				{
					line[i]++;
					printf("fd %-2d (%-13s) line %-3d: %s", fd[i], names[i],
						line[i], txt);
					free(txt);
				}
				else
				{
					printf("fd %-2d (%-13s) EOF\n", fd[i], names[i]);
					close(fd[i]);
					fd[i] = -1;
					done++;
				}
			}
			i++;
		}
	}
	printf("\n✅  round-robin test finished!\n\n");
}

int	main(void)
{
	const char	*files[FILE_COUNT] = {"test1.txt", "empty.txt",
			"no_newline.txt", "long_line.txt"};

	printf("🔎  bonus - multiple-fd test (BUFFER_SIZE = %d)\n\n", BUFFER_SIZE);
	round_robin(files);
	return (0);
}
