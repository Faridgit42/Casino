#include "bibcarte.h"

int ft_calcule_nb_entrer_fichier(char * str)
{
    FILE* fichier = NULL;
    char ligne[100];
    int i;
    fichier = fopen(str, "r");
    for (i = 0; fgets(ligne, 100, fichier) != NULL; ++i);
    fclose(fichier);
    return (i);
}

void ft_suppsautdeligne(char str[60][40], int x)
{
    int i;
    int j;

    for (i = 0; i <= x - 1 ; ++i)
    {   
        for(j = 0; j <= 40; ++j)
        {
            if(str[i][j] == '\r' || str[i][j] == '\n')
                str[i][j] = '\0';
        }
    }
}

void    ft_ini_croisement(SCARTE *paquet, char *suite, char *couleur)
{
    FILE* fsuite = fopen(suite, "r");
    char esuite[60][40];
    int crt;
    int crtmax;
    FILE* fcouleur = fopen(couleur, "r");
    char ecouleurs[60][40];
    int clr;
    int clrmax;
    int x; // nb de cartes
    int i; //les carasuit
    int j; //mini
    char buffvaleur[10];
    char matrix[8][20] = {
                        " __________ ",
                        "|          |",
                        "| x        |",
                        "|          |",
                        "|     x    |",
                        "|          |",
                        "|        x |",
                        "|__________|"};

    if (fsuite == NULL || fcouleur == NULL)
    {
        ft_putstr("Erreur lors de l'ouverture des fichiers textes");
        exit(1);
    }
    for (crtmax = 0; fgets(esuite[crtmax], sizeof esuite, fsuite) != NULL; ++crtmax);
    ft_suppsautdeligne(esuite, crtmax);
    for (clrmax = 0; fgets(ecouleurs[clrmax], sizeof ecouleurs, fcouleur) != NULL; ++clrmax);
    ft_suppsautdeligne(ecouleurs, clrmax);

    for ( x = ft_nbr_carte(paquet), clr = 1, crt = 0; clr <= clrmax - 1; ++x)
    {
        paquet[x].matricule = x +1;
        for (i = 0; esuite[crt][i] !='*'; ++i)
		    paquet[x].suite[i] = esuite[crt][i];
	    paquet[x].suite[i] = '\0';
        i++;
        for (j = 0; esuite[crt][i] !='*'; ++i, ++j)
		    paquet[x].minisuite[j] = esuite[crt][i];
	    paquet[x].minisuite[j] = '\0';
        ++i;
        for (j = 0; esuite[crt][i] !='\0'; ++i, ++j)
		    buffvaleur[j] = esuite[crt][i];
	    buffvaleur[j] = '\0';
        paquet[x].valeur = ft_miniatoi(buffvaleur);
//couleur
        for (i = 0; ecouleurs[clr][i] !='*'; ++i)
		    paquet[x].couleur[i] = ecouleurs[clr][i];
	    paquet[x].couleur[i] = '\0';
        i++;
        for (j = 0; ecouleurs[clr][i] !='\0'; ++i, ++j)
		    paquet[x].minicouleur[j] = ecouleurs[clr][i];
	    paquet[x].minicouleur[j] = '\0';
        ft_strcpy(paquet[x].jonction, ecouleurs[0]);
//matrix
        for(j = 0; j <= 7; ++j)
            ft_strcpy(paquet[x].matrix[j], matrix[j]);   
        for(j = 0; paquet[x].minicouleur[j] != '\0'; ++j)
            paquet[x].matrix[4][6+j] = paquet[x].minicouleur[j];
        //Bonjour les unicodes qui prenne 3 cara pour en afficher 1
        if(paquet[x].minicouleur[0] <= 31)
            {
                paquet[x].matrix[4][14] = '\0';
                paquet[x].matrix[4][13] = '|';
                paquet[x].matrix[4][12] = ' ';
                paquet[x].matrix[4][11] = ' ';
            }
        for(j = 0; paquet[x].minisuite[j] != '\0'; ++j)
            paquet[x].matrix[2][2+j] = paquet[x].minisuite[j];
        for(j = 0; paquet[x].minisuite[j] != '\0'; ++j)
            paquet[x].matrix[6][9+j] = paquet[x].minisuite[j];
        ++crt;
        if (crt == crtmax)
        {
            crt = 0;
            ++clr;
        }
    }
    paquet[x].valeur = -999;
    paquet[x].suite[0] = '\0';
    paquet[x].couleur[0] = '\0';
    fclose(fsuite);
    fclose(fcouleur);
}

void    ft_ini_simple(SCARTE *paquet, char *suite)
{
    FILE* fsuite = fopen(suite, "r");
    char esuite[60][40];
    int crt;
    int crtmax;
    int x; // nb de cartes
    int i; //les carasuit
    int j; //mini
    char buffvaleur[10];
    char matrix[8][20] = {
                        " __________ ",
                        "|          |",
                        "| x        |",
                        "|          |",
                        "|     x    |",
                        "|          |",
                        "|        x |",
                        "|__________|"};

    if (fsuite == NULL)
    {
        ft_putstr("Erreur lors de l'ouverture des fichiers textes");
        exit(1);
    }
    for (crtmax = 0; fgets(esuite[crtmax], sizeof esuite, fsuite) != NULL; ++crtmax);
    ft_suppsautdeligne(esuite, crtmax);
    for (x = ft_nbr_carte(paquet), crt = 0; crt <= crtmax - 1; ++x)
    {
        paquet[x].matricule = x +1;
	    for (i = 0; esuite[crt][i] !='*'; ++i)
		    paquet[x].suite[i] = esuite[crt][i];
	    paquet[x].suite[i] = '\0';
        i++;
        for (j = 0; esuite[crt][i] !='*'; ++i, ++j)
		    paquet[x].minisuite[j] = esuite[crt][i];
	    paquet[x].minisuite[j] = '\0';
        ++i;
        for (j = 0; esuite[crt][i] !='\0'; ++i, ++j)
		    buffvaleur[j] = esuite[crt][i];
	    buffvaleur[j] = '\0';
        paquet[x].valeur = ft_miniatoi(buffvaleur);
        for(j = 0; j <= 7; ++j)
        {
            ft_strcpy(paquet[x].matrix[j], matrix[j]);   
        }
        for(j = 0; paquet[x].suite[j] != '\0'; ++j)
            paquet[x].matrix[4][((12 - ft_len(paquet[x].suite))/2)+j] = paquet[x].suite[j];
        for(j = 0; paquet[x].minisuite[j] != '\0'; ++j)
            paquet[x].matrix[2][2+j] = paquet[x].minisuite[j];
        for(j = 0; paquet[x].minisuite[j] != '\0'; ++j)
            paquet[x].matrix[6][9+j] = paquet[x].minisuite[j];
        ++crt;
    }
    paquet[x].valeur = -999;
    paquet[x].suite[0] = '\0';
    paquet[x].couleur[0] = '\0';
    for(j = 0; paquet[x].suite[j] != '\0'; ++j)
        ft_strcpy(paquet[x].matrix[j], matrix[j]);
    fclose(fsuite);
}

void ft_ini_vide(SCARTE *paquet, int x) //x le nombre de carte
{
    int i;
    char null[80] = "\0";
   
    for(i =0; i <= x; ++i)
    {
        paquet[i].valeur = 0;
        ft_strcpy(paquet[i].suite, null);
        ft_strcpy(paquet[i].couleur, null);
    }
}