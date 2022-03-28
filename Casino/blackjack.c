#include "bibcarte.h"

void    ft_lecture_blackjack(SCARTE *paquet)
{
    int aff;
    int y;
    int l;
    int c;
    int max = 0;
    int t;

    aff = 15;
    for(y = 1; paquet[y].suite[0] != '\0' ; ++y, ++max);
    if(max < aff)
        aff = max;
    for(y = 0; y <= max ; ++y)
    {
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

int ft_blackjack2(SCARTE *pioche, SCARTE *main, int score[2], int x)
{
    int y;
    int val = 0;
    score[1] = 0;

    ft_transfert_aleatoire(pioche, main, x);
    for(y = 0; main[y].suite[0] != '\0' ; ++y)
    {
        val += main[y].valeur;
        if(main[y].valeur == 11)
            ++score[1];
    }
    score[0] = val;
    if (score[0] > 21)
    {
        while(score[1] > 0 && score[0] > 21)
        {
            score[0] -= 10;
            --score[1];
        }
    }
    ft_lecture_blackjack(main);
    ft_putstr(" -> Soit : ");
    ft_putnbr(score[0]);
    ft_putstr("\n\n");
    return(score[0]);
}

void    ft_blackjack(SCARTE *jeux, int *argent)
{
    SCARTE pioche[100];
    SCARTE main[100];
    SCARTE banque[100];
    int score[2] = {0,0};
    int scorebq[2] = {0,0};
    char c;
    char str[20];

    ft_ini_vide(main, 90);
    ft_ini_vide(pioche, 90);
    ft_ini_vide(banque, 90);
    ft_copy_paquet(jeux, pioche);
    system("clear");
    ft_putstr("\nVotre main\n");
    score[0] = ft_blackjack2(pioche, main, score, 2);
    if (score[0] == 21)
    {
        ft_putstr("BLACK JACK !! Vous doublez la mise !!\nVous gagnez 6 jetons\n");
        *argent = *argent + 6;
        return;
    }
    while(score[0] != 21)
    {
        ft_putstr("Souhaitez vous une carte supplementaire ?\nO Pour oui\nN Pour non\n");
        fgets(str, sizeof str, stdin);
        c = str[0];
        if (c == 'n' || c =='N')
            break;
        if(c == 'o' || c == 'O')
        {
            system("clear");
            ft_putstr("\nVous avez :\n");
            score[0] = ft_blackjack2(pioche, main, score, 1);
            if(score[0] > 21)
            {
                if(score[0] > 21)
                {
                    ft_putstr("Perdu... Vous avez depassé 21\nVous perdez 3 jetons\n");
                    *argent = *argent - 3;
                    break;
                }
            }
        } 
    }
    if (score[0] <= 21)
    {
        system("clear");
        ft_putstr("\nVous avez :\n");
        ft_blackjack2(pioche, main, score, 0);
        ft_putstr("\nLa banque a :\n");
        scorebq[0] = ft_blackjack2(pioche, banque, scorebq, 2);
        while (scorebq[0] < 17 && scorebq[0] < score[0] && score[0] > 0)
        {
        sleep(2);
        system("clear");
        ft_putstr("\nVous avez :\n");
        ft_blackjack2(pioche, main, score, 0);
        ft_putstr("\nLa banque re-pioche :\n");
        scorebq[0] = ft_blackjack2(pioche, banque, scorebq, 1);
        }
        if (scorebq[0] > 21 || score[0] > scorebq[0])
        {
            ft_putstr("BRAVO !! Vous avez gagné !!\nVous gagnez 3 jetons\n");
            *argent = *argent + 3;
        }
        else if (scorebq[0] == score[0])
            ft_putstr("Egalité, vous recupez votre mise\n");
        else
        {
            ft_putstr("Perdu... \nDommage Vous perdez 3 jetons\n");
            *argent = *argent - 3;
        }
    }
}
