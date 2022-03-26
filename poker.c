#include "bibcarte.h"

void    ft_lecture_poker(SCARTE *paquet)
{
    int y;

    for(y = 0; paquet[y].suite[0] != '\0' ; ++y)
    { 
        ft_putnbr(y + 1);
        ft_putstr(" : ");
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

void    ft_changement_de_carte(SCARTE *pioche, SCARTE *main, int c)
{
    SCARTE tmp[1];

    ft_ini_vide(tmp, 1);
    ft_transfert_aleatoire(pioche, tmp, 1);
    main[c] = tmp[0];
}

void ft_copy_carte(SCARTE *pioche, SCARTE *main, int c, int p)
{
    main[p] = pioche[c];
}

void    ft_score_poker(SCARTE *paquet, int resultat[100][52], int s)
{
    int i;
    int j;
    int x;
    int d = 0;
    int v = 1; //calcule des suite
    //int s = 5; //nb de carte mini dans une suite
    int c = 4; //nb de couleur

    ft_ordedecroissant(paquet, 'v');
    for (x = 0, i = 0; paquet[i].matricule != '\0'; ++x, ++i) //carte la plus grande
                resultat[0][x] = paquet[i].matricule;
    for (i = 0; paquet[i].suite[0] != '\0'; ++i) //paire
    {
        for(j = c -1; j >= 1; --j)
        {
            if(paquet[i].valeur == paquet[i + j].valeur)
            {
                for (d = 0; resultat[(10*j)+d][0] != 0; ++d);
                for (x = 0; x <= j; ++x, ++i)
                    resultat[(10*j)+d][x] = paquet[i].matricule;
                --i;
            }
        }
    }
    for (i = 0; paquet[i].suite[0] != '\0'; ++i) //suite 
    {
        if(paquet[i].valeur == paquet[i + 1].valeur);
        else if(paquet[i].valeur == paquet[i + 1].valeur+1)
        {
            ++v;
            if (v == s)
            {
                ++i;
                j = 0;
                d = 0;
                for (x = 0; resultat[40+x][0] != 0; ++x);
                while (v >= 1)
                {
                    if(paquet[i].valeur == paquet[i-1].valeur)
                    {
                        --i;
                        ++d;
                    }
                    else if(paquet[i].valeur == paquet[i-1].valeur-1)
                    {
                        resultat[40+x][j] = paquet[i].matricule;
                        ++j;
                        --i;
                        --v;
                        ++d;
                    }
                    if (v == 1)
                    {
                       resultat[40+x][j] = paquet[i].matricule;
                       --v;
                    }
                }
            i = i + d;
            }
        }
        else
        {
            v = 1;
        } 
    }
    ft_ordedecroissant(paquet, 'c');
    for (i = 0; paquet[i].suite[0] != '\0'; ++i) //couleur
    {
        if(ft_strcmp(paquet[i].couleur, paquet[i + s-1].couleur) == 0)
        {
            for (d = 0; resultat[50+d][0] != 0; ++d);
            for (x = 0; x <= s-1; ++x, ++i)
                resultat[50+d][x] = paquet[i].matricule;
        }
    }
    for (i = 0; paquet[i].suite[0] != '\0'; ++i) //quint
    {
        if(ft_strcmp(paquet[i].couleur, paquet[i+1].couleur) == 0 && paquet[i].valeur == paquet[i + 1].valeur+1 )
        {
            ++v;
            if (v == s)
            {
                ++i;
                j = 0;
                d = 0;
                for (x = 0; resultat[60+x][0] != 0; ++x);
                while (v >= 1)
                {
                    if(paquet[i].valeur == paquet[i-1].valeur)
                    {
                        --i;
                        ++d;
                    }
                    else if(paquet[i].valeur == paquet[i-1].valeur-1)
                    {
                        resultat[60+x][j] = paquet[i].matricule;
                        ++j;
                        --i;
                        --v;
                        ++d;
                    }
                    if (v == 1)
                    {
                       resultat[60+x][j] = paquet[i].matricule;
                       --v;
                    }
                }
            i = i + d;
            }
        }
        else
        {
            v = 1;
        } 
    }
    while (resultat[10][0] != 0 && resultat[20][0] != 0) //full
    {
        for (i = 0; resultat[70+i][0] != 0; ++i);
        for (x = 0; resultat[10+i][x] != 0; ++x)
            resultat[70+i][x] = resultat[10][x];
        for (j = 0; resultat[20+i][j] != 0; ++j)
            resultat[70+i][x+j] = resultat[20][j];
        for (x = 0; resultat[10+x][0] != 0; ++x)
        {
            for (j = 0; resultat[10+x][j] != 0; ++j)
            resultat[10+x][j] = resultat[10+x+1][j];
        }
        for (x = 0; resultat[20+x][0] != 0; ++x)
        {
            for (j = 0; resultat[20+x][j] != 0; ++j)
            resultat[20+x][j] = resultat[20+x+1][j];
        }
    }
}

int ft_annonce_score(SCARTE *paquet, int score[100][52])
{
    int i;
    int j;
    int x;
    int u;
    int sctotal = 0;
    SCARTE tmp[100];
   
    for (x = 0; score[60+x][0] != 0; ++x)
    {
        for (u = 0; score[60+x][u] != 0; ++u)
        {
            for (i = 0; paquet[i].matricule != score[60+x][u]; ++i);
            tmp[u] = paquet[i];
        }
        ft_lecture_blackjack(tmp);
        if (paquet[i].valeur == 14)
            ft_putstr("Quinte Flush Royale !");
        else
        {
            ft_putstr("Quinte flush aux ");
            ft_putstr(paquet[i].couleur);
        }
        ft_putstr(".\n");
        sctotal =+ 900 + paquet[i].valeur;
        return(sctotal);
    }
    for (x = 0; score[30+x][0] != 0; ++x)
    {
        for (u = 0; score[30+x][u] != 0; ++u)
        {
            for (i = 0; paquet[i].matricule != score[30+x][u]; ++i);
            tmp[u] = paquet[i];
        }
        ft_lecture_blackjack(tmp);
        ft_putstr("Carré de ");
        ft_putstr(paquet[i].suite);
        ft_putstr(".\n");
        ft_ini_vide(tmp, 5);
        sctotal =+ 800 + paquet[i].valeur;
        return(sctotal);
    }
    for (x = 0; score[70+x][0] != 0; ++x)
    {
        for (u = 0; score[70+x][u] != 0; ++u)
        {
            for (i = 0; paquet[i].matricule != score[70+x][u]; ++i);
            tmp[u] = paquet[i];
        }
        ft_lecture_blackjack(tmp);
        ft_putstr("Full aux ");
        ft_putstr(paquet[i].suite);
        ft_putstr(".\n");
        ft_ini_vide(tmp, 5);
        sctotal =+ 700 + paquet[i].valeur;
        return(sctotal);
    }
    for (x = 0; score[50+x][0] != 0; ++x)
    {
        for (u = 0; score[50+x][u] != 0; ++u)
        {
            for (i = 0; paquet[i].matricule != score[50+x][u]; ++i);
            tmp[u] = paquet[i];
        }
        ft_lecture_blackjack(tmp);
        ft_ini_vide(tmp, 5);
        ft_putstr("Couleur a ");
        ft_putstr(paquet[i].couleur);
        ft_putstr(".\n");
        sctotal =+ 600 + paquet[i].valeur;
        return(sctotal);
    }
    for (x = 0; score[40+x][0] != 0; ++x)
    {
        for (u = 0; score[40+x][u] != 0; ++u)
        {
            for (i = 0; paquet[i].matricule != score[40+x][u]; ++i);
            tmp[u] = paquet[i];
        }
        ft_lecture_blackjack(tmp);
        ft_ini_vide(tmp, 5);
        ft_putstr("Suite aux ");
        ft_putstr(paquet[i].suite);
        ft_putstr(".\n");
        sctotal =+ 500 + paquet[i].valeur;
        return(sctotal);
    }
    for (x = 0; score[20+x][0] != 0; ++x)
    {
        for (u = 0; score[20+x][u] != 0; ++u)
        {
            for (i = 0; paquet[i].matricule != score[20+x][u]; ++i);
            tmp[u] = paquet[i];
        }
        ft_lecture_blackjack(tmp);
        ft_ini_vide(tmp, 5);
        ft_putstr("Brelan de ");
        ft_putstr(paquet[i].suite);
        ft_putstr(".\n");
        sctotal =+ 400 + paquet[i].valeur;
        return(sctotal);
    }
    j = 0;
    for (x = 0; score[10+x][0] != 0 && x < 2 ; ++x)
    {
        for (u = 0; score[10+x][u] != 0; ++u)
        {
            for (i = 0; paquet[i].matricule != score[10+x][u]; ++i);
            tmp[j] = paquet[i];
            ++j;
        }
    }
    if (j > 0)
        ft_lecture_blackjack(tmp);
    ft_ini_vide(tmp, 5);
    for (x = 0; score[10+x][0] != 0 && x < 2; ++x)
    {
        for (i = 0; paquet[i].matricule != score[10+x][0]; ++i);
        ft_putstr("Paire de ");
        ft_putstr(paquet[i].suite);
        ft_putstr(" ");
        if (x == 0)
            sctotal += 100 + paquet[i].valeur;
        else
            sctotal += 100;
    }
    if (j > 0)
        ft_putstr("\n");
    if (sctotal == 0)
    {
        for (i = 0; paquet[i].matricule != score[0][0]; ++i);
        tmp[j] = paquet[i];
        ft_lecture_blackjack(tmp);
        ft_ini_vide(tmp, 5);
        ft_putstr("Carte la plus grande ");
        ft_putstr(paquet[i].suite);
        ft_putstr(" de ");
        ft_putstr(paquet[i].couleur);
        ft_putstr(".\n");
        sctotal =+ paquet[i].valeur;
    }
    return(sctotal);
}

int ft_score_resultat(SCARTE *paquet, int score[100][52])
{
    int i = 0;
    int x;
    int sctotal = 0;
   
    for (x = 0; score[60+x][0] != 0; ++x)
    {
        sctotal =+ 900 + paquet[i].valeur;
        return(sctotal);
    }
    for (x = 0; score[30+x][0] != 0; ++x)
    {
        sctotal =+ 800 + paquet[i].valeur;
        return(sctotal);
    }
    for (x = 0; score[70+x][0] != 0; ++x)
    {
        sctotal =+ 700 + paquet[i].valeur;
        return(sctotal);
    }
    for (x = 0; score[50+x][0] != 0; ++x)
    {
        sctotal =+ 600 + paquet[i].valeur;
        return(sctotal);
    }
    for (x = 0; score[40+x][0] != 0; ++x)
    {
        sctotal =+ 500 + paquet[i].valeur;
        return(sctotal);
    }
    for (x = 0; score[20+x][0] != 0; ++x)
    {
        sctotal =+ 400 + paquet[i].valeur;
    }
    for (x = 0; score[10+x][0] != 0 && x < 2; ++x)
    {
        if (x == 0)
            sctotal = sctotal + 100 + paquet[i].valeur;
        else
            sctotal = sctotal + 100;
    }
    for (i = 0; i <= 4; ++i)
        sctotal = sctotal + paquet[i].valeur;
    return(sctotal);
}

void ft_init_score(int score[100][52])
{
    int x;
    int i;
    int u;

    for (i = 0; i <= 9; ++i)
    {
        for (x = 0; score[(i*10)+x][0] != 0; ++x)
        {
            for (u = 0; score[(i*10)+x][u] != 0; ++u)
                score[(i*10)+x][u] = 0;
        }
    }
}

int ft_poker_IA(SCARTE *pioche, int changement)
{
    SCARTE banque[3][100];;
    SCARTE tmp[100];
    int resultat[100][52] = {0};
    int scoreb = 0;
    int i;
    int c; //carte transfere vers tmp
    int p;
    int scoremini[2];
    int scoreminitmp[2];

    ft_ini_vide(banque[0], 100);
    ft_ini_vide(tmp, 100);
    ft_transfert_aleatoire(pioche, banque[0], 5);
    while (changement > 0 && scoreb <= 500)
    {   
        system("clear");
        ft_putstr("\nla banque a\n");
        ft_ini_vide(banque[1], 100);
        ft_copy_paquet(banque[0], banque[1]);
        ft_lecture_blackjack(banque[0]);
        ft_init_score(resultat);
        ft_score_poker(banque[1], resultat, 5); 
        scoreb = ft_score_resultat(banque[1], resultat);
        if (scoreb <= 500)
        {
            ft_putstr("La banque peut changer \n");
            ft_putnbr(changement);
            ft_putstr(" de fois\n");
            for (i = 0; i <=4; ++i)
            {
                for (c = 0, p = 0; c <=4; ++c)
                {
                    if (c != i)
                    {
                        ft_copy_carte(banque[0], tmp, c, p);
                        ++p;
                    }
                }
                ft_init_score(resultat);
                //ft_lecture_blackjack(tmp); //<-debug ne pas effacer
                ft_score_poker(tmp, resultat, 4);
                scoreminitmp[1] = ft_score_resultat(tmp, resultat);
                if (scoreminitmp[1] > scoremini[1])
                {
                    scoremini[0] = i;
                    scoremini[1] = scoreminitmp[1];
                }
               // printf("\nil y a une paire : %d le score : %d -le mini : %d soit la carte %d\n", resultat[10][0], scoreminitmp[1], scoremini[1], scoremini[0]); 
                ft_ini_vide(tmp, 10);
            }
            sleep(1);
            ft_putstr("\nLa banque change la carte : ");
            ft_putstr(banque[0][scoremini[0]].suite);
            ft_putstr(" de ");
            ft_putstr(banque[0][scoremini[0]].couleur);
            ft_putstr("\n");
            sleep(3);
            ft_changement_de_carte(pioche, banque[0], scoremini[0]);
            scoremini[1] = 0;
            --changement;
        }
    }
    ft_putstr("\nla banque a\n");
    ft_lecture_blackjack(banque[0]);
    sleep(3);
    system("clear");
    ft_putstr("La banque a \n");
    ft_init_score(resultat);
    ft_score_poker(banque[0], resultat, 5);
    scoreb = ft_annonce_score(banque[0], resultat);
    return (scoreb);
}

void    ft_poker(SCARTE *jeux)
{
    SCARTE pioche[100];
    SCARTE main[100];
    char c = 'x';
    char str[20];
    int changement = 5;
    int resultat[100][52] = {0};
    int scorej = 0;
    int scoreb = 0;

    ft_ini_vide(main, 100);
    ft_ini_vide(pioche, 100);
    ft_copy_paquet(jeux, pioche);
    ft_transfert_aleatoire(pioche, main, 5);
    while(changement > 0)
    {
        system("clear");
        ft_putstr("Votre main est :\n");
        ft_lecture_visuel(main, 15);
        if (changement == 5)
            ft_putstr("Vous pouvez changer ");
        else
            ft_putstr("Vous pouvez encore changer ");
        ft_putnbr(changement);
        ft_putstr(" fois de carte ?\nSi oui, indiquer le numero de la carte \nSinon [M] pour garder cette main\n[V]Pour ranger les cartes par ordres de valeur\n[C]Par ordre de couleur\n");
        fgets(str, sizeof str, stdin);
        c = str[0];
        if (c == 'm' || c == 'M')
            break;
        if (c == 'v' || c == 'V' || c == 'c' || c == 'C')
        {
            ft_ordedecroissant(main, c);
        }
        if (c >= '0' && c <= '5')
        {
            ft_changement_de_carte(pioche, main, (c - 49));
            --changement;
        }
    }
    system("clear");
    ft_putstr("Vous avez \n");
    ft_score_poker(main, resultat, 5);
    scorej = ft_annonce_score(main, resultat);
    sleep(4);
    changement = 5;
    scoreb = ft_poker_IA(pioche, changement);
    ft_putstr("\nVous avez \n");
    scorej = ft_annonce_score(main, resultat);
    if (scorej > scoreb)
        ft_putstr("\nVous avez GAGNEZ !!!\n");
    else if (scorej == scoreb)
        ft_putstr("\nEgalité ! Incroyable !\n");
    else
        ft_putstr("\nVous avez perdu...\n");
}

