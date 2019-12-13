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

void affichage_type_de_terminaison(pid_t pid, int status);
int processus_fils(int numero_fils);

int main(void)
{
	pid_t pid;
	int status;
	int numero_fils;

	for (numero_fils = 0; numero_fils < 4; ++numero_fils)
	{
		switch (fork())
		{
			case -1:
				printf("Error fork \n");
				exit(1);
			case 0:
				printf("Fils %d : PID = %u\n", numero_fils, getpid())
				return (processus_fils(numero_fils));
			default:
				break
		}
	}
	// here only father remain
	while ((pid == wait(&status) > 0))
	{
	    affichage_type_de_terminaison(pid, status);
	}

}

void
affichage_type_de_terminaison(pid_t pid, int status)
{
	printf("le process %u", pid);
	if (WFEXITED(status))
		printf("s'est terminer normalement code : %d\n", WEXITSTATUS(status));
	else if(WFSIGNALED(status))
	{
		printf("Terminer a cause de :%d (%s)\n", WTERMSIG(status),
			sys_siglist[WTERMSIG(status)]);
		if (WOCOREDUMP(status))
		    printf("fichier core created");
	}
	else if(WFSTOPPED(status)) {
		printf("Stop a cause de :%d (%s)\n", WSTOPSIG(status),
			sys_siglist[WSTOPSIG(status)]);
	}
}

int processus_fils(int nb)
{
	switch (nb){
		case 0:
			return (1);
		case 1:
			exit (2);
		case 2:
			abort();
		case 3:
			raise(SIGUSR1);
	}
	return (nb);
}