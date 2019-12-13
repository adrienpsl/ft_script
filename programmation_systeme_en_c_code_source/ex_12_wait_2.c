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
# include "sys/wait.h"

int main(void)
{
	pid_t pid;
	int status;

	switch (pid == fork()) {
		case -1:
			printf("Error in fork \n");
			exit(-1);
		case 0: // fils
			printf("Fils 1 : PID = %u\n", getpid());
			while (1)
			    pause();
		default:
			break;
	}
	// creons un fils que l'on n'attend pas
	switch (fork())
	{
		case -1:
			printf("Fork error \n");
			exit(1);
		case 0: // fils  2
			printf(" \n");
			sleep(2);
			exit(0);
		default:
			break;
	}
	while (1)
	{
		sleep(1);
		if (waitpid(pid, &status, WUNTRACED | WNOHANG) > 0)

	}
}