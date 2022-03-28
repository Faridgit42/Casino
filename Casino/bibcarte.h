#ifndef BIBCARTE_H
# define BIBCARTE_H
#  include <stdio.h>
#  include <time.h>
#  include <unistd.h>
#  include <string.h>
#  include <stdlib.h>

typedef struct carte
{
    int valeur;
    int matricule;
    char suite[40];
    char minisuite[10];
    char couleur[40];
    char minicouleur[10];
    char jonction[40];
    char matrix[8][20];
}       SCARTE;

//outils
char    *ft_strcpy(char *dest, char *src);
char    *ft_strcpysc(char *dest, int);
void	ft_putchar(char c);
void    ft_putstr(char *str);
void	ft_putnbr(int nb);
int     ft_miniatoi(char *str);
int     ft_strcmp(char *s1, char *s2);
void    ft_test();
int     ft_len(char *str);

//initialisation
void    ft_suppsautdeligne(char str[60][40], int x);
void    ft_ini_croisement(SCARTE *paquet, char *suite, char *couleur);
void    ft_ini_simple(SCARTE *paquet, char *suite);
void    ft_ini_vide(SCARTE *paquet, int x);
int     ft_calcule_nb_entrer_fichier(char * str);

//manip
int     ft_nbr_carte(SCARTE *paquet);
int     ft_aleatoire(int x, int r); // x le nbr de carte et r le resultat precedent
void    ft_transfert_aleatoire(SCARTE *pioche, SCARTE *main, int z); //z le nb de carte voulue
void    ft_lecture(SCARTE *paquet);
void    ft_lecture_analogique(SCARTE *paquet);
void    ft_lecture_visuel(SCARTE *paquet, int aff);
void    ft_copy_paquet(SCARTE *p1, SCARTE *p2);
void    ft_copy_carte(SCARTE *pioche, SCARTE *main, int c, int p);
void    ft_lecture_double(SCARTE *paquet, SCARTE *paquet2, int aff);

//triage
void    ft_ordedecroissant(SCARTE *paquet, char c);
void    ft_detect_suite(SCARTE *paquet, int s);  //s = egale le nombre de mini de suite voulu
void    ft_detect_suite2(SCARTE *paquet, int x, int v); //v le nombre de carte qui se suive, x la position dans le paquet
void    ft_detect_pair(SCARTE *paquet, int c); //c = nb de couleur
void    ft_detect_pair2(SCARTE *paquet, int i, int j);
void    ft_detect_couleur(SCARTE *paquet);
void    ft_detect_grande_carte(SCARTE *paquet);

//blackjack
int     ft_blackjack2(SCARTE *pioche, SCARTE *main, int score[2], int x);
void    ft_blackjack(SCARTE *jeux, int *argent);
void    ft_lecture_blackjack(SCARTE *paquet);

//poker
void    ft_poker(SCARTE *jeux, int *argent);
void    ft_changement_de_carte(SCARTE *pioche, SCARTE *main, int c);
void    ft_lecture_poker(SCARTE *paquet);
void    ft_init_score(int score[100][52]);
int     ft_score_resultat(SCARTE *paquet, int score[100][52]);
int     ft_annonce_score(SCARTE *paquet, int score[100][52]);
void    ft_score_poker(SCARTE *paquet, int resultat[100][52], int s);

//texas
void    ft_texas(SCARTE *jeux, int *argent);

#endif