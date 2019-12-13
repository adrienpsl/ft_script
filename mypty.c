
#define _XOPEN_SOURCE 600

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
	int fdm;
	int rc;

	// Affichage de /dev/pts
//	system("ls -l /dev/ttys*");

	if ((open("/dev/ptmx", O_RDWR | O_NOCTTY)) < 0)
		printf("no ptmx");
	else
		printf("ptmx ok\n");

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

	// Affichage des changements dans /dev/pts
//	system("ls -l /dev/ptmx");

	printf("Le pseudo-terminal esclave a pour nom : %s\n", ptsname(fdm));
	return 0;
} // main