#ifndef _PRINTR_
#define _PRINTR_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "elf.h"




/*
 
 */
void get_ln (FILE *fd,Elf32_Ehdr entete,Elf32_Shdr table_section []);

//return vrai si le sh_type est SHT_DYNSYM
int is_dynamique(Elf32_Word section_type);



//nombre de réadressage
int nb_dyn_sym(FILE *fd,Elf32_Ehdr entete,Elf32_Shdr table_section []);	

//lecture table reloc
Elf32_Rel *read_reloc_table(FILE * f, Elf32_Off tableOffset, Elf32_Word tableSize);

/*
 read_reloc_index_table
    Descr: Lecture d'une table de realocation dont on donne l'indice
    Param:
        - f: fichier dans lequel lire la table
        - sectionHeaderTable: Pointeur vers la table de section header
        - tableIndex: Indice de section correspondant à une table de realocation
    Effet de bord: Appel a lire_realocation
 */
Elf32_Rel* lire_realocation_index_table(FILE* f, Elf32_Shdr* sectionHeaderTable, int tableIndex);

/*
 affiche_table_realocation
    Descr: Affichage des tables de realocation
    Param:
        - f: fichier dans lequel est la realoc table
        - realoc_Table: Table de realocation à afficher
        - symtab: Table de symbole du fichier
    Effet de bord: Affiche la table de relocation donnée
 */
void affiche_table_realocation(FILE* f, Elf32_Rel* relocTable, Elf32_Word tableSize, Elf32_Sym* symtab);


/*
 affiche_all_table_realocation
    Descr: Affiche l'ensemble des tables de realocation
    Param:
        - f: fichier dans lequel lire les tables
        - header: ELF header du fichier f
        - sectionHeaderTable: Table de section header
        - symtab: Table de symbole du fichier
 */
void affiche_all_table_realocation(FILE* f, Elf32_Ehdr header, Elf32_Shdr sectionHeaderTable[], Elf32_Sym* symtab);

char* get_section_name(FILE* f, Elf32_Ehdr header, Elf32_Shdr* section_header_table, int index);

int find_header_section(FILE *f, Elf32_Shdr *section_header_table,char *nm_index, Elf32_Ehdr header);

int find_type_section_table(Elf32_Shdr *section_header_table,Elf32_Word type ,Elf32_Ehdr header);


#endif
