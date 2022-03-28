#include "bibcarte.h"

int list_vainqueur(int score[10], int vainqueur[10])
{
    int i;
    int j = 0;
    int v = 0;
    int max;
    for (i = 0; score[i] != 0;++i)
    {
        if (score[i] > max)
            max = score[i];
    }
    for (i = 0; score[i] != 0;++i)
    {
        if (score[i] == max)
        {
            vainqueur[j] = i;
            ++j;
            ++v;
        }
    }
    return (v);
}

void    ft_texas(SCARTE *jeux, int *argent)
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
    int nbj = 3;
    int jactif;
    int resultat[100][52] = {0};
    int score[10] = {0};
    int vainqueur[10] = {0};
    int v;
    int t = 0; // le nombre de toure
    int r; // le decomte de la riviere
    int mise = 0;
    char c = '\0';
    char str[20];

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
            r = 3;
            l = 22;
        }
        if (t > 0)
        {
            r = 1;
            l = 100;
        }
        if (t>0)
            ft_lecture_blackjack(riviere);
        //les joueurs
        if (c == '\0' || c=='m' || c=='M')
        {
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
                score[i+1] = ft_score_resultat(tmp, resultat);
                ft_ini_vide(tmp, 9);
                x = ft_aleatoire(6, score[i+1]);
                ft_putstr("Joueur (");
                ft_putnbr(i+1);
                if (score[i+1] + x < l)
                {
                    ft_putstr(") se couche\n");
                    ft_ini_vide(joueur[i], 10);
                    ++jactif;
                }
                else
                {
                    ft_putstr(") suit\n");
                    mise += 2;
                }
            }
        }
        if (jactif == nbj +1)
        {
            ft_putstr("Tout le monde c'est couché\nVous gagnez la mise\n");
            *argent = *argent + mise;
            break;
        }
        //les joueurs fin
        }
        ////les joueurs fin
        ft_putstr("[M] Pour Miser (2 jetons)\n[Q] Pour Quitez\n");
        ft_putstr("\nLe pot est de : ");
        ft_putnbr(mise);
        ft_putstr("\nVous avez : ");
        ft_putnbr(*argent);
        ft_putstr(" jetons\n");
        fgets(str, sizeof str, stdin);
        c = str[0];
        if (c == 'q' || c == 'Q')
            break;
        if (c == 'm' || c == 'M')
        {
            mise += 2;
            *argent = *argent- 2;
            if(t <3)
                ft_transfert_aleatoire(pioche, riviere, r);
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
        system("clear");
        ft_putstr("Vous avez ");
        ft_score_poker(main, resultat, 5);
        score[0] = ft_annonce_score(main, resultat);
        //ft_putnbr(score[0]);
        for (i = 0; i <= nbj; ++i)
        {
            if (joueur[i]->suite[0] != '\0')
            {
                ft_putstr("\nJoueur (");
                ft_putnbr(i+1);
                ft_putstr(") a ");
                for (x = 0; riviere[x].suite[0] != '\0'; ++x)
                {
                    ft_copy_carte(riviere, joueur[i], x, (2+x));
                }
                ft_init_score(resultat);
                ft_score_poker(joueur[i], resultat, 5);
                score[1+i] = ft_annonce_score(joueur[i], resultat);
                //ft_putnbr(score[1+i]);
            }
        }
        v = list_vainqueur(score, vainqueur);
        if (v == 1)
        {
            if (vainqueur[0] == 0)
            {
                ft_putstr("Vous avez gagnez !!\nVous remportez le pot");
                *argent = *argent + mise;
            }
            else
            {
                ft_putstr("Joueur (");
                ft_putnbr(vainqueur[0]);
                ft_putstr(") gagne la partie et le pot\n");
            }
        }
        else
        {
            ft_putstr("Il y a ");
            ft_putnbr(v);
            ft_putstr(" vainqueur a ce partager le pot :\n");
            if (vainqueur[0] == 0)
                ft_putstr("- Vous\n");
            for (i = 1; vainqueur[i] != 0; ++i)
            {
                ft_putstr("- Joueur (");
                ft_putnbr(vainqueur[i]);
                ft_putstr(")\n");
            }
            if (vainqueur[0] == 1)
            {
                ft_putstr("\nVous avez gagnez une partie du pot : ");
                ft_putnbr(mise/v);
                ft_putstr(" jetons\n");
                *argent = *argent + (mise/v);
            }
        }
    }
}  