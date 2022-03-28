#include "bibcarte.h"

void    ft_sousmenu(void (*fct)( SCARTE* , int*), char *jeux, int *argent)
{
    char cara;
    char str[20];
    SCARTE pioche[100];

    ft_ini_vide(pioche, 70);
    ft_ini_croisement(pioche, jeux, "Fichier_txt/Couleur.txt");
    fct(pioche, argent);
    while (1)
    {
        ft_putstr("\nSouhaitez vous rejouer ?\nO Pour oui\nN Pour non\n");
        if (*argent > 1)
        {
            ft_putstr("Vous avez ");
            ft_putnbr(*argent);
            ft_putstr(" jetons\n");
        }
        if (*argent == 1)
             ft_putstr("Il vous reste un seul jeton ");
        if (*argent <= 0)
        {
            system("clear");
            ft_putstr("Vous n'avez plus de jeton\nOnt vous a bien plumer\nMerci d'avoir jouer");
            sleep(6);
            exit(0);
        }
        fgets(str, sizeof str, stdin);
        cara = str[0];
        if (cara == 'n' || cara =='N')
           break;
        if (cara == 'o' || cara == 'O')
            fct(pioche, argent);
    }
}


void    ft_menu()
{
    char cara;
    char str[20];
    int argent;

    argent = 50;
    while (cara != 'q')
    {
        system("clear");
        ft_putstr("\nA quoi souhaitez vous jouer ?\n[P] - Pour Poker (5 jetons la mise)\n[B] - Pour BlackJack (3 jetons la mise)\n[T] - Pour Texas Hold'em (2 jetons la mise)\n[Q] - Pour Quitter\n");
        if (argent > 1)
        {
            ft_putstr("Vous avez ");
            ft_putnbr(argent);
            ft_putstr(" jetons\n");
        }
        if (argent == 1)
             ft_putstr("Il vous reste un seul jeton !");
        fgets(str, sizeof str, stdin);
        cara = str[0];
        if (cara == 'q' || cara == 'Q')
           break;
        if (cara == 'p' || cara == 'P')
            ft_sousmenu(ft_poker, "Fichier_txt/Suitepoker.txt", &argent);
        if (cara == 'b' || cara == 'B')
            ft_sousmenu(ft_blackjack, "Fichier_txt/Suiteblack.txt", &argent);
        if (cara == 't' || cara == 'T')
            ft_sousmenu(ft_texas, "Fichier_txt/Suitepoker.txt", &argent); 
            
    }
    ft_putstr("Merci d'avoir jouer :)");
    sleep(5);
}

int main()
{
    //ft_test();
    ft_menu();
    return 0;
}

