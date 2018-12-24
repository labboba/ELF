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
#include "print_header.h"
#include "print_symbole.h"
#include "print_section.h"
#include "convert.h"
#include "elf.h"




int main (int argc , char * argv []) {
	FILE *fd;
	Elf32_Ehdr entete;
	Elf32_Shdr * table_section;
	Elf32_Sym *table_symbole;
	int etat = 1;
	int i_section;
	char choix;
	char section [40];
	if (argc < 2) {
		printf ("Arguments insuffisants\n");
		return ECHEC;
	}
	
	//ouverture du fichier avec open
	//l'option O_RDONLY Pour une lecture seule
	fd = fopen (argv[1],"rb");
	if (fd == NULL) {
		printf ("Erreur d'ouverture deu fichier\n");
		return ECHEC;
	}
	
	//initialisation du header
	int r = lecture_elf_fichier (fd,&entete);
	if (r == ECHEC) {
		printf ("Erreur d'initialisation de l'entête\n");
		return ECHEC;
	}
	
	//allocation de la section header table
	table_section = (Elf32_Shdr *) malloc(entete.e_shentsize*entete.e_shnum);
	if (!table_section) {
		printf ("Erreur d'allocation mémoire de la table\n");
	}
	if (lecture_entete_section (fd,entete,table_section) == ECHEC) {
		printf ("Erreur de lecture de la table des sections\n");
		return ECHEC;
	}
	menu ();
	while (etat == 1) {
		scanf ("%c",&choix);
		switch (choix) {
			case 'h': printf ("\n");affiche_entete (&entete);
			 etat = 1;
			break;
			case 'S': afficher_table_section (fd,entete,table_section);
			 etat = 1;
			break;
			case 'x': printf ("Entrez une section\n");
					  scanf ("%s",section);
					 printf ("\n");	
					i_section = recherche_section(fd,entete,table_section,section);
					if (i_section != ECHEC) {		printf ("Section trouvée\n");
						affiche_une_section (fd,entete,table_section,i_section);
						etat = 1;
					} else {
						printf ("Erreur: AVERTISSEMENT: La section << %s >> n'a pas été vidangée parce qu'inexistante !\n",section);		
						etat = 1;
					}				  
			break;
			case 's': affiche_symboles(fd,entete,table_section,table_symbole);
				  etat = 1;
			break;
			case 'r': printf ("Réimplantation pas encore faite\n");
			break;
			case 'q': printf ("Vous venez de quitter l'appli\n");etat = 0;
			break;
			default: printf ("\n");menu ();
		}
	}
	
	

} 

