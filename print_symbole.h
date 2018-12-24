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

/*lecture de la table des symboles
--la fonction retourn ECHEC si la lecture s'est bien passée sinon ECHEC
elle prend :le pointeur sur le fichier ,la table des symboles à initialisé ,le header puis la table des sections vu que les symboles sont contenues dans les sections
*/
int lecture_table_symbole (FILE *fd,Elf32_Shdr table_section[],Elf32_Sym *table_symbole,int32_t i_sym,Elf32_Ehdr entete);

//affiche les symboles
void affiche_symboles  (FILE *fd,Elf32_Ehdr entete,Elf32_Shdr section_table[],Elf32_Sym *table_symbole);//lecture d'un type de symbole

void type_symb (Elf32_Sym symbole);
//affiche le link correspondant au champ st_shndx

void affiche_link (Elf32_Sym symbole);
//affiche la visibilité des symboles selon la valeur de st_other

void affiche_visi (Elf32_Sym symbole);
#endif
