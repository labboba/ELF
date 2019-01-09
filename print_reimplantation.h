#ifndef _PRINTR_
#define _PRINTR_

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

#include "print_section.h"
#include "print_header.h"
#include "print_symbole.h"
#include "elf.h"
#include "convert.h"

/*principe : determine si le type est dynamique
  parametre : entete
  valeur de retour : 0 si c'est vrai sinon 1
*/
int is_dynamique(Elf32_Word section_type);

/*principe : nombre de réadressage
  parametre : fichier, entete, table des sections
  valeur de retour : le nombre de readressages
*/
int nb_dyn_sym(FILE *fd,Elf32_Ehdr entete,Elf32_Shdr table_section []);

/*principe : lecture table reloc
  parametre : fichier, table de decallage, entete de section
  valeur de retour : table de relocation
*/
Elf32_Rel *read_reloc_table(FILE * f, Elf32_Off tableOffset, Elf32_Word tableSize);

/*principe : lecture de la table de relocation a partir d'un indice passé en parametre
  parametre : fichier, table des sections, indice
  valeur de retour : table de relocation
*/
Elf32_Rel *read_reloc_index_table(FILE * f, Elf32_Shdr * sectionHeaderTable, int tableIndex);

/*principe : type de la table de relocation
  parametre : entete
  valeur de retour : aucune
*/
void print_reloc_type(Elf32_Word type);

/*principe : affichage des informations concernant les sections contenant des readressages
  parametre : fichier, table de relocation, table des symboles, pointeur de caractere
  valeur de retour : aucune
*/
void print_reloc(FILE* f, Elf32_Rel reloc, Elf32_Sym* symtab, char *tampon);

/*principe : fonction permettant de trouver les section contenant les readressages
  parametre : fichier, entete de section, table de sections
  valeur de retour : aucune
*/
void get_ln (FILE *fd,Elf32_Ehdr entete,Elf32_Shdr table_section []);

/*principe : recupere la valeur de la section ou symbole pour faire la reimplantation
  parametre : table des symboles, entete
  valeur de retour : adresse de la section a reimplanter
*/
Elf32_Addr getValueReimplantation(Elf32_Sym *tableSymbole, Elf32_Word info);

#endif
