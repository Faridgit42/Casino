#include "bibcarte.h"

int ft_nbr_carte(SCARTE *paquet)
{
    int i;

    for(i = 0; paquet[i].suite[0] != '\0' ; ++i);
    return(i);
}

void    ft_lecture_double(SCARTE *paquet, SCARTE *paquet2, int aff)
{
    int y;
    int l;
    int c;
    int max;
    int t;
    
    max = ft_nbr_carte(paquet) + ft_nbr_carte(paquet2);
    if(max < aff)
        aff = max;
    for(y = 0; y <= max ; ++y)
    {
        for(l = 0; l <= 7 ; ++l)
        {
            for(t = 0; t <= aff && t < (ft_nbr_carte(paquet)-y); ++t)
            {
                for(c = 0; paquet[y+t].matrix[l][c] != '\0'; ++c)
                {
                    ft_putchar(paquet[y+t].matrix[l][c]);
                }
                ft_putchar(' ');
            }
            ft_putstr("  ");
            for(t = 0; t <= aff && t < (ft_nbr_carte(paquet2)-y); ++t)
            {
                for(c = 0; paquet2[y+t].matrix[l][c] != '\0'; ++c)
                {
                    ft_putchar(paquet2[y+t].matrix[l][c]);
                }
                ft_putchar(' ');
            }
        ft_putchar('\n');
        }
    ft_putchar('\n');
    y = y + aff;
    }
}

void    ft_lecture_analogique(SCARTE *paquet)
{
    int y;

    for(y = 0; paquet[y].suite[0] != '\0' ; ++y)
    { 
        ft_putstr(paquet[y].suite);
        if(paquet[y].couleur[0] != '\0')
        {
            ft_putstr(" ");
            ft_putstr(paquet[y].jonction);
            ft_putstr(" ");
        }
        ft_putstr(paquet[y].couleur);
        ft_putstr("\n");
    }
}

void    ft_lecture_visuel(SCARTE *paquet, int aff)
{
    int y;
    int l;
    int c;
    int max = 0;
    int t;
    char tete[20] = "            ";

    aff -= 1;
    for(y = 1; paquet[y].suite[0] != '\0' ; ++y, ++max);
    if(max < aff)
        aff = max;
    for(y = 0; y <= max ; ++y)
    {
        for(t = 0; t <= aff && t <= (max-y); ++t)
        {
            ft_strcpysc(tete, (y+t+1));
            ft_putstr(tete);
            ft_putchar(' ');
        }
        ft_putchar('\n');
        for(l = 0; l <= 7 ; ++l)
        {
            for(t = 0; t <= aff && t <= (max-y); ++t)
            {
                for(c = 0; paquet[y + t].matrix[l][c] != '\0'; ++c)
                {
                    ft_putchar(paquet[y + t].matrix[l][c]);
                }
                ft_putchar(' ');
            }
        ft_putchar('\n');
        }
    ft_putchar('\n');
    y = y + aff;
    }
}

void    ft_lecture(SCARTE *paquet)
{
    int y;

    for(y = 0; paquet[y].suite[0] != '\0' ; ++y)
    {
        ft_putnbr(paquet[y].matricule);
        ft_putchar('-');
        ft_putstr(paquet[y].minisuite);
        ft_putstr(paquet[y].minicouleur);
        ft_putstr(" / ");
        ft_putstr(paquet[y].suite);
        if(paquet[y].couleur[0] != '\0')
        {
            ft_putstr(" ");
            ft_putstr(paquet[y].jonction);
            ft_putstr(" ");
        }
        ft_putstr(paquet[y].couleur);
        ft_putstr(" = ");
        ft_putnbr(paquet[y].valeur);
        ft_putstr("\n");
    }

}

int ft_aleatoire(int x, int r)
{
    int t;
    
    t = (time(NULL));
    while (t < 1000)
        t = t*t;
    t = t%100;
    if (t == 0)
    t = 42;
    
    while (r < 10000000)
        {
            r = r*t;
            r = r+t+x;
        }
    r = r%10000000 / (10000000/x);
    return (r);
}

void ft_transfert_aleatoire(SCARTE *pioche, SCARTE *main, int z) //z le nb de carte voulue
{
    int r; // resultat
    int c; // la carte prise de la pioche
    int m; // la main
    int x;

    x = ft_nbr_carte(pioche);
    if (z > x)
        z = x;
    for (r = x, m = ft_nbr_carte(main); z > 0; ++m, --x, --z)
    {
        c = ft_aleatoire(x,r);
        if (c > x)
            c = x;
        r = c;
        main[m] = pioche[c];
        while (pioche[c].suite[0] != '\0')
        {
            pioche[c] = pioche[c + 1];
            ++c;
        }
    }
}
void    ft_copy_paquet(SCARTE *p1, SCARTE *p2)
{
    int i;

    for (i = 0; p1[i].suite[0] != '\0'; ++i)
        p2[i] = p1[i];
}

void    ft_copy_carte(SCARTE *pioche, SCARTE *main, int c, int p)
{
    main[p] = pioche[c];
}
