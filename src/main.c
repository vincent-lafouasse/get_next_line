/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlafouas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:11:45 by vlafouas          #+#    #+#             */
/*   Updated: 2023/12/21 21:20:23 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define PATH "./aux/short.txt"

int main(void)
{
	int fd = open(PATH, O_RDONLY);

	char buffer[BUFFER_SIZE];
	bzero(buffer, BUFFER_SIZE);

	size_t i = 0;

	while (read(fd, buffer + i, 1) > 0)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			break;
		}
		i++;
	}
	printf("first line\n");
	printf("%s\n", buffer);

	bzero(buffer, BUFFER_SIZE);
	i = 0;
	while (read(fd, buffer + i, 1) > 0)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			break;
		}
		i++;
	}
	printf("second line\n");
	printf("%s\n", buffer);

}
