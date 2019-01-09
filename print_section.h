#ifndef _PRINTS_
#define _PRINTS_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <elf.h>
#include <byteswap.h>
#define  NB_OCTETS 16

/*principe : lecture de la table des sections
  parametre : l'entete du fichier ELF, le fichier fd, la table des symboles
  valeur de retour : 0 si le deplacement a bien ete effectué sinon 1
*/
int lecture_entete_section (FILE *fd,Elf32_Ehdr entete,Elf32_Shdr sh_table[]);

/*lecture d'une section
  parametre : elle prend en paramètre le pointeur de fichier fd,puis la table des sections
  valeur de retour : elle renvoie un tampon s'il n 'y a pas eu erreur autrement NULL
*/
char *lecture_section (FILE *fd,Elf32_Shdr table);

/*Affichage du fanion
  parametre : entete de section
  valeur de retour : aucune
*/
void fanion (Elf32_Shdr entete_section);

/*Affichage de la table des sections
  parametre : fichier fd, entete, table des sections
  valeur de retour : aucune
*/
void afficher_table_section (FILE *fd,Elf32_Ehdr entete,Elf32_Shdr table_section []);


/*afficher le type de l'entete correspondant
  parametre : entete de section
  valeur de retour : aucune
*/
void afficher_type(Elf32_Shdr entete_section);

/*cette fonction recherche une section
  parametre : fichier fd, entete, table des sections, nom de la section
  valeur de retour : 0 si la section existe sinon 1
*/
int recherche_section (FILE *fd,Elf32_Ehdr entete,Elf32_Shdr table_section[],char *shname);

/*affiche une section en fonction du nom
  parametre : fichier fd, entete, table des sections, indice de la section
  valeur de retour : aucune
*/
void affiche_une_section (FILE *fd,Elf32_Ehdr entete,Elf32_Shdr table_section [],int i_section);

/*affiche le caractère correspondant au code ascii c[indice]
  parametre : tableau d'entier, taille du tableau
  valeur de retour : aucune
*/
void affiche_caracatere (int *c,int taille);
#endif
