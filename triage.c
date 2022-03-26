#include  "bibcarte.h"

void    ft_ordedecroissant(SCARTE *paquet, char c)
{
    int i;
    SCARTE	tmp;
    
    for (i = 1; paquet[i].suite[0] != '\0'; ++i)
    {
        if(ft_strcmp(paquet[i].couleur, paquet[i-1].couleur) < 0)
        {
            tmp = paquet[i-1];
	        paquet[i-1] = paquet[i];
	        paquet[i] = tmp;
            i = 0;
        }
    }
    if (c == 'v' || c == 'V')
    {
        for (i = 1; paquet[i].suite[0] != '\0'; ++i)
        {
            if(paquet[i].valeur > paquet[i-1].valeur)
            {
                tmp = paquet[i-1];
	            paquet[i-1] = paquet[i];
	            paquet[i] = tmp;
                i = 0;
            }
        }
    }
}

void    ft_detect_pair2(SCARTE *paquet, int i, int j)
{
    if (j == 2)
        ft_putstr("Vous avez une paire de ");
    if (j == 3)
        ft_putstr("Vous avez un brelan de ");
    if (j == 4)
        ft_putstr("Vous avez un carre de ");
    if (j > 4)
    {
        ft_putstr("Vous avez ");
        ft_putnbr(j);
        ft_putstr(" cartes identique de ");
    }
    ft_putstr(paquet[i].suite);
    ft_putstr(".\n");
}

void    ft_detect_pair(SCARTE *paquet, int c) //c = nb de couleur
{
    int i;
    int j;

    ft_ordedecroissant(paquet, 'v');
    for (i = 0; paquet[i].suite[0] != '\0'; ++i)
    {
        for(j = c; j >= 1; --j)
        {
            if(paquet[i].valeur == paquet[i + j].valeur)
            {
                ft_detect_pair2(paquet, i, j + 1);
                i = i + j;
            }
        }
    }
}


void    ft_detect_couleur(SCARTE *paquet)
{
    int i;

    ft_ordedecroissant(paquet, 'c');
    for (i = 0; paquet[i].suite[0] != '\0'; ++i)
    {
        if(ft_strcmp(paquet[i].couleur, paquet[i + 4].couleur) == 0)
        {
            ft_putstr("\nVous avez une couleur au ");
            ft_putstr(paquet[i].couleur);
            ft_putstr("\n");
        }
    }
}
void    ft_detect_suite2(SCARTE *paquet, int x, int v) //v le nombre de carte qui se suive, x la position dans le paquet
{
    ft_putstr("Vous avez une suite de ");
    ft_putnbr(v);
    ft_putstr(" cartes : "); 
    while(v >= 1)
    {
        while(paquet[x].valeur == paquet[x - 1].valeur)
            --x;
        ft_putstr(paquet[x].suite);
        if(v != 1)
            ft_putstr(", ");
        --x;
        --v;
    }
    ft_putstr(".\n");
}

void    ft_detect_suite(SCARTE *paquet, int s) //s = egale le nombre de mini de suite voulu
{
    int i;
    int v;

    ft_ordedecroissant(paquet, 'v');
    v = 1;
    for (i = 0; paquet[i].suite[0] != '\0'; ++i)
    {
        if(paquet[i].valeur == paquet[i + 1].valeur);
        else if(paquet[i].valeur == paquet[i + 1].valeur + 1)
            ++v;
        else
        {
            if (v >= s)
                ft_detect_suite2(paquet, i, v);
            v = 1;
        }
    }
    if (v >= s)
       ft_detect_suite2(paquet, i, v);
}

void ft_detect_grande_carte(SCARTE *paquet)
{
    ft_ordedecroissant(paquet, 'v');
    ft_putstr("Votre carte la plus grande est ");
    ft_putstr(paquet[0].suite);
}
