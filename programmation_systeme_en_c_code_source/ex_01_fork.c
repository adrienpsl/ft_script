/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpusel <adpusel@student.42.fr>            +#+  +:+       +#+        */

/*   Created: 2017/10/19 10:48:07 by adpusel           #+#    #+#             */
/*   Updated: 2017/11/16 12:45:50 by adpusel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "errno.h"
# include "sys/wait.h"

int main(void)
{
	pid_t pid_fils;
	
	/* si je ne peux pas fork, c'est que le system est dans un
	 * etat critique, il serait plus jusdicieux d'attendre entre
	 * les syscall */
	do
	{
		pid_fils = fork();
	} while ((pid_fils == -1) && (errno == EAGAIN));

	// error -------------------------------------------------------------------
	if (pid_fils == -1)
	{
		fprintf(stderr, "fork() impossible errno=%d\n", errno);
		return (1);
	}
	
	if (pid_fils == 0)
	{
		fprintf(stdout, "Fils : PID=%d, PPID=%d\n",
			getpid(), getppid());
		wait(NULL);
		return (0);
	}
	else {
		fprintf(stdout, "Pere : PID=%d, PPID=%d\n", getpid(), getppid());
		wait(NULL);
		return (0);
	}
}
