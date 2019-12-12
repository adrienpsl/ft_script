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

void
gestion_sortie(int code, void *ptr)
{
	printf("call with the exit code : %d", code);
	if (ptr == NULL)
	    printf("No file add");
	else
	{
		printf("fermeture du file \n");
		fclose((FILE *)ptr);
	}
}

int
main(void)
{
	FILE *fp;

	fp = fopen("exemple_atexit.c", "r");
	if (on_exit(gestion_sortie, (void *)fp) != 0)
		fprintf(stderr, "Erreur dans on_exit \n");

	// the ptr has been save inside the on_exit, that is so cool !
	fp = fopen("exemple_atexit.c", "r");
	if (on_exit(gestion_sortie, (void *)fp) != 0)
		fprintf(stderr, "Erreur dans on_exit \n");
}

