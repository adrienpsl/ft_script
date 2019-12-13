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

#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#define __USE_BSD
#include <termios.h>

int main(void)
{
	int  fdm, fds, rc;
	char input[150];

	fdm = posix_openpt(O_RDWR);
	if (fdm < 0)
	{
		fprintf(stderr, "Erreur %d sur posix_openpt()\n", errno);
		return 1;
	}

	rc = grantpt(fdm);
	if (rc != 0)
	{
		fprintf(stderr, "Erreur %d sur grantpt()\n", errno);
		return 1;
	}

	rc = unlockpt(fdm);
	if (rc != 0)
	{
		fprintf(stderr, "Erreur %d sur unlockpt()\n", errno);
		return 1;
	}

	// Ouverture du PTY esclave
	fds = open(ptsname(fdm), O_RDWR);

	// Création d'un processus fils
	if (fork())
	{
		// Code du processus pere

		// Fermeture de la partie esclave du PTY
		close(fds);

		while (1)
		{
			// Saisie operateur (entree standard = terminal)
			write(1, "Entree : ", sizeof("Entree : "));

			rc = read(0, input, sizeof(input));

			if (rc > 0)
			{
				// Envoie de la saisie aux processus fils via le PTY
				write(fdm, input, rc);

				// Lecture de la reponse du fils dans le PTY
				rc = read(fdm, input, sizeof(input) - 1);

				if (rc > 0)
				{
					// Ajout d'une fin de chaine en fin de buffer
					input[rc] = '\0';

					fprintf(stderr, "%s", input);
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		} // End while
	}
	else
	{
		struct termios slave_orig_term_settings; // Saved terminal settings
		struct termios new_term_settings; // Current terminal settings

		// Code du processus fils

		// Fermeture de la partie maitre du PTY
		close(fdm);

		// Sauvegarde des parametre par defaut du PTY esclave
		rc = tcgetattr(fds, &slave_orig_term_settings);

		// Positionnement du PTY esclave en mode RAW
		new_term_settings = slave_orig_term_settings;

		cfmakeraw (&new_term_settings);
		tcsetattr (fds, TCSANOW, &new_term_settings);

		// Le cote esclave du PTY devient l'entree et les sorties standards du fils
		close(0); // Fermeture de l'entrée standard (terminal courant)
		close(1); // Fermeture de la sortie standard (terminal courant)
		close(2); // Fermeture de la sortie erreur standard (terminal courant)
		dup(fds); // Le PTY devient l'entree standard (0)
		dup(fds); // Le PTY devient la sortie standard (1)
		dup(fds); // Le PTY devient la sortie erreur standard (2)
		system("ls");

		while (1)
		{
			rc = read(fds, input, sizeof(input) - 1);
			if (rc > 0)
			{
				// Remplacement du retour a la ligne par une fin de chaine
				input[rc - 1] = '\0';

				printf("Le fils a recu : '%s'\n", input);
			}
			else
			{
				break;
			}
		} // End while
	}

	return 0;
} // main