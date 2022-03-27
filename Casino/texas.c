#include "bibcarte.h"

void    ft_texas(SCARTE *jeux)
{
    SCARTE pioche[100];
    SCARTE main[100];
    SCARTE riviere[100];
    SCARTE tmp[100];
    SCARTE joueur[10][100];
    int i;
    int x;
    int j;
    int l; //limite du jeu
    int argent;
    int nbj = 3;
    int jactif;
    int resultat[100][52] = {0};
    int scorem = 0; //score de la main
    int scorej[10];
    int t = 0; // le nombre de toure
    int r; // le decomte de la riviere
    int mise = 0;
    char c = '\0';
    char str[20];

    argent = 50;
    ft_ini_vide(tmp, 90);
    ft_ini_vide(main, 90);
    ft_ini_vide(riviere, 90);
    ft_ini_vide(pioche, 90);
    for (i = 0; i <= nbj; ++i)
        ft_ini_vide(joueur[i], 90);
    ft_copy_paquet(jeux, pioche);
    ft_transfert_aleatoire(pioche, main, 2);
    for (i = 0; i <= nbj; ++i)
        ft_transfert_aleatoire(pioche, joueur[i], 2);
    jactif = 0;   
    while (t <= 3)
    {
        system("clear");
        ft_putstr("\nVotre main\n");
        ft_lecture_blackjack(main);
        if (t == 0)
        {
            r = 0;
            l = 22;
        }
        if (t == 1)
        {
            r = 3;
            l = 100;
        }
        if (t > 1)
            r = 1;
        ft_transfert_aleatoire(pioche, riviere, r);
        if (t>0)
            ft_lecture_blackjack(riviere);
        //les joueurs
        for (i = 0; i <= nbj; ++i)
        {
            if (joueur[i]->suite[0] != '\0')
            {
                j = 0;
                for (x = 0; joueur[i][x].suite[0] != '\0'; ++x)
                {
                    ft_copy_carte(joueur[i], tmp, x, x);
                    ++j;
                }
                for (x = 0; riviere[x].suite[0] != '\0'; ++x)
                {
                    ft_copy_carte(riviere, tmp, x, (2+x));
                    ++j;
                }
                ft_init_score(resultat);
                //ft_lecture_blackjack(tmp);
                ft_score_poker(tmp, resultat, j);
                scorej[i] = ft_score_resultat(tmp, resultat);
                ft_ini_vide(tmp, 9);
                x = ft_aleatoire(6, scorej[i]);
                ft_putstr("Joueur ");
                ft_putnbr(i+1);
                if (scorej[i] + x < l)
                {
                    ft_putstr(" se couche\n");
                    ft_ini_vide(joueur[i], 10);
                    ++jactif;
                }
                else
                {
                    ft_putstr(" suit\n");
                    mise += 5;
                }
            }
        }
        if (jactif == nbj +1)
        {
            ft_putstr("Tout le monde c'est couché");
            //sleep(3);
            break;
        }
        //les joueurs fin
        ft_putstr("[M] Pour Miser (5 pieces)\n[Q] Pour Quitez\n");
        ft_putstr("\nLe pot est de :");
        ft_putnbr(mise);
        ft_putstr("\nVous avez : ");
        ft_putnbr(argent);
        ft_putstr(" pieces\n");
        fgets(str, sizeof str, stdin);
        c = str[0];
        if (c == 'q' || c == 'Q')
            break;
        if (c == 'm' || c == 'M')
        {
            mise += 5;
            argent -= 5;
            ++t;
        }
    }
    if ((c == 'm' && jactif < (nbj +1)) || (c == 'M' && jactif < (nbj +1)))
    {
        for (i = 0; riviere[i].suite[0] != '\0'; ++i)
        {
            ft_copy_carte(riviere, main, i, (2+i));
        }
        ft_init_score(resultat);
        ft_putstr("Vous avez :\n");
        ft_score_poker(main, resultat, 5);
        scorem = ft_annonce_score(main, resultat);
        for (i = 0; i <= nbj; ++i)
        {
            if (joueur[i]->suite[0] != '\0')
            {
                ft_putstr("\nJoueur ");
                ft_putnbr(i+1);
                ft_putstr(" a :\n");
                //ft_lecture_blackjack(joueur[i]);
                for (x = 0; riviere[x].suite[0] != '\0'; ++x)
                {
                    ft_copy_carte(riviere, joueur[i], x, (2+x));
                }
                ft_init_score(resultat);
                ft_score_poker(joueur[i], resultat, 5);
                scorej[i] = ft_annonce_score(joueur[i], resultat);
            }
        }
        if (scorem > scorej[0] && scorem > scorej[1] && scorem > scorej[2] && scorem > scorej[3])
            ft_putstr("\nVous avez gagner !!\n");
    }
}  