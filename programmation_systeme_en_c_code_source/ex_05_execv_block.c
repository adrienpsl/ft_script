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
# include "fcntl.h"
# include "stdio.h"
# include "unistd.h"
# include "errno.h"
int main(int argc, char *argv[])
{
	int fd;
	char *nv_argv[] = { "./a.out", NULL };

	fprintf(stdout, "Essai d'ouverture de %s ..." , argv [0]);

	if ((fd = open(argv[0], O_WRONLY | O_APPEND)) < 0)
	{
		if (errno != ETXTBSY)
		{
			fprintf(stdout, "impossible, errno %d\n", errno);
			exit(1);
		}
		fprintf(stdout, "échec ETXTBSY, fichier déjà utilisé \n");
	}

	fprintf(stdout, "Ouverture de exemple_execvp en écriture ... ");
	if ((fd = open("a.out", O_WRONLY | O_APPEND)) < 0)
	{
		fprintf(stdout, "impossible, errno %d\n", errno);
		exit(1);
	}

	fprintf(stdout, "ok \n Tentative d'exécuter exemple_execvp ... ");
	execv("./a.out", nv_argv);

	if (errno == ETXTBSY)
		fprintf(stdout, "échec ETXTBSY fichier déjà utilisé \n");
	else
		fprintf(stdout, "errno = %d\n", errno);
	return (1);
}
