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
#include "convert.h"
#define SUCCES 0
#define ECHEC  -1

//test si le fichier est elf ou pas 
//retourne ECHEC si le format elf n'est pas respecté
int verifie_elf (Elf32_Ehdr entete) {
	if ((entete.e_ident [EI_MAG0]!= ELFMAG0) || (entete.e_ident [EI_MAG1] != ELFMAG1) || (entete.e_ident [EI_MAG2] != ELFMAG2) || (entete.e_ident [EI_MAG3] != ELFMAG3) ) 
		return ECHEC;
	return SUCCES;
}

//lecture du fichier elf et initialisation du pointeur de fichier
//retourne SUCCES si la lecture s'est bien passée sinon echec
int lecture_elf_fichier (FILE *fd,Elf32_Ehdr *entete) {
	if (entete == NULL) return ECHEC;
	//on se déplace dans le fichier à partir du début de o offset
	if (fseek(fd,0,SEEK_SET) != 0) return ECHEC;
	if (fread ((void*)entete,sizeof(Elf32_Ehdr),1,fd) != 1) return ECHEC;
	if (verifie_elf (*entete) == ECHEC) {
		printf ("Le fichier n'a pas le Format ELF\n");
		return ECHEC;
	}
	entete -> e_type    = valeur_big_endian16 (entete -> e_type);
	entete -> e_machine = valeur_big_endian16 (entete -> e_machine);
	entete -> e_version = valeur_big_endian32 (entete -> e_version); 
	entete -> e_entry   = valeur_big_endian32 (entete -> e_entry);
	entete -> e_phoff   = valeur_big_endian32 (entete -> e_phoff);
	entete -> e_shoff   = valeur_big_endian32 (entete -> e_shoff);
	entete -> e_flags   = valeur_big_endian32 (entete -> e_flags);
	entete -> e_ehsize  = valeur_big_endian16 (entete -> e_ehsize);
	entete -> e_phentsize = valeur_big_endian16 (entete -> e_phentsize);
	entete -> e_phnum   = valeur_big_endian16 (entete -> e_phnum);
	entete -> e_shentsize = valeur_big_endian16 (entete -> e_shentsize);
	entete -> e_shnum = valeur_big_endian16 (entete -> e_shnum);
	entete -> e_shstrndx = valeur_big_endian16 (entete -> e_shstrndx);

	return SUCCES;
}
void menu () {
	printf ("***************Affichage ELF : Faites un choix*****************\n");
	printf ("  h:		Pour afficher l'entete\n");
	printf ("  S:		Pour afficher les section\n");
	printf ("  x:		Pour afficher une section\n");
	printf ("  s:		Pour afficher la table des symboles\n");
	printf ("  r:		Pour afficher les tables de réimplantations\n");
	printf ("  q:		Pour quitter\n");	
}
