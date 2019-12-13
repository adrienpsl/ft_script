/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpusel <adpusel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 10:48:07 by adpusel           #+#    #+#             */
/*   Updated: 2017/11/16 12:45:50 by adpusel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
# include "stdlib.h"
# include "unistd.h"
# include "signal.h"
# include "errno.h"
# include "sys/wait.h"
# include "sys/resource.h"

int
main(void)
{
	pid_t pid;
	int status;
	int j, i;
	struct rusage usage;

	pid = fork();
	if (pid == 0)
	{
		printf("Fils : PID = %u\n", getpid());
		j = 0;
		for (i = 0; i < 5000000; ++i)
			j += i;
		raise(SIGSTOP);
		for (int k = 0; k < ; ++k)

	}
}