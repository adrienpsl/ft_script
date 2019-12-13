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
# include "sys/resource.h"
# include "sys/wait.h"

int
main(void)
{
	struct rlimit limit;
	pid_t pid;

	if (getrlimit(RLIMIT_NPROC, &limit) != 0)
	{
		perror("getrlimit");
		exit(EXIT_FAILURE);
	}
	limit.rlim_cur = 160;
	if (setrlimit(RLIMIT_NPROC, &limit) != 0)
	{
	    perror("setrlimit");
	    exit(1);
	}
	while (1)
	{
	    pid = fork();
	    if (pid == (pid_t) -1)
	    {
	        perror("fork");
	        exit(1);
	    }
	    if (pid != 0)
	    {
	        printf("%ld \n", (long)pid);
	        if (waitpid(pid, NULL, 0) != pid)
	            perror("waitpid");
			break;
	    }
	    return (0);
	}

}


