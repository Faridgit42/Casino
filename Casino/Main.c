#include "bibcarte.h"

void    ft_sousmenu(void (*fct)( SCARTE*), char *jeux)
{
    char cara;
    char str[20];
    SCARTE pioche[100];

    ft_ini_vide(pioche, 70);
    ft_ini_croisement(pioche, jeux, "Fichier_txt/Couleur.txt");
    fct(pioche);
    while (1)
    {
        ft_putstr("\nSouhaitez vous rejouer ?\nO Pour oui\nN Pour non\n");
        fgets(str, sizeof str, stdin);
        cara = str[0];
        if (cara == 'n' || cara =='N')
           break;
        if (cara == 'o' || cara == 'O')
            fct(pioche);
    }
}


void    ft_menu()
{
    char cara;
    char str[20];

    while (cara != 'q')
    {
        system("clear");
        ft_putstr("\nA quoi souhaitez vous jouer ?\n[P] - Pour Poker\n[B] - Pour BlackJack\n[T] - Pour Texas Hold them\n[Q] - Pour Quitter\n");
        fgets(str, sizeof str, stdin);
        cara = str[0];
        if (cara == 'q' || cara == 'Q')
           break;
        if (cara == 'p' || cara == 'P')
            ft_sousmenu(ft_poker, "Fichier_txt/Suitepoker.txt");
        if (cara == 'b' || cara == 'B')
            ft_sousmenu(ft_blackjack, "Fichier_txt/Suiteblack.txt");
        if (cara == 't' || cara == 'T')
            ft_sousmenu(ft_texas, "Fichier_txt/Suitepoker.txt"); 
    }
    ft_putstr("Merci d'avoir jouer :)");
    sleep(3);
}

int main()
{
    //ft_test();
    ft_menu();
    return 0;
}

