/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlafouas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:41:06 by vlafouas          #+#    #+#             */
/*   Updated: 2023/12/21 17:11:37 by vlafouas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1u << 10
#endif

char* get_next_line(int fd)
{
	(void)fd;
	printf("%u\n", BUFFER_SIZE);
	return NULL;
}
