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
#include "print_symbole.h"
#include "convert.h"
#include "elf.h"

//afficher le type correspondant à la valeur de st_sype
void type_symb (Elf32_Sym symbole) {
	switch (symbole.st_info) {
		case STT_NOTYPE:
			printf ("NOTYPE  ");
		break;
		case STT_OBJECT:printf ("OBJECT");
		break;
		case STT_FUNC:printf ("FUNC");
		break;	
		case STT_SECTION:printf ("SECTION ");
		break;
		case STT_FILE:printf ("FILE    ");
		break;
		case STT_LOPROC:printf ("LOPROC");
		break;	
		case STT_HIPROC:printf ("HIPROC");
		break;
		default:	printf ("NOTYPE  ");
		break;
	}
}

//affiche le link correspondant au champ st_shndx
void affiche_link (Elf32_Sym symbole) {
	switch (symbole.st_info) {
		case STB_LOCAL: printf ("LOCAL\t");break;
 		case STB_GLOBAL:printf ("GLOBAL ");break;
		case STB_WEAK:printf ("WEAK\t");break;
		case STB_LOPROC:printf ("LOPROC\t");break;
		case STB_HIPROC:printf ("HIPROC\t");break;
		default :       printf ("GLOBAL\t");break;
	}
}

//affiche la visibilité des symboles selon la valeur de st_other
void affiche_visi (Elf32_Sym symbole) {
	switch (symbole.st_other) {
		case STV_DEFAULT: printf ("DEFAULT");break;
 		case STV_INTERNAL:printf ("INTERNAL");break;
		case STV_HIDDEN:printf ("HIDDEN");break;
		case STV_PROTECTED:printf ("PROTECTED");break;
		default :break;
	}
}

//lit et affiche les symboles pour une sections
int lecture_table_symbole (FILE *fd, Elf32_Shdr table_section[], Elf32_Sym *table_symbole, int32_t i_sym, Elf32_Ehdr entete) {
	//lecture d'une section 
	char *tampon;
	int32_t sec_symb_link, nb_symbole;
	//char *tampon_table ;
	//on récupère le tampon de début
	//test 0
	printf("je pense que c la\n");
	char *tampon_table = lecture_section (fd,table_section [entete.e_shstrndx]);

	table_symbole =(Elf32_Sym *) lecture_section (fd,table_section[i_sym]);
	if (table_symbole == NULL) 
		return ECHEC;
	
	//on le lit un lien entre une section et un symbole
	sec_symb_link = table_section [i_sym].sh_link;
	tampon = lecture_section (fd,table_section [sec_symb_link]);
	if (tampon == NULL) 
		return ECHEC;
	//test 1
	printf("le tampon contient: %s", tampon);
	//pour parcourir la table des symboles on calcule le nombre de symbole de la section
	nb_symbole = table_section [i_sym].sh_size/(sizeof(Elf32_Sym));
	//test 2
	printf("le nombre de symbole dans la table est : %i\n", nb_symbole); 
	printf ("\nTable de symboles << %s >> contient %d entrées :\n",tampon_table+table_section[i_sym].sh_name,nb_symbole);
	printf ("   Num:	valeur\t\tTail Type\tLien	Vis	Nom\n");
	for (int i = 0; i < nb_symbole;i ++) {
		printf ("    %2d: ",i);
		table_symbole [i].st_name  = valeur_big_endian32 (table_symbole[i]. st_name);
        table_symbole [i].st_value = valeur_big_endian32 (table_symbole[i].st_value);
		table_symbole [i].st_other = valeur_big_endian32 (table_symbole[i].st_other);
	//affichage
		printf ("%08x\t",table_symbole [i].st_value);
		printf ("%d     ",table_symbole [i].st_size);
	    type_symb (table_symbole [i]);
		affiche_link (table_symbole [i]);
	//affiche la visibilité des symboles selon la valeur de st_other
		affiche_visi(table_symbole[i]);
		printf (" %s ",tampon + table_symbole[i]. st_name);
		printf ("\n");
	}
	return SUCCES;
}

//return ECHEC si l'initialisation a echou lorsque la fonction lecture retourne ECHEC
//sinon SUCCES
void affiche_symboles  (FILE *fd,Elf32_Ehdr entete,Elf32_Shdr section_table[],Elf32_Sym *table_symbole) {
		//on pacourt tous les entêtes
	for (int i = 0; i < entete.e_shnum ; i ++) {
		if (section_table[i].sh_type == SHT_SYMTAB || section_table[i].sh_type == SHT_DYNSYM )  {
			if (lecture_table_symbole (fd, section_table,table_symbole,i,entete) == ECHEC) {
				printf ("Erreur de lecture des symboles\n");
				exit (0);
			}
		}
	}
}

