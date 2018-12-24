#ifndef _ELF_
#define _ELF_

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

#define SUCCES 0
#define ECHEC  -1

//test si le fichier est elf ou pas 
//retourne ECHEC si le format elf n'est pas respecté
int verifie_elf (Elf32_Ehdr entete);
//lecture du fichier elf et initialisation du pointeur de fichier
//retourne SUCCES si la lecture s'est bien passée sinon echec
int lecture_elf_fichier (FILE *fd,Elf32_Ehdr *entete);

//un petit menu pour inviter l'utilisateur à faire un choix
void menu ();
#endif
