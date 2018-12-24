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
#include "elf.h"
#include "convert.h"


//afficher le type de l'entete correspondant
void afficher_type(Elf32_Shdr entete_section)
{
	switch(entete_section.sh_type)
	{
		case SHT_NULL: 
			printf("NULL");
			break;
		case SHT_PROGBITS:
			printf("PROGBITS\t  ");
			break;
		case SHT_SYMTAB: printf("SYMTAB\t  ");
			break;
		case SHT_STRTAB: printf("STRTAB\t  ");
			break;
		case SHT_RELA: printf("RELA");
			break;
		case SHT_HASH: printf("HASH");
			break;
		case SHT_DYNAMIC: printf("DYNAMIC");
			break;
		case SHT_NOTE: printf("NOTE\t  ");
			break;
		case SHT_NOBITS: printf("NOBITS");
			break;
		case SHT_REL: printf("REL");
			break;
		case SHT_SHLIB: printf("SHLIB");
			break;
		case SHT_DYNSYM: printf("DYNSYM");
			break;
		case SHT_LOPROC: printf("LOPROC");
			break;
		case SHT_HIPROC: printf("HIPROC");
			break;
		case SHT_LOUSER: printf("LOUSER");
			break;
		case SHT_HIUSER: printf ("HIUSER");
			break;
		default:
			printf ("UNDEFINED  ");
	}
}

//lecture de la table des sections 
//la fonction retourn ECHEC si la lecture s'est bien passée sinon ECHEC
//lecture d'une section
int lecture_entete_section (FILE *fd,Elf32_Ehdr entete,Elf32_Shdr sh_table[]) {
	uint32_t i;
	//on se déplace là aussi début à e_shoff
	if (fseek (fd,entete.e_shoff,SEEK_SET) != 0) {
		printf ("Erreur de déplacement dans le fichier\n");
		return ECHEC;
	}
	for (i = 0; i < entete.e_shnum ; i ++) {
			 ;
		//lecture du bloc
		if (fread ((void *)&sh_table[i],entete.e_shentsize,1,fd) != 1) {
			printf ("Erreur de lecture\n");
		    return ECHEC;
		}
		sh_table[i].sh_name = valeur_big_endian32 (sh_table[i].sh_name);
		sh_table[i].sh_type = valeur_big_endian32 (sh_table[i].sh_type);
		sh_table[i].sh_flags = valeur_big_endian32 (sh_table[i].sh_flags);
		sh_table[i].sh_addr = valeur_big_endian32 (sh_table[i].sh_addr);
		sh_table[i].sh_offset = valeur_big_endian32 (sh_table[i].sh_offset);
		sh_table[i].sh_size = valeur_big_endian32 (sh_table[i].sh_size);
		sh_table[i].sh_link = valeur_big_endian32 (sh_table [i].sh_link);
		sh_table[i].sh_info = valeur_big_endian32 (sh_table[i].sh_info);
		sh_table[i].sh_addralign = valeur_big_endian32 (sh_table[i].sh_addralign);
		sh_table[i].sh_entsize = valeur_big_endian32 (sh_table[i].sh_entsize);
		
	}
	
	return SUCCES;
}
//Affichage fanion
void fanion (Elf32_Shdr entete_section) {
	switch (entete_section.sh_flags) {
		case 1:printf ("W  ");
		break ;
		case 2:printf ("A  ");
		break;
		case 4:printf ("X  ");
		break;
		case 3:printf("AW ");
		break;
		case SHF_MASKPROC: printf ("M  ");
		break;
		case 6:printf ("AX ");
		break;
		default:printf("   ");
	}
}
//elle prend en paramètre le pointeur de fichier fd,puis la table des sections
//elle renvoie un tampon s'il n 'y a pas eu erreur autrement NULL
char *lecture_section (FILE *fd,Elf32_Shdr table) {
	char *tampon = malloc (table.sh_size);
	if (tampon == NULL) return NULL;
	//on séplace aussi dans le fichier du début de sh_offset
	if (fseek (fd,(off_t)table.sh_offset,SEEK_SET) != 0) {	
			printf ("Erreur (lecture_section) : déplacement\n");
			return NULL;
	}	
	
	int rd = fread ((void *) tampon,table.sh_size,1,fd);
	if (rd != 1) {
		printf ("Erreur (lecture) :tampon\n");
		return NULL;
	}
	return tampon;
	
}
//Affichage de la table des sections
void afficher_table_section (FILE *fd,Elf32_Ehdr entete,Elf32_Shdr table_section []) {
	char *tampon_table ;
	//on récupère le tampon de début
	tampon_table = lecture_section (fd,table_section [entete.e_shstrndx]);
	if (tampon_table == NULL) {
		printf ("Erreur tampon\n");
	}	
	//Affiche le contenu d'une section dont le nom est donné en paramètre

	printf ("Il y a %d en-tetes de section ,débutant à l'adresse de décalage 0x%x:\n\n",entete.e_shnum,entete.e_shoff);
	printf ("En-têtes de section :\n");
	printf (" [N°] Décala Adr      Taille\tAl LN INf Fan  Type\t Nom \n");
	for (int i = 0; i < entete.e_shnum ; i++) {

		printf(" [%02d] ",i);
	    printf("%06x ", table_section[i].sh_offset);
		printf("%08x ", table_section[i].sh_addr);
		printf("%06x ", table_section[i].sh_size);
		printf("%4d  ", table_section[i].sh_addralign);
		printf("%2d ",table_section [i].sh_link); 
		printf("%2d  ",table_section [i].sh_info);
		//fanion
		fanion (table_section[i]);
		printf ("  ");
		//affichage du type
		afficher_type(table_section[i]);
		printf("%s",tampon_table +table_section[i].sh_name);
		printf ("\n");
	}
}

//cette fonction recherche une section si elle existe renvoie l'indice oû ce strouve la section  sinon renvoie ECHEC 
int recherche_section (FILE *fd,Elf32_Ehdr entete,Elf32_Shdr table_section[],char *shname) {
	int i;
	//on parcours la table des sections on compare les name par rapport au name fournit 
	char *tampon = lecture_section (fd,table_section [entete.e_shstrndx]);
	for (i = 0; i < entete.e_shnum; i ++) {
		if (strcmp (shname,tampon + table_section[i].sh_name) == 0)
			return i;
	}
	return ECHEC;
}
void affiche_caracatere (int *c,int taille) {
	for (int k = 0; k < taille ; k ++) 	{
		if (c [k] >= 32 && c [k] <= 126) printf ("%c",c[k]);
		
		else printf (".");
	}
}

void affiche_une_section (FILE *fd,Elf32_Ehdr entete,Elf32_Shdr table_section [],int i_section) {
	int adr = table_section[i_section].sh_addr,j ,i = 0;
	
	//il est nécessaire de stocker les codes asci dans un tableau pour les afficher apprès
	int code_asci [NB_OCTETS];
	//on se déplace dans le fichier pour être exactement à la section que nous souhaitons lire les caractères qui suivent
	fseek (fd,table_section[i_section].sh_offset,SEEK_SET);
	for  (; i < table_section[i_section].sh_size;i += 16) {
		
			printf ("0x%08x ",adr);
			for (j = 0; j < NB_OCTETS ; j++) {
				 if (j % 4 == 0) printf (" ");
				 code_asci [j] = fgetc (fd); 
				 printf ("%02x",code_asci[j]);
			}
			printf (" ");
			//affiche des caracteres
			affiche_caracatere (code_asci,j);
			printf ("\n");
			adr += 16;
		
	}
}

