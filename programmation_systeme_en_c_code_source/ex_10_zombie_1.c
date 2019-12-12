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

int main(void)
{
	pid_t pid;
	char command[128];

	if((pid = fork()) < 0)
	{
		printf("Echec fork() \n");
		exit(1);
	}

	if (pid == 0)
	{
		// pid == 0, because it's the fils (bitch)
	    sleep(2);
	    printf("le process fils %u se termine \n", getpid());
	    exit(0);
	}
	else
	{
		// process pere:
		sprintf(command, "ps %u", pid);

	}

}