/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_seek.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <leofariasrj25@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:46:50 by lfarias-          #+#    #+#             */
/*   Updated: 2022/04/23 20:20:19 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int ft_file_size(char *str)
{
	int	fd;
	char *buff;
	int f_size;

	fd = open(str, O_RDONLY);
	if (fd != -1)
	{
		buff = malloc(1);
		f_size = 0;
		while (read(fd, buff, 1) != 0)
			f_size++;
		close(fd);
		free(buff);
		return f_size;
	}
}
