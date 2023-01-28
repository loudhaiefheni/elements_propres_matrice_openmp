#include "load_matrix.h"

gsl_spmatrix* charger_matrice(char *nom_fichier){
	
	FILE *f = fopen(nom_fichier, "r");
	if (!f)
	{
		printf("Erreur lors de l'ouverture du fichier!\n");
		exit(EXIT_FAILURE);
	}
	return gsl_spmatrix_fscanf(f);
}

gsl_matrix* remplir_matrice(char *nom_fichier)
{

	// Ouvrir le fichier de marché de matrice
	FILE *f = fopen(nom_fichier, "r");
	if (!f)
	{
		 printf("Erreur lors de l'ouverture du fichier!\n");
		exit(EXIT_FAILURE);
	}

	int lignes, colonnes, non_zeros;

	// Passer l'entête de matrice s'il est là
	char line[256];
	while (fgets(line, sizeof(line), f) != NULL)
	{
		if (line[0] != '%')
			break;
	}

	int ret = sscanf(line, "%d %d %d", &lignes, &colonnes, &non_zeros);
	if (ret != 3)
	{
		printf("Erreur lors de la lecture de l'entête de matrice!\n");
		exit(EXIT_FAILURE);
	}

   // Allouer de la mémoire pour la matrice
	gsl_matrix *matrice = gsl_matrix_alloc(lignes, colonnes);
	if (!matrice)
	{
		printf("Erreur lors de l'allocation de mémoire pour la matrice!\n");
		exit(EXIT_FAILURE);
	}

	// Lire la matrice à partir du fichier
	int i, j;
	double valeur;
	for (int k = 0; k < non_zeros; k++)
	{
		ret = fscanf(f, "%d %d %lf\n", &i, &j, &valeur);
		if (ret != 3)
		{
			printf("Erreur lors de la lecture de l'élément de matrice %d!\n", k);
			exit(EXIT_FAILURE);
		}
		gsl_matrix_set(matrice, i - 1, j - 1, valeur);
		gsl_matrix_set(matrice, j - 1, i - 1, valeur);
	}

	fclose(f);
	return matrice;
}

void afficher_matrice(gsl_matrix *matrice)
{
	// Imprimer la matrice
	for (size_t i = 0; i < matrice->size1; i++)
	{
		for (size_t j = 0; j < matrice->size2; j++)
		{
			printf("%g ", gsl_matrix_get(matrice, i, j));
		}
		printf("\n");
	}
}
