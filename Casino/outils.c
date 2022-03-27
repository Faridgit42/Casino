#include "bibcarte.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void    ft_putstr(char *str)
{
	int	i;

	for(i = 0; str[i] != '\0'; ++i)
		ft_putchar(str[i]);
}

void	ft_putnbr(int nb)
{
    if (nb < 0)
    {
        nb = -nb;
        ft_putchar('-');
    }
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}

int ft_len(char *str)
{
    int i;

    for (i = 0; str[i] !='\0'; ++i);
    return(i);
}

int ft_miniatoi(char *str)
{
    int i;
    int reso;
    int sign;

    reso = 0;
    sign = 1;
    i = 0;
    for (i = 0; str[i] == '-'; ++i)
        sign = sign * -1;
    while (str[i])
    {
        reso = reso * 10 + (str[i] - 48);
        ++i;
    }
    return (reso*sign);
}

char    *ft_strcpy(char *dest, char *src)
{
	int		i;

	for (i = 0; src[i] !='\0'; ++i)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char    *ft_strcpysc(char *dest, int n)
{
	int		i = (ft_len(dest)/2);

    while (n > 0)
	{
		dest[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (dest);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0'; ++i);
	return (s1[i] - s2[i]);
}

void    ft_test()
{
    SCARTE pioche[100];
    SCARTE main[10][100];
    

    ft_ini_croisement(pioche, "Fichier_txt/Suite.txt", "Fichier_txt/Couleur.txt");
    //ft_ini_simple(pioche, "Fichier_txt/Speciale.txt");
    ft_transfert_aleatoire(pioche, main[0], 15);
    ft_copy_paquet(main[0], main[1]);
    ft_putstr("le paquet : \n");
    ft_lecture(main[1]);
    //ft_transfert_aleatoire(main, main2, 15);
    //ft_lecture_visuel(pioche, 13);
    //ft_transfert_aleatoire(pioche, main, 15);
    //ft_putstr("\nEt les cartes aleatoires\n");
    //ft_lecture_visuel(main, 13);
    //ft_lecture(main2);
}