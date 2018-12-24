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
//lecture de la table des sections 
//la fonction retourn ECHEC si la lecture s'est bien passée sinon ECHEC
int lecture_entete_section (FILE *fd,Elf32_Ehdr entete,Elf32_Shdr sh_table[]);

//lecture d'une section
//elle prend en paramètre le pointeur de fichier fd,puis la table des sections
//elle renvoie un tampon s'il n 'y a pas eu erreur autrement NULL
char *lecture_section (FILE *fd,Elf32_Shdr table);

//Affichage de la table des sections
void afficher_table_section (FILE *fd,Elf32_Ehdr entete,Elf32_Shdr table_section []);

//afficher le type de l'entete correspondant
void afficher_type(Elf32_Shdr entete_section);
//afficher le fanion
void fanion (Elf32_Shdr entete_section);
//cette fonction recherche une section si elle existe renvoie SUCCES sinon ECHC
int recherche_section (FILE *fd,Elf32_Ehdr entete,Elf32_Shdr table_section[],char *shname);
//aFfiche une section en fonction du
void affiche_une_section (FILE *fd,Elf32_Ehdr entete,Elf32_Shdr table_section [],int i_section);
//cette fonction prend un tableau d'entier qui contient des codes ascii et le nombr d'élemnt du tableau
//affiche le caractère correspondant au code ascii c[idince] si celui ci est imprimable sinon affiche .
void affiche_caracatere (int *c,int taille);
#endif
