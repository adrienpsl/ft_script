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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int
main(void)
{
	FILE *message;
	char *commande;
	if ((commande = (char *)malloc(strlen(getlogin()) + 6)) == NULL)
	{
		fprintf(stderr, "Erreur malloc %d\n", errno);
		exit(1);
	}
	strcpy(commande, "mail ");
	strcat(commande, getlogin());
	if ((message = popen(commande, "w")) == NULL)
	{
		fprintf(stderr, " Erreur popen %d \n", errno);
		exit(1);
	}
	fprintf(message, "Ceci est un message \n");
	fprintf(message, "émis par moi-meme\n");
	pclose(message);
	return(0);
}
