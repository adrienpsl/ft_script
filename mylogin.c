#include <stdio.h>

int main(void)
{
	char nom_de_login[150];
	char mot_de_passe[150];

	printf("%lu\n", sizeof(void*));
	printf("%lu\n", sizeof(int));
	// Par défaut stdin, stdout et stderr sont ouverts
	fprintf(stdout, "login : ");
	if (NULL == fgets(nom_de_login, sizeof(nom_de_login), stdin))
	{
		fprintf(stderr, "Pas de nom de login\n");
		return 1;
	}

	fseek(stdin, 0, SEEK_END);
	fprintf(stdout, "Mot de passe : ");
	if (NULL == fgets(mot_de_passe, sizeof(mot_de_passe), stdin))
	{
		fprintf(stderr, "Pas de mot de passe\n");
		return 1;
	}

	fprintf(stdout, "La saisie est :\n%s%s\n", nom_de_login, mot_de_passe);
	return 0;
}
